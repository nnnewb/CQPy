from cqpy.events import dispatch, Event, EventType
# 生命周期回调


def on_enable() -> int:
    return dispatch(Event(EventType.Enable))


def on_disable() -> int:
    return dispatch(Event(EventType.Disable))

# 消息事件


def on_private_msg(sub_type: int, msg_id: int, from_qq: int, msg: bytes, font: int) -> int:
    return dispatch(
        Event(
            EventType.PrivateMessage,
            sub_type=sub_type,
            msg_id=msg_id,
            from_qq=from_qq,
            msg=msg.decode('gb18030'),
            font=font,
        )
    )


def on_group_msg(sub_type: int, msg_id: int, from_group: int, from_qq: int, from_anonymous_base64: bytes, msg: bytes, font: int) -> int:
    return dispatch(
        Event(
            EventType.GroupMessage,
            sub_type=sub_type,
            msg_id=msg_id,
            from_group=from_group,
            from_qq=from_qq,
            from_anonymous_base64=from_anonymous_base64.decode('gb18030'),
            msg=msg.decode('gb18030'),
            font=font,
        )
    )


def on_discuss_msg(sub_type: int, msg_id: int, from_discuss: int, from_qq: int, msg: bytes, font: int) -> int:
    return dispatch(
        Event(
            EventType.DiscussMessage,
            msg_id=msg_id,
            from_discuss=from_discuss,
            from_qq=from_qq,
            msg=msg.decode('gb18030'),
            font=font,
        )
    )

# 群组事件


def on_group_upload(sub_type: int, send_time: int, from_group: int, from_qq: int, file_base64: bytes) -> int:
    return dispatch(
        Event(
            EventType.GroupUpload,
            sub_type=sub_type,
            send_time=send_time,
            from_group=from_group,
            from_qq=from_qq,
            file_base64=file_base64.decode('gb18030'),
        )
    )


def on_group_admin(sub_type: int, send_time: int, from_group: int, being_operate_qq: int) -> int:
    return dispatch(
        Event(
            EventType.GroupAdmin,
            sub_type=sub_type,
            send_time=send_time,
            from_group=from_group,
            being_operate_qq=being_operate_qq,
        )
    )


def on_group_member_decrease(sub_type: int, send_time: int, from_group: int, being_operate_qq: int) -> int:
    return dispatch(
        Event(
            EventType.GroupMemberDecrease,
            sub_type=sub_type,
            send_time=send_time,
            from_group=from_group,
            being_operate_qq=being_operate_qq,
        )
    )


def on_group_member_increase(sub_type: int, send_time: int, from_group: int, being_operate_qq: int) -> int:
    return dispatch(
        Event(
            EventType.GroupMemberIncrease,
            sub_type=sub_type,
            send_time=send_time,
            from_group=from_group,
            being_operate_qq=being_operate_qq,
        )
    )


def on_group_ban(sub_type: int, send_time: int, from_group: int, from_qq: int, being_operate_qq: int, duration: int) -> int:
    return dispatch(
        Event(
            EventType.GroupBan,
            sub_type=sub_type,
            send_time=send_time,
            from_group=from_group,
            from_qq=from_qq,
            being_operate_qq=being_operate_qq,
            duration=duration,
        )
    )

# 通知事件


def on_friend_add(sub_type: int, send_time: int, from_qq: int) -> int:
    return dispatch(
        Event(
            EventType.FriendAdd,
            sub_type=sub_type,
            send_time=send_time,
            from_qq=from_qq,
        )
    )

# 请求


def on_friend_request(sub_type: int, send_time: int, from_qq: int, msg: bytes, response_flag: bytes) -> int:
    return dispatch(
        Event(
            EventType.FriendRequest,
            sub_type=sub_type,
            send_time=send_time,
            from_qq=from_qq,
            msg=msg.decode('gb18030'),
            response_flag=response_flag.decode('gb18030'),
        )
    )


def on_group_request(sub_type: int, send_time: int, from_group: int, from_qq: int, msg: bytes, response_flag: bytes) -> int:
    return dispatch(
        Event(
            EventType.GroupRequest,
            sub_type=sub_type,
            send_time=send_time,
            from_group=from_group,
            from_qq=from_qq,
            msg=msg.decode('gb18030'),
            response_flag=response_flag.decode('gb18030'),
        )
    )
