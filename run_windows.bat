@echo off
cd /d "%~dp0"
if not exist sorting.exe call build_windows.bat
if exist sorting.exe sorting.exe
pause
