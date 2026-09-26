@echo off

REM Check if Python is installed
where python >nul 2>&1
if %errorlevel% neq 0 (
REM Python is not installed. Prompt user to confirm installation
set /p install=Python is not installed. Do you want to install it? (Y/N)
if /i "%install%"=="Y" (
    REM Download Python installer
    powershell -command "(New-Object Net.WebClient).DownloadFile('https://www.python.org/ftp/python/3.10.0/python-3.10.0-amd64.exe', 'python-3.10.0-amd64.exe')"

    REM Install Python
    python-3.10.0-amd64.exe /quiet

    REM Clean up the downloaded installer
    del python-3.10.0-amd64.exe
) else (
    echo Python installation skipped. Plots can not be shown this way.
  
)
) else (
    echo Python is already installed on this system.
)

REM Verify installation
where python >nul 2>&1
if %errorlevel% equ 0 (
    echo Python has been installed successfully.
) else (
    echo Failed to install Python.
)

REM Set the virtual environment name
set VENV_NAME=myenv

REM Create the virtual environment
python -m venv %VENV_NAME%

REM Activate the virtual environment
call %VENV_NAME%\Scripts\activate

REM Install dependencies from requirements.txt
pip install -r requirements.txt

REM Run the Python script
python Plot_Data_1.py
python Plot_Data_2.py
python Print_Tables.py

REM Keep the Command Prompt window open until a key is pressed
pause

REM Deactivate the virtual environment
deactivate


