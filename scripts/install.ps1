$projectDir = Split-Path $PSScriptRoot -Parent

$appId = "top.weak-ptr.cqpy"
$coolqRoot = "C:\Users\weakptr\AppData\Roaming\酷Q Pro"
$appOutDir = "${ProjectDir}\build"

$coolqAppDevDir = "$coolqRoot\dev\$appId"
$dllName = "${appId}.dll"
$dllPath = "$appOutDir\$dllName"
$jsonName = "app.json"
$jsonPath = "$projectDir\$jsonName"

Write-Host "复制文件到酷Q开发目录 ${coolqAppDevDir}"
New-Item -Path $coolqAppDevDir -ItemType Directory -ErrorAction SilentlyContinue
Copy-Item -Force $dllPath "$coolqAppDevDir\app.dll"
Copy-Item -Force $jsonPath "$coolqAppDevDir\$jsonName"
Write-Host "复制完成" -ForegroundColor Green