$projectDir = Split-Path $PSScriptRoot -Parent

$coolqRoot = "C:\Users\weakptr\AppData\Roaming\��Q Pro" # �޸�Ϊ��Ŀ�QĿ¼
$appId = "top.weak-ptr.cqpy"  # ��� App ID
$appOutDir = "${ProjectDir}\build"

$coolqAppDevDir = "$coolqRoot\dev\$appId"
$dllName = "${appId}.dll"
$dllPath = "$appOutDir\$dllName"
$jsonName = "app.json"
$jsonPath = "$projectDir\$jsonName"

Write-Host "���ڿ����������QӦ��Ŀ¼����"
New-Item -Path $coolqAppDevDir -ItemType Directory -ErrorAction SilentlyContinue
Copy-Item -Force $dllPath "$coolqAppDevDir\app.dll"
Copy-Item -Force $jsonPath "$coolqAppDevDir\$jsonName"
Write-Host "�������" -ForegroundColor Green