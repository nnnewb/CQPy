$projectDir = Split-Path $PSScriptRoot -Parent

$appId = "top.weak-ptr.cqpy"
$coolqRoot = "C:\Users\weakptr\AppData\Roaming\酷Q Pro"
# $appOutDir = "${ProjectDir}\out\build\x86-Debug\"
$appOutDir = "${ProjectDir}\build\Debug\"

$coolqAppDevDir = "$coolqRoot\dev\$appId"
$dllName = "${appId}.dll"
$dllPath = "$appOutDir\$dllName"
$jsonName = "app.json"
$jsonPath = "$projectDir\$jsonName"

$cqpyPackage = "$coolqRoot\data\app\$appId\cqpy"
Write-Host "从数据目录删除 cqpy 库 $cqpyPackage"
Remove-Item -Force -Recurse $cqpyPackage -ErrorAction SilentlyContinue
Write-Host "删除完毕" -ForegroundColor Green

Write-Host "复制 cqpy 到数据目录 $cqpyPackage"
Copy-Item -Recurse -Force "$projectDir\cqpy" $cqpyPackage
Write-Host "复制完毕" -ForegroundColor Green

Write-Host "复制构建文件到酷Q 目录 ${coolqAppDevDir}"
New-Item -Path $coolqAppDevDir -ItemType Directory -ErrorAction SilentlyContinue
Copy-Item -Force $dllPath "$coolqAppDevDir\app.dll"
Copy-Item -Force $jsonPath "$coolqAppDevDir\$jsonName"
Write-Host "复制完成" -ForegroundColor Green