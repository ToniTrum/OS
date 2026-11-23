@echo off
setlocal

set "SCRIPT_DIR=%~dp0"
set "BUILD_DIR=%SCRIPT_DIR%build"

cmake -S "%SCRIPT_DIR%" -B "%BUILD_DIR%" -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

cmake --build "%BUILD_DIR%" --config Release --parallel
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

cmake --install "%BUILD_DIR%" --config Release --prefix "%BUILD_DIR%\dist"
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%