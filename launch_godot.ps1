# Launch Godot with the current project
# PowerShell script to easily open the project in Godot 4.4

$godotPath = "c:\Users\apastukhov\Godot\Godot_v4.4.1-stable_win64.exe"

Write-Host "Launching Godot 4.4 with project..." -ForegroundColor Cyan

if (Test-Path $godotPath) {
    Start-Process $godotPath -ArgumentList "--path", ".", "--editor"
    Write-Host "Godot launched successfully!" -ForegroundColor Green
} else {
    Write-Error "Godot not found at: $godotPath"
    Write-Host "Please check the Godot installation path." -ForegroundColor Yellow
}
