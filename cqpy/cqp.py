# _embed is special module embedding in top.weak-ptr.cqpy plugin
from base64 import b64decode
from typing import List

from cqpy.types import BinPack, GroupMemberInfo, GroupInfo, ListedGroupInfo, FriendInfo, UserInfo

try:
    import _embed
except ImportError:
    raise RuntimeError('CQPy only run within top.weak-ptr.cqpy CoolQ plugin.')

# internal
AUTH_CODE: int = _embed.AUTH_CODE
APP_ID: str = _embed.APP_ID.decode('gb18030')


# Message


def send_private_msg(qq: int, msg: str) -> int:
    return _embed.cq_send_private_msg(AUTH_CODE, qq, msg.encode('gb18030'))


def send_group_msg(group_id: int, msg: str) -> int:
    return _embed.cq_send_group_msg(AUTH_CODE, group_id, msg.encode('gb18030'))


def send_discuss_msg(discuss_id: int, msg: str) -> int:
    return _embed.cq_send_discuss_msg(AUTH_CODE, discuss_id, msg.encode('gb18030'))


def delete_msg(msg_id: int) -> int:
    return _embed.cq_delete_msg(AUTH_CODE, msg_id)


# friend operation


def send_like(qq: int) -> int:
    return _embed.cq_send_like(AUTH_CODE, qq)


def send_like_v2(qq: int) -> int:
    return _embed.cq_send_like_v2(AUTH_CODE, qq)


# group operation


def set_group_kick(group_id: int, qq: int, reject_add_request: int) -> int:
    return _embed.cq_set_group_kick(AUTH_CODE, group_id, qq, reject_add_request)


def set_group_ban(group_id: int, qq: int, duration: int) -> int:
    return _embed.cq_set_group_ban(AUTH_CODE, group_id, qq, duration)


def set_group_anonymous_ban(group_id: int, anonymous: str, duration: int) -> int:
    return _embed.cq_set_group_anonymous_ban(AUTH_CODE, group_id, anonymous.encode('gb18030'), duration)


def set_group_whole_ban(group_id: int, enable: int) -> int:
    return _embed.cq_set_group_whole_ban(AUTH_CODE, group_id, enable)


def set_group_admin(group_id: int, qq: int, set_: int) -> int:
    return _embed.cq_set_group_admin(AUTH_CODE, group_id, qq, set_)


def set_group_anonymous(group_id: int, enable: int) -> int:
    return _embed.cq_set_group_anonymous(AUTH_CODE, group_id, enable)


def set_group_card(group_id: int, qq: int, new_card: str) -> int:
    return _embed.cq_set_group_card(AUTH_CODE, group_id, qq, new_card.encode('utf-8'))


def set_group_leave(group_id: int, is_dismiss: int) -> int:
    return _embed.cq_set_group_leave(AUTH_CODE, group_id, is_dismiss)


def set_group_special_title(group_id: int, qq: int, new_special_title: str, duration: int) -> int:
    return _embed.cq_set_group_special_title(AUTH_CODE, group_id, qq, new_special_title.encode('gb18030'), duration)


def set_discuss_leave(discuss_id: int) -> int:
    return _embed.cq_set_discuss_leave(AUTH_CODE, discuss_id)


# request


def set_friend_add_request(response_flag: str, response_operation: int, remark: str) -> int:
    return _embed.cq_set_friend_add_request(response_flag.encode('gb18030'), response_operation,
                                            remark.encode('gb18030'))


def set_group_add_request(response_flag: str, request_type: int, response_operation: int) -> int:
    return _embed.cq_set_group_add_request(AUTH_CODE, response_flag.encode('gb18030'), request_type, response_operation)


def set_group_add_request_v2(response_flag: str, request_type: int, response_operation: int, reason: str) -> int:
    return _embed.cq_set_group_add_request_v2(AUTH_CODE, response_flag.encode('gb18030'), request_type,
                                              response_operation, reason.encode('gb18030'))


# QQ Information


def get_login_qq() -> int:
    return _embed.cq_get_login_qq(AUTH_CODE)


def get_login_nick() -> str:
    return _embed.cq_get_login_nick(AUTH_CODE).decode('gb18030')


def get_stranger_info(qq: int, no_cache: int) -> str:
    ret_buf = _embed.cq_get_stranger_info(AUTH_CODE, qq, no_cache).decode('gb18030')
    bin_pack = BinPack(b64decode(ret_buf))
    return bin_pack.to_object(UserInfo)


def get_friend_list(reserved: int) -> str:
    ret_buf = _embed.cq_get_friend_list(AUTH_CODE, reserved).decode('gb18030')
    bin_pack = BinPack(b64decode(ret_buf))
    return bin_pack.to_multi_object(FriendInfo)


def get_group_list() -> List[ListedGroupInfo]:
    ret_buf = _embed.cq_get_group_list(AUTH_CODE).decode('gb18030')
    bin_pack = BinPack(b64decode(ret_buf))
    return bin_pack.to_multi_object(ListedGroupInfo)


def get_group_info(group_id: int, no_cache: int) -> GroupInfo:
    ret_buf = _embed.cq_get_group_info(AUTH_CODE, group_id, no_cache).decode('gb18030')
    bin_pack = BinPack(b64decode(ret_buf))
    return bin_pack.to_object(GroupInfo)


def get_group_member_list(group_id: int) -> List[GroupMemberInfo]:
    ret_buf = _embed.cq_get_group_member_list(AUTH_CODE, group_id).decode('gb18030')
    bin_pack = BinPack(b64decode(ret_buf))
    return bin_pack.to_multi_object(GroupMemberInfo)


def get_group_member_info_v2(group_id: int, qq: int, no_cache: int) -> GroupMemberInfo:
    ret_buf = _embed.cq_get_group_member_info_v2(AUTH_CODE, group_id, qq, no_cache).decode('gb18030')
    bin_pack = BinPack(b64decode(ret_buf))
    return bin_pack.to_object(GroupMemberInfo)


# CoolQ


def get_cookies() -> str:
    return _embed.cq_get_cookies(AUTH_CODE).decode('gb18030')


def get_cookies_v2(domain: str) -> str:
    return _embed.cq_get_cookies_v2(AUTH_CODE, domain.encode('gb18030')).decode('gb18030')


def get_csrf_token() -> int:
    return _embed.cq_get_csrf_token(AUTH_CODE)


def get_app_directory() -> str:
    return _embed.cq_get_app_directory(AUTH_CODE).decode('gb18030')


def get_record(file: str, out_format: str) -> str:
    return _embed.cq_get_record(AUTH_CODE, file.encode('gb18030'), out_format.encode('gb18030')).decode('gb18030')


def get_record_v2(file: str, out_format: str) -> str:
    return _embed.cq_get_record_v2(AUTH_CODE, file.encode('gb18030'), out_format.encode('gb18030')).decode('gb18030')


def get_image(file: str) -> str:
    return _embed.cq_get_image(AUTH_CODE, file.encode('gb18030')).decode('gb18030')


def can_send_image() -> int:
    return _embed.cq_can_send_image(AUTH_CODE)


def can_send_record() -> int:
    return _embed.cq_can_send_record(AUTH_CODE)


def add_log(level: int, category: str, log_msg: str) -> int:
    return _embed.cq_add_log(AUTH_CODE, level, category.encode('gb18030'), log_msg.encode('gb18030'))


def set_fatal(error_info: str) -> int:
    return _embed.cq_set_fatal(AUTH_CODE, error_info.encode('gb18030'))


def set_restart() -> int:
    return _embed.cq_set_restart(AUTH_CODE)
