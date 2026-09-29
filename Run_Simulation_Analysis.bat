@echo off
setlocal enabledelayedexpansion

REM Run from the folder containing this script, so relative paths
REM work even if the script is started from another location
cd /d "%~dp0"

set VENV_NAME=myenv
set PYTHON_CMD=python
set PYTHON_VERSION=3.10.0
set PYTHON_INSTALLER=python-%PYTHON_VERSION%-amd64.exe

REM ============================================================
REM  1. Make sure Python is installed
REM ============================================================
REM "python --version" is used rather than "where python", because
REM Windows includes a placeholder python.exe that only opens the
REM Microsoft Store. "where" finds it, but it cannot run scripts.
python --version >nul 2>&1
if !errorlevel! equ 0 (
    echo Python is already installed on this system.
    goto :python_ready
)

set /p INSTALL_CONFIRM=Python is not installed. Do you want to install it? (Y/N): 
if /i not "!INSTALL_CONFIRM!"=="Y" (
    echo Python installation skipped. Plots cannot be shown without Python.
    goto :end
)

echo Downloading Python %PYTHON_VERSION%...
powershell -NoProfile -Command "[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; (New-Object Net.WebClient).DownloadFile('https://www.python.org/ftp/python/%PYTHON_VERSION%/%PYTHON_INSTALLER%', '%PYTHON_INSTALLER%')"
if not exist "%PYTHON_INSTALLER%" (
    echo Failed to download the Python installer.
    goto :end
)

echo Installing Python %PYTHON_VERSION%. This may take a few minutes...
REM PrependPath=1 adds Python to PATH for terminals opened later
start /wait "" "%PYTHON_INSTALLER%" /quiet InstallAllUsers=0 PrependPath=1 Include_pip=1
del "%PYTHON_INSTALLER%"

REM PATH changes do not reach this already-open window, so use the
REM default per-user install location of Python 3.10 for the rest
REM of this script
set "PYTHON_CMD=%LOCALAPPDATA%\Programs\Python\Python310\python.exe"
if not exist "!PYTHON_CMD!" (
    echo Failed to install Python. Please install it manually from https://www.python.org/downloads/
    goto :end
)
echo Python has been installed successfully.

:python_ready

REM ============================================================
REM  2. Use the virtual environment, creating it if needed
REM ============================================================
if exist "%VENV_NAME%\Scripts\activate.bat" (
    echo Virtual environment "%VENV_NAME%" found. Activating it...
    call "%VENV_NAME%\Scripts\activate.bat"
    goto :run_scripts
)

if not exist "requirements.txt" (
    echo requirements.txt was not found in this folder. Cannot install the dependencies.
    goto :end
)

echo Virtual environment "%VENV_NAME%" not found. Creating it...
"!PYTHON_CMD!" -m venv "%VENV_NAME%"
if !errorlevel! neq 0 (
    echo Failed to create the virtual environment.
    goto :end
)

call "%VENV_NAME%\Scripts\activate.bat"

echo Installing dependencies from requirements.txt...
python -m pip install -r requirements.txt
if !errorlevel! neq 0 (
    echo Failed to install the dependencies.
    goto :remove_venv
)
echo Dependencies installed successfully.

REM ============================================================
REM  3. Run the analysis scripts
REM ============================================================
:run_scripts
echo.
echo Running the analysis scripts...
python Plot_Data_1.py
python Plot_Data_2.py
python Print_Tables.py

call deactivate
goto :end

:remove_venv
REM Delete the incomplete environment. Otherwise the next run would
REM find it, skip the installation, and fail on missing packages.
call deactivate
rmdir /s /q "%VENV_NAME%"
echo The incomplete virtual environment was removed. Fix the problem above, then run this script again.

:end
endlocal
pause
