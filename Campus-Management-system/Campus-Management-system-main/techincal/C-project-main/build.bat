@echo off
REM Build script for Campus Navigation System (Windows)

setlocal enabledelayedexpansion

echo === Building Campus Navigation System ===
echo.

REM Create build directory if it doesn't exist
if not exist "build" (
    echo Creating build directory...
    mkdir build
)

cd build

REM Run CMake
echo Configuring with CMake...
cmake ..

REM Build the project
echo Building project...
cmake --build . --config Release

cd ..

echo.
echo === Build Complete ===
echo.
echo To run the navigation system:
echo   .\build\Release\navigate.exe
echo.
echo To view the frontend:
echo   cd frontend
echo   python -m http.server 8000
echo   Then open http://localhost:8000 in your browser
