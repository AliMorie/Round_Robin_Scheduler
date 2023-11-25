@echo off
setlocal

REM Set the path to the Doxygen executable
set DOXYGEN_PATH="C:\Program Files\doxygen\bin"

REM Set the path to the Doxygen configuration file
set DOXYFILE_PATH=".\\Docs\\Doxyfile"

REM Set the path to the source code directory
set SOURCE_CODE_DIR=".\\SchedulingAlgoV2.0"

REM Set the output directory for Doxygen files
set OUTPUT_DIR=".\\Docs"



echo Run Doxygen to generate documentation
"%DOXYGEN_PATH%" "%DOXYFILE_PATH%"

echo Create the output directory if it doesn't exist
if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

echo Copy necessary source files to the output directory
xcopy /E /I "%SOURCE_CODE_DIR%" "%OUTPUT_DIR%\src"


echo Documentation generated successfully!

endlocal