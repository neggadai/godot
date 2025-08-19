#!/bin/bash

echo "Building Godot Game Extension..."

# Create build directory
mkdir -p build
cd build

# Configure with CMake
cmake ..
if [ $? -ne 0 ]; then
    echo "CMake configuration failed!"
    exit 1
fi

# Build
make -j$(nproc)
if [ $? -ne 0 ]; then
    echo "Build failed!"
    exit 1
fi

echo "Build completed successfully!"
