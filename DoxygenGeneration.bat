@echo off
setlocal enabledelayedexpansion

REM Set the path to the Doxygen executable
set DOXYGEN_PATH=C:\Program Files\doxygen\bin\doxygen.exe

REM Set the path to the Doxygen configuration file
set DOXYFILE_PATH=".\Docs\Doxyfile"

REM Set the path to the source code directory
set SOURCE_CODE_DIR=".\src"

REM Set the output directory for Doxygen files
set OUTPUT_DIR=".\Docs"

echo Checking if Doxygen is installed...

REM First check if doxygen is available on PATH
where doxygen >nul 2>nul
if %errorlevel% == 0 (
    set DOXYGEN_CMD=doxygen
    goto :doxygen_found
)

REM Fall back to checking the expected install location
if exist "%DOXYGEN_PATH%" (
    set DOXYGEN_CMD=%DOXYGEN_PATH%
    goto :doxygen_found
)

REM Doxygen was not found - ask the user for confirmation to install it
echo Doxygen was not found on this system.
set /p INSTALL_CONFIRM="Do you want to install Doxygen now? (Y/N): "

if /I not "%INSTALL_CONFIRM%"=="Y" (
    echo Doxygen is required to generate documentation. Exiting.
    goto :end
)

echo Installing Doxygen...

REM Try winget first (built into modern Windows 10/11)
where winget >nul 2>nul
if %errorlevel% == 0 (
    winget install --id DimitriVanHeesch.Doxygen -e --accept-source-agreements --accept-package-agreements
    if !errorlevel! == 0 (
        echo Doxygen installed successfully via winget.
        goto :recheck_doxygen
    ) else (
        echo winget installation failed.
    )
)

REM Try chocolatey as a fallback
where choco >nul 2>nul
if %errorlevel% == 0 (
    choco install doxygen.install -y
    if !errorlevel! == 0 (
        echo Doxygen installed successfully via Chocolatey.
        goto :recheck_doxygen
    ) else (
        echo Chocolatey installation failed.
    )
)

echo Could not install Doxygen automatically - winget/choco not available or install failed.
echo Please install it manually from https://www.doxygen.nl/download.html
goto :end

:recheck_doxygen
REM Re-check after install attempt
where doxygen >nul 2>nul
if %errorlevel% == 0 (
    set DOXYGEN_CMD=doxygen
    goto :doxygen_found
)
if exist "%DOXYGEN_PATH%" (
    set DOXYGEN_CMD=%DOXYGEN_PATH%
    goto :doxygen_found
)

echo Doxygen installation could not be verified. You may need to restart your terminal
echo for PATH changes to take effect, then run this script again.
goto :end

:doxygen_found
echo Doxygen found: !DOXYGEN_CMD!
echo.

echo Run Doxygen to generate documentation
"!DOXYGEN_CMD!" "%DOXYFILE_PATH%"

echo Create the output directory if it does not exist
if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

echo Copy necessary source files to the output directory
xcopy /E /I "%SOURCE_CODE_DIR%" "%OUTPUT_DIR%\src"

echo Documentation generated successfully!

:end
endlocal
pause
