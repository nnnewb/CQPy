# CQPy

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

在酷Q目录（有`CQP.exe`文件的目录）下创建`cqpy.py`文件，内容如下：

```python
import _embed

def on_enable():
    _embed.cq_add_log(embed.get_auth_code(), 10, "py", "Hello world!")
    return 0
```

在酷Q里启用插件，即可看到日志里输出了一行`Hello world!`。

提供的事件回调如下：

```python
# 生命周期回调

def on_enable() -> int:
    return 0

def on_disable() -> int:
    return 0

# 消息事件

def on_private_msg(sub_type: int, msg_id: int, from_qq: int, msg: bytes, font: int) -> int:
    return 0

def on_group_msg(sub_type: int, msg_id: int, from_group: int, from_qq: int, from_anonymous_base64: bytes, msg: bytes, font: int) -> int:
    return 0

def on_discuss_msg(sub_type: int, msg_id: int, from_discuss: int, from_qq: int, msg: bytes, font: int) -> int:
    return 0

# 群组事件

def on_group_upload(sub_type: int, send_time: int, from_group: int, from_qq: int, file_base64: bytes) -> int:
    return 0

def on_group_admin(sub_type: int, send_time: int, from_group: int, being_operate_qq: int) -> int:
    return 0

def on_group_member_decrease(sub_type: int, send_time: int, from_group: int, being_operate_qq: int) -> int:
    return 0

def on_group_member_increase(sub_type: int, send_time: int, from_group: int, being_operate_qq: int) -> int:
    return 0

def on_group_ban(sub_type: int, send_time: int, from_group: int, from_qq: int, being_operate_qq: int, duration: int) -> int:
    return 0

# 通知事件

def on_friend_add(sub_type: int, send_time: int, from_qq: int) -> int:
    return 0

# 请求

def on_friend_request(sub_type: int, send_time: int, from_qq: int, msg: bytes, response_flag: bytes) -> int:
    return 0

def on_group_request(sub_type: int, send_time: int, from_group: int, from_qq: int, msg: bytes, response_flag: bytes) -> int:
    return 0

```

`_embed`模块提供的接口如下：

```python
# internal
def get_auth_code(auth_code: int) -> int: ...

# Message
def cq_send_private_msg(auth_code: int, qq: int, msg: bytes) -> int: ...
def cq_send_group_msg(auth_code: int,group_id:int,msg:bytes) -> int: ...
def cq_send_discuss_msg(auth_code: int,discuss_id:int,msg:bytes) -> int: ...
def cq_delete_msg(auth_code: int,msg_id:int) -> int: ...

# friend operation
def cq_send_like(auth_code: int, qq:int) -> int: ...
def cq_send_like_v2(auth_code: int, qq:int) -> int: ...

# group operation
def cq_set_group_kick(auth_code: int, group_id:int, qq:int, reject_add_request: int) -> int: ...
def cq_set_group_ban(auth_code: int, group_id: int, qq: int, duration: int) -> int: ...
def cq_set_group_anonymous_ban(auth_code: int, group_id: int, anonymous: bytes, duration: int) -> int: ...
def cq_set_group_whole_ban(auth_code: int, group_id: int, enable: int) -> int: ...
def cq_set_group_admin(auth_code: int, group_id: int, qq: int, set: int) -> int: ...
def cq_set_group_anonymous(auth_code: int, group_id: int, enable: int) -> int: ...
def cq_set_group_card(auth_code: int, group_id: int, qq: int, new_card: bytes) -> int: ...
def cq_set_group_leave(auth_code: int, group_id: int, is_dismiss: int) -> int: ...
def cq_set_group_special_title(auth_code: int, group_id: int, qq: int, new_special_title: bytes, duration: int) -> int: ...
def cq_set_discuss_leave(auth_code: int, discuss_id: int) -> int: ...

# request
def cq_set_friend_add_request(auth_code: int, response_flag: bytes, response_operation: int, remark: bytes) -> int: ...
def cq_set_group_add_request(auth_code: int, response_flag: bytes, request_type: int, response_operation: int) -> int: ...
def cq_set_group_add_request_v2(auth_code: int, response_flag: bytes, request_type: int, response_operation: int, reason: bytes) -> int: ...

# QQ Information
def cq_get_login_qq(auth_code: int) -> int: ...
def cq_get_login_nick(auth_code: int) -> bytes: ...
def cq_get_stranger_info(auth_code: int, qq: int, no_cache: int) -> bytes: ...
def cq_get_friend_list(auth_code: int, reserved: int) -> bytes: ...
def cq_get_group_list(auth_code: int) -> bytes: ...
def cq_get_group_info(auth_code: int, group_id: int, no_cache: int) -> bytes: ...
def cq_get_group_member_list(auth_code: int, group_id: int) -> bytes: ...
def cq_get_group_member_info_v2(auth_code: int, group_id: int, qq: int, no_cache: int) -> bytes: ...

# CoolQ
def cq_get_cookies(auth_code: int) -> bytes: ...
def cq_get_cookies_v2(auth_code: int, domain: bytes) -> bytes: ...
def cq_get_csrf_token(auth_code: int) -> int: ...
def cq_get_app_directory(auth_code: int) -> bytes: ...
def cq_get_record(auth_code: int, file: bytes, out_format: bytes) -> bytes: ...
def cq_get_record_v2(auth_code: int, file: bytes, out_format: bytes) -> bytes: ...
def cq_get_image(auth_code: int, file: bytes) -> bytes: ...
def cq_can_send_image(auth_code: int) -> int: ...
def cq_can_send_record(auth_code: int) -> int: ...
def cq_add_log(auth_code: int, level: int, category: bytes, log_msg: bytes) -> int: ...
def cq_set_fatal(auth_code: int, error_info: bytes) -> int: ...
def cq_set_restart(auth_code: int) -> int: ...
```


## Build

准备工作：启用酷Q的开发模式。

1. 把 `script/install.ps1`里的路径改成你的酷Q安装路径。
2. 把 `CMakeLists.txt` 中 `add_definitions(-DAPP_ID="top.weak-ptr.cqpy" -DNOMINMAX)` 的 `top.weak-ptr.cqpy` 改为你的应用ID
3. 把 `app.json` 中 `name`、`author`、`description` 改为你的应用信息。
4. 执行下面的命令

```batch
cd /path/to/CQPy
mkdir build
cd build
cmake .. -AWin32 -DCMAKE_TOOLCHAIN_FILE=/path/to/your/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build .
```

完成后即可在`酷Q Pro\dev\你的AppID\`下看到`app.dll`和`app.json`两个文件了。

## special thanks

特别感谢 @richardchien 大佬的 cqcppsdk，因为没找到 酷Q 的 C++ api 文档，所以很大程度上借(<kbd>ctrl</kbd>+<kbd>c</kbd>)鉴(<kbd>ctrl</kbd>+<kbd>v</kbd>)了 richardchien 的代码，稍加我自己喜好的风格润色。

## LICENSE

以 GPL-v3 协议开放源代码。
