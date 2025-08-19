@echo off
echo Building Godot Game Extension...

REM Check if godot-cpp library exists
if not exist "godot-cpp\bin\libgodot-cpp.windows.template_debug.dev.x86_64.lib" (
    echo Error: godot-cpp library not found!
    echo Please run setup.bat first to build godot-cpp
    pause
    exit /b 1
)

if not exist "build" mkdir build
cd build

cmake .. -G "Visual Studio 17 2022" -A x64
if %errorlevel% neq 0 (
    echo CMake configuration failed!
    pause
    exit /b 1
)

cmake --build . --config Debug
if %errorlevel% neq 0 (
    echo Build failed!
    pause
    exit /b 1
)

echo Build completed successfully!
pause
