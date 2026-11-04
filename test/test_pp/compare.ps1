# 用法（VSCode PowerShell）:
#   cd test_pp
#   .\compare.ps1                        # 跑全部（自動往上層找 build\program.exe）
#   .\compare.ps1 -Prog ..\..\build\program.exe
#   .\compare.ps1 -Only 'pp0*','err/e1*' # 只跑符合萬用字元的檔案
#   .\compare.ps1 -Update                # 重新產生快照（只有人工檢查過才用）
#
# 判定:
#  1. exit code：正向 0、err/ 下 1
#  2. 程式的 stdout 必須是空的
#  3. 輸出檔、stderr（錯誤+警告的訊息/檔名/行列號/數量）都要和 expected\ 內的快照完全相同
#  4. 可與 gcc 比對的檔案：輸出再與 gcc -E -P 做 token 層級比對
#     （忽略空白與換行的多寡，但 token 邊界必須一致：int ab 與 int a b 不同）
param(
    [string]$Prog,
    [string[]]$Only,
    [switch]$Update
)
Set-Location $PSScriptRoot

if (-not $Prog) {
    $dir = $PSScriptRoot
    while ($dir) {
        $cand = Join-Path $dir "build\program.exe"
        if (Test-Path $cand) { $Prog = $cand; break }
        $parent = Split-Path $dir -Parent
        if ($parent -eq $dir) { break }
        $dir = $parent
    }
}
if (-not $Prog -or -not (Test-Path $Prog)) {
    Write-Host "找不到 program.exe，請用 -Prog 指定路徑" -ForegroundColor Red
    exit 2
}
$Prog = (Resolve-Path $Prog).Path

$tmp = Join-Path $env:TEMP "pp_test"
New-Item -ItemType Directory -Force $tmp | Out-Null
$expDir = Join-Path $PSScriptRoot "expected"
New-Item -ItemType Directory -Force $expDir | Out-Null
$out = "$tmp\out.txt"; $err = "$tmp\err.txt"; $std = "$tmp\stdout.txt"
$utf8 = New-Object Text.UTF8Encoding $false

# 含 __FILE__/__DATE__/__TIME__ 或刻意與 gcc 不同的檔案，不跟 gcc 比
$noGcc = @("pp07_builtin.c", "pp_known_gaps.c", "warn_backslash_space.c")

function ReadText($p) { if (Test-Path $p) { [IO.File]::ReadAllText($p) } else { $null } }
function NormNL($s) { if ($null -eq $s) { "" } else { ($s -replace "`r`n", "`n").TrimEnd() } }
function Mask($s) {
    if ($null -eq $s) { return "" }
    $s = $s -replace '"[A-Z][a-z]{2} [ 0-9][0-9] [0-9]{4}"', '"<DATE>"'
    return ($s -replace '"[0-9]{2}:[0-9]{2}:[0-9]{2}"', '"<TIME>"')
}

# 把 C 文字切成 pp-token（字串/字元/pp-number/識別字/多字元運算子/單一字元）
function Tokens($s) {
    if ($null -eq $s) { return @() }
    $re = '"(?:\\.|[^"\\\r\n])*"|''(?:\\.|[^''\\\r\n])*''|\.?[0-9](?:[eEpP][+-]|[0-9A-Za-z_.])*|[A-Za-z_][A-Za-z0-9_]*|\.\.\.|<<=|>>=|->|\+\+|--|<<|>>|<=|>=|==|!=|&&|\|\||\*=|/=|%=|\+=|-=|&=|\^=|\|=|##|[^\s]'
    return @([regex]::Matches($s, $re) | ForEach-Object { $_.Value })
}
function Ctx($arr, $idx) {
    if ($arr.Count -eq 0) { return "(空)" }
    $a = [Math]::Max(0, $idx - 4); $b = [Math]::Min($arr.Count - 1, $idx + 4)
    if ($a -gt $b) { return "(到結尾)" }
    return ($arr[$a..$b] -join ' ')
}

function Run($f) {
    Remove-Item $out, $err, $std -ErrorAction SilentlyContinue
    $p = Start-Process -FilePath $Prog -ArgumentList "`"$f`"", "`"$out`"" `
         -WorkingDirectory $PSScriptRoot `
         -RedirectStandardError $err -RedirectStandardOutput $std `
         -NoNewWindow -Wait -PassThru
    return $p.ExitCode
}

function ShowDiff($want, $got) {
    $a = @($want -split "`n"); $b = @($got -split "`n")
    $d = @(Compare-Object $a $b)
    $shown = 0
    foreach ($x in $d) {
        if ($shown -ge 6) { Write-Host "    ..."; break }
        $tag = if ($x.SideIndicator -eq '<=') { "預期" } else { "實際" }
        $line = [string]$x.InputObject
        if ($line.Length -gt 160) { $line = $line.Substring(0, 160) + "..." }
        Write-Host "    [$tag] $line"
        $shown++
    }
}

function SnapCompare($label, $path, $actual, $problems) {
    $want = ReadText $path
    if ($null -eq $want) { $problems.Add("$label 沒有快照（先人工檢查，再用 -Update 建立）"); return }
    $want = NormNL $want
    if ($want -cne $actual) {
        $problems.Add("$label 與快照不同")
        ShowDiff $want $actual
    }
}

$files = @()
$files += Get-ChildItem -File pp0[1-9]*.c, pp_all.c, pp_known_gaps.c, warn_backslash_space.c, std\*.c |
          ForEach-Object { [pscustomobject]@{ Path = ($_.FullName.Substring($PSScriptRoot.Length + 1) -replace '\\', '/'); Neg = $false } }
$files += Get-ChildItem -File err\e*.c |
          ForEach-Object { [pscustomobject]@{ Path = ($_.FullName.Substring($PSScriptRoot.Length + 1) -replace '\\', '/'); Neg = $true } }
if ($Only) {
    $files = @($files | Where-Object { $p = $_.Path; ($Only | Where-Object { $p -like $_ }).Count -gt 0 })
}

$pass = 0; $fail = 0
foreach ($t in $files) {
    $f = $t.Path
    $name = $f -replace '[\\/]', '_'
    $rc = Run $f
    $problems = New-Object System.Collections.Generic.List[string]

    $wantRc = if ($t.Neg) { 1 } else { 0 }
    if ($rc -ne $wantRc) { $problems.Add("exit=$rc（預期 $wantRc）") }
    if ((NormNL (ReadText $std)) -ne "") { $problems.Add("程式的 stdout 不是空的") }

    $o = NormNL (Mask (ReadText $out))
    $e = NormNL (ReadText $err)

    # gcc 比對（只有正向且可比的檔案）
    $gccOk = $true
    if (-not $t.Neg -and ($noGcc -notcontains $f)) {
        $tr = Tokens ((& gcc -E -P -std=c17 $f 2>$null) -join "`n")
        $tm = Tokens (ReadText $out)
        $n = [Math]::Min($tr.Count, $tm.Count); $idx = -1
        for ($i = 0; $i -lt $n; $i++) {
            if ($tr[$i] -cne $tm[$i]) { $idx = $i; break }
        }
        if ($idx -lt 0 -and $tr.Count -ne $tm.Count) { $idx = $n }
        if ($idx -ge 0) {
            $gccOk = $false
            $problems.Add("token 序列與 gcc -E 不同（第 $idx 個 token）")
            Write-Host ("    gcc : " + (Ctx $tr $idx))
            Write-Host ("    mine: " + (Ctx $tm $idx))
        }
    }

    if ($Update) {
        if ($gccOk -and $problems.Count -eq 0) {
            [IO.File]::WriteAllText("$expDir\$name.err", $e + "`n", $utf8)
            if ($o -ne "") { [IO.File]::WriteAllText("$expDir\$name.out", $o + "`n", $utf8) }
            else { Remove-Item "$expDir\$name.out" -ErrorAction SilentlyContinue }
            Write-Host "UPDATE $f" -ForegroundColor Cyan; $pass++
        } else {
            Write-Host "SKIP   $f（有問題，不寫快照）: $($problems -join '; ')" -ForegroundColor Yellow; $fail++
        }
        continue
    }

    SnapCompare "stderr(錯誤/警告)" "$expDir\$name.err" $e $problems
    $outSnap = "$expDir\$name.out"
    if (Test-Path $outSnap) { SnapCompare "輸出檔" $outSnap $o $problems }
    elseif ($o -ne "")      { $problems.Add("輸出檔有內容但沒有快照") }

    if ($problems.Count -eq 0) { Write-Host "PASS  $f" -ForegroundColor Green; $pass++ }
    else { Write-Host "FAIL  $f : $($problems -join '; ')" -ForegroundColor Red; $fail++ }
}

Write-Host "=== 結果: pass=$pass fail=$fail ==="
if ($Update) { Write-Host "快照已寫入 expected\，請用 git diff 逐一檢查後再提交。" }
exit ([int]($fail -gt 0))