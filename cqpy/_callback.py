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
