$projectDir = Split-Path $PSScriptRoot -Parent

$coolqRoot = "C:\Users\weakptr\AppData\Roaming\酷Q Pro" # 修改为你的酷Q目录
$appId = "top.weak-ptr.frejya"  # 你的 App ID
$appOutDir = "${ProjectDir}\build"

$coolqAppDevDir = "$coolqRoot\dev\$appId"
$dllName = "${appId}.dll"
$dllPath = "$appOutDir\$dllName"
$jsonName = "app.json"
$jsonPath = "$projectDir\$jsonName"

Write-Host "正在拷贝插件到酷Q应用目录……"
New-Item -Path $coolqAppDevDir -ItemType Directory -ErrorAction SilentlyContinue
Copy-Item -Force $dllPath "$coolqAppDevDir\app.dll"
Copy-Item -Force $jsonPath "$coolqAppDevDir\$jsonName"
Write-Host "拷贝完成" -ForegroundColor Green