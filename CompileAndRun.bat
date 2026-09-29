@echo off

:: Run from the folder containing this script, so relative paths
:: work even if the script is started from another location
cd /d "%~dp0"

:: Create the input and output folders if they don't exist.
:: Git doesn't track empty folders, so they can be missing
:: from a fresh clone of the repository.
if not exist "input" mkdir "input"
if not exist "output" mkdir "output"

:: Set the name of the output executable
set output=Simulator

:: Set the names of the C source files to compile
set sources=.\src\Main.c .\src\DataGenerator.c .\src\Scheduler.c .\src\Evaluation.c .\src\Helper.c

:: Compile the C source files
gcc -o "%output%" %sources% -lm

:: Check if the compilation was successful
if %errorlevel% == 0 (
    echo Compilation successful.

    REM Run the application
    echo Running the application
    .\Simulator 10 ".\input\input_file.txt" 3 ".\output\output.csv"
) else (
    echo Compilation failed.
)

pause
