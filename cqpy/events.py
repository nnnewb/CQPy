import traceback
from enum import Enum
from logging import getLogger
from typing import Callable, Any, Mapping, List

from cqpy import cqp

logger = getLogger(__name__)


class EventType(Enum):
    Enable = 100
    Disable = 101

    PrivateMessage = 201
    GroupMessage = 202
    DiscussMessage = 203

    GroupUpload = 301
    GroupAdmin = 302
    GroupMemberDecrease = 303
    GroupMemberIncrease = 304
    GroupBan = 305

    FriendAdd = 401

    FriendRequest = 501
    GroupRequest = 502


class Event(object):

    def __init__(self, event_type: EventType, **event_args):
        self.event_args: dict = event_args
        self.event_type = event_type
        self.propagate = True


callback_registry: Mapping[EventType, List] = {}


def dispatch(event: Event):
    cqp.add_log(0, __name__, f'python 模块收到事件 {event.event_type.name}')
    callbacks = callback_registry.get(event.event_type, [])
    try:
        for fn, priority in callbacks:
            cqp.add_log(0, __name__, f'调用事件处理函数 {fn}')
            fn(event)
            if not event.propagate:
                break
    except Exception:
        logger.exception('在处理事件时发生异常')
        cqp.add_log(20, __name__, f'处理事件时发生异常\n{traceback.format_exc()}')
        return -1
    return 0


def on(event_type: EventType, priority: int = 1000):
    def wrapper(fn: Callable[[Event], Any]):
        callback_registry.setdefault(event_type, [])
        callback_registry[event_type].append((fn, priority))
        callback_registry[event_type].sort(key=lambda t: t[1], reverse=True)
        return fn

    return wrapper
