#!/bin/bash

echo "Setting up Godot Game Development Environment..."

echo "Cloning godot-cpp..."
git submodule add -b 4.4 https://github.com/godotengine/godot-cpp
git submodule update --init --recursive

echo "Creating necessary directories..."
mkdir -p bin/win64
mkdir -p bin/linux
mkdir -p bin/macos

echo "Building godot-cpp..."
cd godot-cpp

# Detect platform
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    PLATFORM="linux"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    PLATFORM="macos"
else
    echo "Unsupported platform: $OSTYPE"
    exit 1
fi

scons platform=$PLATFORM target=template_debug dev_build=yes
if [ $? -ne 0 ]; then
    echo "Failed to build godot-cpp!"
    exit 1
fi

cd ..
echo "Setup completed successfully!"
echo "Run ./build.sh to build the game extension."
