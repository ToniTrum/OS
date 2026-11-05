@echo off
setlocal enabledelayedexpansion

set "SCRIPT_DIR=%~dp0"
set "BUILD_DIR=%SCRIPT_DIR%build"

pushd "%SCRIPT_DIR%.."

echo == [1/3] Updating repository ==
git pull --ff-only
if %ERRORLEVEL% neq 0 (
    echo [ERROR] Updating repository failed.
    popd
    exit /b %ERRORLEVEL%
)

popd

echo == [2/3] CMake configuration ==
cmake -S "%SCRIPT_DIR%." -B "%BUILD_DIR%" -G "MinGW Makefiles"
if %ERRORLEVEL% neq 0 (
    echo [ERROR] CMake configuration failed.
    exit /b %ERRORLEVEL%
)

echo == [3/3] Building project ==
cmake --build "%BUILD_DIR%" --config Release --parallel
if %ERRORLEVEL% neq 0 (
    echo [ERROR] Building project failed.
    exit /b %ERRORLEVEL%
)

echo [OK] Build completed successfully!
echo ^> Executable is located in: %BUILD_DIR%
endlocal