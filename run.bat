@echo off
setlocal enabledelayedexpansion

set "OTHER_FLAG=-Wall -Wextra"
set "FLAG_OPTIMIZE=-O3"
set "SRCDIR=src"
set "INCDIR=include"
set "OUTDIR=build"
set "OUTEXE=program.exe"
set "SOURCES="

if not exist "%SRCDIR%" (
    echo Source directory "%SRCDIR%" not found.
    exit /b 1
)
if not exist "%INCDIR%" (
    echo Include directory "%INCDIR%" not found.
    exit /b 1
)
for /r "%SRCDIR%" %%F in (*.c) do (
    set "SOURCES=!SOURCES! "%%~fF""
)
if "%SOURCES%"=="" (
    echo No .c files found under "%SRCDIR%".
    exit /b 1
)
if not exist "%OUTDIR%" mkdir "%OUTDIR%"

set "GCC_FLAGS=%OTHER_FLAG% %FLAG_OPTIMIZE%"

echo Build command: gcc %GCC_FLAGS% -I"%INCDIR%" %SOURCES% -o "%OUTDIR%\%OUTEXE%"

gcc %GCC_FLAGS% -I"%INCDIR%" %SOURCES% -o "%OUTDIR%\%OUTEXE%"
if errorlevel 1 (
    echo Build failed.
    exit /b 1
)

echo Build succeeded: "%OUTDIR%\%OUTEXE%"

echo Running: "%OUTDIR%\%OUTEXE%" %*
"%OUTDIR%\%OUTEXE%" %*
endlocal & exit /b %errorlevel%
