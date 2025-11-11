@echo off
echo Compiling university project...
g++ -std=c++11 -Iheaders sources/main.cpp sources/Student.cpp sources/Teacher.cpp sources/Administrative.cpp sources/Keeper.cpp -o university.exe
if %errorlevel% == 0 (
    echo Compilation successful!
    echo Running program...
    university.exe
) else (
    echo Compilation failed!
)
pause