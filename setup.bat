@echo off
echo Setting up Godot Game Development Environment...

echo Cloning godot-cpp...
git submodule add -b 4.4 https://github.com/godotengine/godot-cpp
git submodule update --init --recursive

echo Creating necessary directories...
if not exist "bin" mkdir bin
if not exist "bin\win64" mkdir bin\win64
if not exist "bin\linux" mkdir bin\linux
if not exist "bin\macos" mkdir bin\macos

echo Building godot-cpp...
cd godot-cpp
scons platform=windows target=template_debug dev_build=yes
if %errorlevel% neq 0 (
    echo Failed to build godot-cpp!
    pause
    exit /b 1
)

cd ..
echo Setup completed successfully!
echo Run build.bat to build the game extension.
pause
