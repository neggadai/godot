# Godot Game - C++ CMake Skeleton

A minimal C++ game development skeleton using Godot 4.4 with GDExtension and CMake build system.

**✅ FULLY WORKING PROJECT** - Successfully builds on Windows with PowerShell scripts!

## Project Structure

```
godot-test/
├── src/                    # C++ source files
│   ├── register_types.cpp  # GDExtension registration
│   ├── register_types.h
│   ├── player.cpp          # Player character class
│   ├── player.h
│   ├── game.cpp           # Game manager class
│   └── game.h
├── scenes/                 # Godot scene files
│   └── main.tscn          # Main game scene
├── bin/                   # Compiled libraries (auto-generated)
├── build/                 # CMake build files (auto-generated)
├── godot-cpp/             # Godot C++ bindings (submodule)
├── CMakeLists.txt         # CMake build configuration
├── godot_game.gdextension # GDExtension configuration
├── project.godot          # Godot project file
├── setup.bat/.sh/.ps1     # Environment setup scripts
└── build.bat/.sh/.ps1     # Build scripts
```

## Prerequisites

- **Godot 4.4+** - Download from [godotengine.org](https://godotengine.org/)
- **CMake 3.20+** - For building the C++ extension
- **Git** - For cloning submodules
- **C++ Compiler:**
  - Windows: Visual Studio 2022 or MinGW
  - Linux: GCC or Clang
  - macOS: Xcode Command Line Tools

### Additional Requirements

- **SCons** - Required for building godot-cpp
  ```bash
  pip install scons
  ```

## Setup Instructions

### 1. Initialize the Project

**Windows (PowerShell - Recommended):**
```powershell
.\setup.ps1
```

**Windows (Batch):**
```cmd
setup.bat
```

**Linux/macOS:**
```bash
./setup.sh
```

This will:
- Clone the godot-cpp submodule
- Create necessary directories
- Build the godot-cpp library

### 2. Build the Extension

**Windows (PowerShell - Recommended):**
```powershell
.\build.ps1
```

**Windows (Batch):**
```cmd
build.bat
```

**Linux/macOS:**
```bash
./build.sh
```

### 3. Open in Godot

1. Open Godot Engine
2. Import the project by selecting `project.godot`
3. The extension should automatically load

## Game Features

### Player Class
- Inherits from `CharacterBody2D`
- Basic 2D movement with WASD/Arrow keys
- Configurable speed property
- Physics-based movement with `move_and_slide()`

### Game Class
- Inherits from `Node2D`
- Score management system
- Game state management (start/end game)
- Extensible for additional game logic

## Controls

- **W/↑** - Move up
- **A/←** - Move left
- **S/↓** - Move down
- **D/→** - Move right

## PowerShell Script Features (Windows)

The PowerShell scripts provide enhanced functionality over batch files:

- **Better error handling** with detailed error messages
- **Prerequisite checking** (Git, CMake, SCons availability)
- **Colored output** for better readability
- **Progress indicators** and status messages
- **Build configuration options** (Debug/Release)
- **Automatic cleanup** options
- **Non-interactive mode** support with `-NoWait` parameter

**PowerShell Script Options:**

```powershell
# Basic setup
.\setup.ps1

# Basic build
.\build.ps1

# Build with specific configuration
.\build.ps1 -Configuration Release

# Clean build
.\build.ps1 -Clean

# Non-interactive mode (for CI/CD)
.\build.ps1 -NoWait
```

## Development Workflow

1. **Modify C++ Code:** Edit files in the `src/` directory
2. **Rebuild:** Run the build script for your platform
3. **Reload in Godot:** The extension will automatically reload
4. **Test:** Run the scene in Godot

## Extending the Game

### Adding New Classes

1. Create header (.h) and implementation (.cpp) files in `src/`
2. Register the class in `register_types.cpp`:
   ```cpp
   #include "your_class.h"
   // In initialize_game_module():
   ClassDB::register_class<YourClass>();
   ```
3. Rebuild the extension

### Scene Setup

- The main scene (`scenes/main.tscn`) contains a basic setup
- Attach your C++ classes as scripts to nodes
- Use Godot's editor to design levels and UI

## Troubleshooting

### Build Issues

- **CMake not found:** Ensure CMake is in your PATH
- **Compiler errors:** Check that you have a compatible C++ compiler
- **godot-cpp build fails:** Ensure SCons is installed

### Godot Issues

- **Extension not loading:** Check the GDExtension configuration file
- **Class not found:** Ensure the class is registered in `register_types.cpp`
- **Runtime errors:** Check Godot's debugger output

### Platform-Specific Notes

**Windows:**
- Requires Visual Studio 2022 or compatible compiler
- Use x64 Native Tools Command Prompt for best results
- **PowerShell Execution Policy:** If you get execution policy errors, run:
  ```powershell
  Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
  ```

**Linux:**
- Install development packages: `sudo apt-get install build-essential`
- May need to install additional libraries depending on your distribution

**macOS:**
- Install Xcode Command Line Tools: `xcode-select --install`
- Universal binary support included

## Next Steps

- Add sprites and animations to the player
- Implement enemies and collision detection
- Add sound effects and music
- Create multiple levels/scenes
- Implement UI elements (health, score display)
- Add game mechanics (collectibles, power-ups)

## Resources

- [Godot Documentation](https://docs.godotengine.org/)
- [GDExtension Documentation](https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/)
- [Godot C++ Bindings](https://github.com/godotengine/godot-cpp)
- [CMake Documentation](https://cmake.org/documentation/)
