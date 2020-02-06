import struct
from dataclasses import dataclass
from enum import Enum
from typing import Type

from cqpy import cqp


class BinPack(object):
    """ 处理酷Q传递的二进制数据的工具类
    """

    def __init__(self, buf: bytes) -> None:
        cqp.add_log(0, __name__, f'buf size {len(buf)}')
        self.buffer = buf
        self.offset = 0

    def pop_int16(self) -> int:
        cqp.add_log(0, __name__, f'pop buf {self.buffer[self.offset:self.offset + 2]}')
        ret, = struct.unpack_from('!h', self.buffer, self.offset)
        self.offset += 2
        return ret

    def pop_int32(self) -> int:
        cqp.add_log(0, __name__, f'pop buf {self.buffer[self.offset:self.offset + 4]}')
        ret, = struct.unpack_from('!i', self.buffer, self.offset)
        self.offset += 4
        return ret

    def pop_int64(self) -> int:
        cqp.add_log(0, __name__, f'pop buf {self.buffer[self.offset:self.offset + 8]}')
        ret, = struct.unpack_from('!q', self.buffer, self.offset)
        self.offset += 8
        return ret

    def pop_str(self) -> str:
        """ pop binary string from BinPack buffer

        binary format:

            ...[2bytes len][len bytes string(gb18030 encoded)]...
        """
        length = self.pop_int16()
        str_buf = self.buffer[self.offset:self.offset + length]
        self.offset += length
        return str_buf.decode('gb18030')

    def pop_bool(self) -> bool:
        return bool(self.pop_int32())

    def pop_token(self) -> bytes:
        length = self.pop_int16()
        token_buf = self.buffer[self.offset:self.offset + length]
        self.offset += length
        return token_buf

    def pop_bytes(self, size: int):
        buf = self.buffer[self.offset:self.offset + size]
        self.offset += size
        return buf

    def to_object(self, cls: Type):
        if hasattr(cls, '_bin_pack'):
            kwargs = {}
            fmt = getattr(cls, '_bin_pack')
            for name, tp in fmt:
                if tp is long:
                    kwargs[name] = self.pop_int64()
                elif tp is int:
                    kwargs[name] = self.pop_int32()
                elif tp is str:
                    kwargs[name] = self.pop_str()
                elif tp is bytes:
                    kwargs[name] = self.pop_token()
                elif tp is bool:
                    kwargs[name] = self.pop_bool()
                elif tp is Enum or Enum in tp.__mro__:
                    kwargs[name] = tp(self.pop_int32())
                cqp.add_log(0, __name__, f'pop field {name} of type {tp}, value {kwargs[name]}')
            return cls(**kwargs)
        raise ValueError(f'不可反序列化的类型{cls}，类定义中不包含 _bin_pack 字段。')

    def to_multi_object(self, cls: Type):
        ret = []
        count = self.pop_int32()
        for _ in range(count):
            buf = self.pop_token()
            obj = BinPack(buf).to_object(cls)
            ret.append(obj)
        return ret


class long(int):
    """ dummy class """
    pass


class GroupRole(Enum):
    Member = 1
    Admin = 2
    Owner = 3


class Gender(Enum):
    Male = 0
    Female = 1
    Unknown = 255


@dataclass
class GroupInfo(object):
    group_id: long
    name: str
    member_count: int
    max_member_count: int

    _bin_pack = [
        ('group_id', long),
        ('name', str),
        ('member_count', int),
        ('max_member_count', int),
    ]


@dataclass
class ListedGroupInfo(object):
    group_id: long
    name: str

    _bin_pack = [
        ('group_id', long),
        ('name', str),
    ]


@dataclass
class AnonymousInfo(object):
    id: long
    nickname: str
    token: str

    _bin_pack = [
        ('id', long),
        ('nickname', str),
        ('token', str),
    ]


@dataclass
class UserInfo(object):
    user_id: long
    nickname: str
    gender: Gender
    age: int

    _bin_pack = [
        ('user_id', long),
        ('nickname', str),
        ('gender', Gender),
        ('age', int),
    ]


@dataclass
class FriendInfo(object):
    user_id: long
    nickname: str
    remark: str

    _bin_pack = [
        ('user_id', long),
        ('nickname', str),
        ('remark', str),
    ]


@dataclass
class GroupMemberInfo(object):
    group_id: long
    user_id: long
    nickname: str
    card: str
    gender: Gender
    age: int
    area: str
    join_time: int
    last_sent_time: int
    level: str
    role: GroupRole
    unfriendly: bool
    title: str
    title_expire_time: int
    card_changeable: bool

    _bin_pack = [
        ("group_id", long),
        ("user_id", long),
        ("nickname", str),
        ("card", str),
        ("gender", Gender),
        ("age", int),
        ("area", str),
        ("join_time", int),
        ("last_sent_time", int),
        ("level", str),
        ("role", GroupRole),
        ("unfriendly", bool),
        ("title", str),
        ("title_expire_time", int),
        ("card_changeable", bool),
    ]


@dataclass
class FileInfo(object):
    id: long
    name: str
    size: long
    busize: long

    _bin_pack = [
        ('id', long),
        ('name', str),
        ('size', long),
        ('busize', long),
    ]
