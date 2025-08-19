cmake_minimum_required(VERSION 3.20)
project(godot_game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set build type to Debug by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Platform-specific settings
if(WIN32)
    set(TARGET_PATH "win64")
    set(GODOT_CPP_PLATFORM "windows")
    set(TARGET_NAME "libgodot_game.windows.template_debug.dev.x86_64.dll")
    set(GODOT_CPP_LIB_EXTENSION "lib")
elseif(UNIX AND NOT APPLE)
    set(TARGET_PATH "linux")
    set(GODOT_CPP_PLATFORM "linux")
    set(TARGET_NAME "libgodot_game.linux.template_debug.dev.x86_64.so")
    set(GODOT_CPP_LIB_EXTENSION "a")
elseif(APPLE)
    set(TARGET_PATH "macos")
    set(GODOT_CPP_PLATFORM "macos")
    set(TARGET_NAME "libgodot_game.macos.template_debug.dev.universal.dylib")
    set(GODOT_CPP_LIB_EXTENSION "a")
endif()

# Create bin directory for output
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${TARGET_PATH})

# GDExtension includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/godot-cpp/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/godot-cpp/gen/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/godot-cpp/gdextension)

# Source files
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*.h"
)

# Create shared library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Set output directory and name
set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${TARGET_PATH}
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${TARGET_PATH}
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin/${TARGET_PATH}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin/${TARGET_PATH}
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin/${TARGET_PATH}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin/${TARGET_PATH}
    OUTPUT_NAME godot_game.${TARGET_PATH}.template_debug.dev.x86_64
)

# Link godot-cpp
target_link_libraries(${PROJECT_NAME} 
    ${CMAKE_CURRENT_SOURCE_DIR}/godot-cpp/bin/libgodot-cpp.${GODOT_CPP_PLATFORM}.template_debug.dev.x86_64.${GODOT_CPP_LIB_EXTENSION}
)

# Compiler flags
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32_LEAN_AND_MEAN)
    
    # Set runtime library to match godot-cpp (static release runtime)
    set_property(TARGET ${PROJECT_NAME} PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded")
        
    # Disable iterator debug level to match godot-cpp
    target_compile_definitions(${PROJECT_NAME} PRIVATE _ITERATOR_DEBUG_LEVEL=0)
endif()
