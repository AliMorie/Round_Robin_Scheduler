@echo off
setlocal

REM Set the path to the Doxygen executable
set DOXYGEN_PATH="C:\Program Files\doxygen\bin"

REM Set the path to the Doxygen configuration file
set DOXYFILE_PATH="./Docs/Doxyfile"

REM Set the path to the source code directory
set SOURCE_CODE_DIR="./SchedulingAlgoV2.0"

REM Set the output directory for Doxygen files
set OUTPUT_DIR="./Docs"

REM Check if Doxygen is installed
if exist %DOXYGEN_PATH% (
    echo Doxygen is already installed.
	
) else (
	echo so far so good
    echo Doxygen is not found on this system.
    echo Do you want to download and install Doxygen? (Y/N)
    set /p install_choice=

    REM Check user's choice
    if /i "%install_choice%"=="Y" (
        REM Download and install Doxygen form:
		echo https://www.doxygen.nl/files/doxygen-1.9.8-setup.exe

         powershell -command "(New-Object Net.WebClient).DownloadFile('https://www.doxygen.nl/files/doxygen-1.9.8-setup.exe', 'doxygen-1.9.8-setup.exe')"

    REM Install Python
    doxygen-1.9.8-setup.exe /quiet

    REM Clean up the downloaded installer
    del doxygen-1.9.8-setup.exe
    ) else (
        echo Doxygen installation is required to generate documentation.
        echo Exiting...
        exit /b 1
    )
)

echo Run Doxygen to generate documentation
%DOXYGEN_PATH% %DOXYFILE_PATH%

echo Create the output directory if it doesn't exist
if not exist %OUTPUT_DIR% mkdir %OUTPUT_DIR%

echo Copy necessary source files to the output directory
xcopy /E /I %SOURCE_CODE_DIR% %OUTPUT_DIR%\src

echo Documentation generated successfully!

endlocal