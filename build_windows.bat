@echo off
cd /d "%~dp0"
if not exist results mkdir results
gcc -std=c11 -O2 -Wall -Wextra -Wpedantic src\main.c src\sorting.c src\benchmark.c src\utils.c -o sorting.exe -lpsapi
if errorlevel 1 (
  echo Build failed. Check that MinGW-w64 GCC is installed and available in PATH.
  pause
  exit /b 1
)
echo Build successful.
echo Run sorting.exe to start the menu.
pause
