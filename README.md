# CQPy

轻量级的酷Q Python插件，支持运行指定的 Python 模块。

<del>原本是这么想的...</del>

总之，现在是一个最简的酷Q API包装，基本什么都没有，可以随意往里面添加东西。

目前有的功能就是启用插件时写一句 Hello world。

## requirements

你需要安装一个 `Visual Studio 2019` 或者 `Visual C++ Build Tool`，以及`CMake`。

## Usage

1. 把 `script/install.ps1`里的路径改成你的酷Q安装路径。
2. `cmake . -B build`
3. `cmake --build build`

`app.json`同理，自己看着办吧。
