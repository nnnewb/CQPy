from cqpy.events import on, EventType, Event
from cqpy import settings, cqp


@on(EventType.Enable)
def on_enable(event: Event):
    """
    机器人上线 demo

    :param event:
    :return:
    """
    if 'master' in settings:
        cqp.send_private_msg(settings['master'], '我上线啦！')
    else:
        cqp.add_log(10, __name__, '在settings.json中添加 `"master": 你的qq号` ，即可在机器人上线时收到问候啦!')


REPEAT_MODE = False


@on(EventType.GroupMessage)
def on_group_message(event: Event):
    """
    复读机 demo

    :param event:
    :return:
    """
    global REPEAT_MODE

    if 'master' not in settings:
        cqp.add_log(10, __name__, '在settings.json中添加 `"master": 你的qq号` ，即可体验复读机的快乐。')

    if event.event_args['from_qq'] == settings['master'] and '复读开始' in event.event_args['msg']:
        REPEAT_MODE = True
        cqp.add_log(10, __name__, '复读开始！')
        cqp.send_group_msg(event.event_args['from_group'], '复读开始！')

    if REPEAT_MODE is True:
        cqp.send_group_msg(event.event_args['from_group'], event.event_args['msg'])
