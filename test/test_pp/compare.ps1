# 用法（在 VSCode 的 PowerShell）:
#   cd .\test\test_pp
#   .\compare.ps1
#   .\compare.ps1 -Prog ..\build\program.exe
#   .\compare.ps1 -Files pp01_object_macro.c,std\ex3.c   # 只跑指定檔案（正向）
param(
    [string]$Prog = "..\build\program.exe",
    [string[]]$Files
)
Set-Location $PSScriptRoot
$Prog = (Resolve-Path $Prog).Path
$tmp  = Join-Path $env:TEMP "pp_test"
New-Item -ItemType Directory -Force $tmp | Out-Null
$out = Join-Path $tmp "out.txt"
$err = Join-Path $tmp "err.txt"
$std = Join-Path $tmp "stdout.txt"

function Strip($s) { if ($null -eq $s) { "" } else { ($s -replace '\s', '') } }

function Run($f) {
    Remove-Item $out, $err, $std -ErrorAction SilentlyContinue
    $p = Start-Process -FilePath $Prog -ArgumentList "`"$f`"", "`"$out`"" `
         -WorkingDirectory $PSScriptRoot `
         -RedirectStandardError $err -RedirectStandardOutput $std `
         -NoNewWindow -Wait -PassThru
    return $p.ExitCode
}

function ErrCount() {
    if (-not (Test-Path $err)) { return 0 }
    return @(Select-String -Path $err -Pattern '^\[(Preprocess|Syntax) Error\]').Count
}

$pass = 0; $fail = 0

Write-Host "=== 正向測試：不能有錯誤，且與 gcc -E 比對（忽略空白） ==="
$pos = if ($Files) { $Files } else {
    @(Get-ChildItem pp0[1-6]*.c, pp_all.c, std\*.c | ForEach-Object { Resolve-Path -Relative $_.FullName })
}
foreach ($f in $pos) {
    $rc = Run $f; $n = ErrCount
    $mine = Strip (Get-Content $out -Raw -ErrorAction SilentlyContinue)
    $ref  = Strip ((& gcc -E -P -std=c17 $f 2>$null) -join "")
    if ($rc -eq 0 -and $n -eq 0 -and $mine -ceq $ref) {
        Write-Host "PASS  $f" -ForegroundColor Green; $pass++
    } else {
        Write-Host "FAIL  $f (exit=$rc, errors=$n)" -ForegroundColor Red
        if (Test-Path $err) { Get-Content $err -TotalCount 3 }
        if ($mine -cne $ref) {
            Write-Host "  gcc : $($ref.Substring(0,  [Math]::Min(200, $ref.Length)))"
            Write-Host "  mine: $($mine.Substring(0, [Math]::Min(200, $mine.Length)))"
        }
        $fail++
    }
}

if (-not $Files) {
    Write-Host "=== 只檢查「沒有錯誤」（含 __FILE__/__DATE__ 或刻意與 gcc 不同，不比對 gcc） ==="
    foreach ($f in "pp07_builtin.c", "pp_known_gaps.c", "warn_backslash_space.c") {
        $rc = Run $f; $n = ErrCount
        if ($rc -eq 0 -and $n -eq 0) { Write-Host "PASS  $f" -ForegroundColor Green; $pass++ }
        else { Write-Host "FAIL  $f (exit=$rc, errors=$n)" -ForegroundColor Red; $fail++ }
    }

    Write-Host "=== 錯誤測試：exit code 要是 1，錯誤數 >= 檔內 '// E:' 的行數 ==="
    foreach ($e in Get-ChildItem err\e*.c) {
        $f = Resolve-Path -Relative $e.FullName
        $rc = Run $f; $n = ErrCount
        $exp = [Math]::Max(1, @(Select-String -Path $f -Pattern '// E:').Count)
        if ($rc -eq 1 -and $n -ge $exp) {
            Write-Host "PASS  $f (errors=$n, expected>=$exp)" -ForegroundColor Green; $pass++
        } else {
            Write-Host "FAIL  $f (exit=$rc, errors=$n, expected>=$exp)" -ForegroundColor Red; $fail++
        }
    }
}

Write-Host "=== 結果: pass=$pass fail=$fail ==="
exit ([int]($fail -gt 0))