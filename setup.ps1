# Godot Game Development Environment Setup Script
# PowerShell version for Windows

param(
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
    Write-Status "Setting up Godot Game Development Environment..."
    Write-Host ""

    # Check if git is available
    if (-not (Get-Command git -ErrorAction SilentlyContinue)) {
        Write-Error "Git is not installed or not in PATH. Please install Git first."
        if (-not $NoWait) { Read-Host "Press Enter to exit" }
        exit 1
    }

    # Check if scons is available
    if (-not (Get-Command scons -ErrorAction SilentlyContinue)) {
        Write-Error "SCons is not installed or not in PATH. Please install SCons first:"
        Write-Host "  pip install scons" -ForegroundColor Yellow
        if (-not $NoWait) { Read-Host "Press Enter to exit" }
        exit 1
    }

    Write-Status "Cloning godot-cpp..."
    
    # Check if godot-cpp already exists
    if (Test-Path "godot-cpp") {
        Write-Host "godot-cpp directory already exists. Updating..." -ForegroundColor Yellow
        Set-Location "godot-cpp"
        git fetch origin
        git checkout 4.4
        git pull origin 4.4
        Set-Location ".."
    } else {
        git submodule add -b 4.4 https://github.com/godotengine/godot-cpp
        if ($LASTEXITCODE -ne 0) {
            Write-Error "Failed to clone godot-cpp repository!"
            if (-not $NoWait) { Read-Host "Press Enter to exit" }
            exit 1
        }
    }
    
    git submodule update --init --recursive
    if ($LASTEXITCODE -ne 0) {
        Write-Error "Failed to update submodules!"
        if (-not $NoWait) { Read-Host "Press Enter to exit" }
        exit 1
    }

    Write-Status "Creating necessary directories..."
    $directories = @("bin", "bin\win64", "bin\linux", "bin\macos")
    foreach ($dir in $directories) {
        if (-not (Test-Path $dir)) {
            New-Item -ItemType Directory -Path $dir -Force | Out-Null
            Write-Host "Created directory: $dir" -ForegroundColor Gray
        }
    }

    Write-Status "Building godot-cpp..."
    Set-Location "godot-cpp"
    
    # Build godot-cpp with error handling
    $sconsArgs = "platform=windows", "target=template_debug", "dev_build=yes"
    Write-Host "Running: scons $($sconsArgs -join ' ')" -ForegroundColor Gray
    
    & scons $sconsArgs
    if ($LASTEXITCODE -ne 0) {
        Write-Error "Failed to build godot-cpp!"
        Set-Location ".."
        if (-not $NoWait) { Read-Host "Press Enter to exit" }
        exit 1
    }

    Set-Location ".."
    Write-Success "Setup completed successfully!"
    Write-Host ""
    Write-Host "Next steps:" -ForegroundColor Yellow
    Write-Host "  1. Run build.ps1 to build the game extension" -ForegroundColor White
    Write-Host "  2. Open project.godot in Godot 4.4+" -ForegroundColor White
    Write-Host ""

} catch {
    Write-Error "An error occurred during setup: $($_.Exception.Message)"
    if (-not $NoWait) { Read-Host "Press Enter to exit" }
    exit 1
}

if (-not $NoWait) {
    Read-Host "Press Enter to continue"
}
