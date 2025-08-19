# Godot Game Extension Build Script
# PowerShell version for Windows

param(
    [ValidateSet("Debug", "Release")]
    [string]$Configuration = "Debug",
    [string]$Generator = "Visual Studio 17 2022",
    [string]$Architecture = "x64",
    [switch]$Clean = $false,
    [switch]$NoWait = $false
)

function Write-Status {
    param([string]$Message)
    Write-Host $Message -ForegroundColor Cyan
}

function Write-Success {
    param([string]$Message)
    Write-Host $Message -ForegroundColor Green
}

function Write-Error {
    param([string]$Message)
    Write-Host $Message -ForegroundColor Red
}

try {
    Write-Status "Building Godot Game Extension..."
    Write-Host "Configuration: $Configuration" -ForegroundColor Gray
    Write-Host "Generator: $Generator" -ForegroundColor Gray
    Write-Host "Architecture: $Architecture" -ForegroundColor Gray
    Write-Host ""

    # Check if CMake is available
    if (-not (Get-Command cmake -ErrorAction SilentlyContinue)) {
        Write-Error "CMake is not installed or not in PATH. Please install CMake first."
        if (-not $NoWait) { Read-Host "Press Enter to exit" }
        exit 1
    }

    # Check if godot-cpp is built
    $godotCppLib = "godot-cpp\bin\libgodot-cpp.windows.template_debug.dev.x86_64.lib"
    if (-not (Test-Path $godotCppLib)) {
        Write-Error "godot-cpp library not found at: $godotCppLib"
        Write-Host "Please run setup.ps1 first to build godot-cpp" -ForegroundColor Yellow
        if (-not $NoWait) { Read-Host "Press Enter to exit" }
        exit 1
    }

    # Clean build directory if requested
    if ($Clean -and (Test-Path "build")) {
        Write-Status "Cleaning build directory..."
        Remove-Item "build" -Recurse -Force
    }

    # Create build directory
    if (-not (Test-Path "build")) {
        New-Item -ItemType Directory -Path "build" -Force | Out-Null
        Write-Host "Created build directory" -ForegroundColor Gray
    }

    Set-Location "build"

    Write-Status "Configuring with CMake..."
    $cmakeConfigArgs = @(
        "..",
        "-G", $Generator,
        "-A", $Architecture
    )
    
    Write-Host "Running: cmake $($cmakeConfigArgs -join ' ')" -ForegroundColor Gray
    & cmake $cmakeConfigArgs
    
    if ($LASTEXITCODE -ne 0) {
        Write-Error "CMake configuration failed!"
        Set-Location ".."
        if (-not $NoWait) { Read-Host "Press Enter to exit" }
        exit 1
    }

    Write-Status "Building extension..."
    $cmakeBuildArgs = @(
        "--build", ".",
        "--config", $Configuration
    )
    
    Write-Host "Running: cmake $($cmakeBuildArgs -join ' ')" -ForegroundColor Gray
    & cmake $cmakeBuildArgs
    
    if ($LASTEXITCODE -ne 0) {
        Write-Error "Build failed!"
        Set-Location ".."
        if (-not $NoWait) { Read-Host "Press Enter to exit" }
        exit 1
    }

    Set-Location ".."
    
    # Check if the output file was created
    $outputPath = "bin\win64"
    if (Test-Path $outputPath) {
        $builtFiles = Get-ChildItem $outputPath -Filter "*.dll" | Measure-Object
        if ($builtFiles.Count -gt 0) {
            Write-Success "Build completed successfully!"
            Write-Host ""
            Write-Host "Output files in: $outputPath" -ForegroundColor Gray
            Get-ChildItem $outputPath -Filter "*.dll" | ForEach-Object {
                Write-Host "  $($_.Name)" -ForegroundColor White
            }
        } else {
            Write-Error "Build completed but no DLL files found in $outputPath"
        }
    } else {
        Write-Error "Output directory not found: $outputPath"
    }

    Write-Host ""
    Write-Host "Next steps:" -ForegroundColor Yellow
    Write-Host "  1. Open project.godot in Godot 4.4+" -ForegroundColor White
    Write-Host "  2. The extension should load automatically" -ForegroundColor White
    Write-Host ""

} catch {
    if (Get-Location | Where-Object { $_.Path.EndsWith("build") }) {
        Set-Location ".."
    }
    Write-Error "An error occurred during build: $($_.Exception.Message)"
    if (-not $NoWait) { Read-Host "Press Enter to exit" }
    exit 1
}

if (-not $NoWait) {
    Read-Host "Press Enter to continue"
}
