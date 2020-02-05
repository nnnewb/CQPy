# CQPy

> 非常早期的开发状态，不要用。欢迎参与开发。

轻量级的酷Q Python插件，支持运行指定的 Python 模块。

## requirements

首先你需要一个`Visual Studio 2019`和`CMake`，然后我推荐使用vcpkg来安装相关依赖。

依赖项：

- `pybind11`

安装方式：

```batch
vcpkg install pybind11:x86-windows
```

## Usage

> SDK 还在 WIP 的状态，需要做基础的 Python 封装才比较方便使用(字符串解码、base64解码、json解码、回调注册)，欢迎提 PR。

食用方法参考`cqpy.tutorial`。

设置例子：

```json
{
    "master": 12345,  // 你的 qq 号
    "virtualenv": "C:/Users/weakptr/.virtualenvs/frejya",  // 如果有使用 virtualenv ，也需要填写 virtualenv 路径
    "extras": [
        "C:/Users/weakptr/Documents/GitHub/frejya" // 额外的python包搜索路径，会添加到 sys.path中
    ],
    "plugins": [
        ""  // 你的python包名或模块名
    ]
}
```

## Build

准备工作：启用酷Q的开发模式。

```batch
cd /path/to/CQPy
mkdir build
cd build
cmake .. \
    "-GVisual Studio 16 2019" \
    -AWin32 \
    -DCMAKE_TOOLCHAIN_FILE=/path/to/your/vcpkg/scripts/buildsystems/vcpkg.cmake \
    -DCMAKE_INSTALL_PREFIX=酷Q安装路径
cmake --build .
cmake install
```

`cmake install`会做下面两件事：

1. 复制`app.dll`和`app.json`到`酷Q Pro\dev\top.weak-ptr.cqpy`下。
2. 复制`cqpy`到`酷Q Pro\data\app\top.weak-ptr.cqpy\`下。

## TODO && Contribute

目前还有下面的工作没有做

1. 在我的电脑上还有比较频繁的崩溃发生，需要更多测试和调试
2. Python 接口(`cqpy.cqp`和`cqpy.events`)要进一步封装简化（主要是以base64返回、传递参数的部分）

## special thanks

特别感谢 @richardchien 大佬的 cqcppsdk，因为没找到 酷Q 的 C++ api 文档，所以很大程度上借(<kbd>ctrl</kbd>+<kbd>c</kbd>)鉴(<kbd>ctrl</kbd>+<kbd>v</kbd>)了 richardchien 的代码，稍加我自己喜好的风格润色。

## LICENSE

以 GPL-v3 协议开放源代码。
