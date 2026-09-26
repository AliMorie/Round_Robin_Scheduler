@echo off

:: Set the name of the output executable
set output=Simulator

:: Set the names of the C source files to compile
set sources=.\src\Main.c .\src\DataGenerator.c .\src\Scheduler.c .\src\Evaluation.c .\src\Helper.c

:: Compile the C source files
gcc -o "%output%" %sources% -lm

:: Check if the compilation was successful
if %errorlevel% == 0 (
    echo Compilation successful.

    :: Run the application
    echo Running the application
    .\Simulator 10 ".\input\input_file.txt" 3 ".\output\output.csv"
) else (
    echo Compilation failed.
)


pause
