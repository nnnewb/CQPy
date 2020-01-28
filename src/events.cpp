#include "events.hpp"
#include "cqapi.hpp"

#pragma region LifeCycle

// 返回 API 版本和 App ID
CQ_EVENT(const char *, AppInfo, 0)
{
    return "9," APP_ID;
}

// 初始化
CQ_EVENT(int32_t, Initialize, 4, int32_t auth_code)
{
    AUTH_CODE = auth_code;
    cqapi_initialize();
    return 0;
}

// 启用插件
CQ_EVENT(int32_t, cq_event_enable, 0)
{
    CQ_addLog(AUTH_CODE, 10, "Log", "Hello world");
    return 0;
}

// 禁用插件
CQ_EVENT(int32_t, cq_event_disable, 0)
{
    return 0;
}

// 酷Q启动
CQ_EVENT(int32_t, cq_event_coolq_start, 0)
{
    return 0;
}

// 酷Q退出
CQ_EVENT(int32_t, cq_event_coolq_exit, 0)
{
    return 0;
}

#pragma endregion

#pragma region Message

/**
 * Type=21 私聊消息
 * sub_type 子类型，11/来自好友 1/来自在线状态 2/来自群 3/来自讨论组
 */
CQ_EVENT(int32_t, cq_event_private_message, 24, int32_t sub_type, int32_t msg_id, int64_t from_qq, const char *msg, int32_t font)
{
    return 0;
}

/**
 * Type=2 群消息
 */
CQ_EVENT(int32_t, cq_event_group_message, 36, int32_t sub_type, int32_t msg_id, int64_t from_group, int64_t from_qq, const char *from_anonymous_base64, const char *msg, int32_t font)
{
    return 0;
}

/**
 * Type=4 讨论组消息
 */
CQ_EVENT(int32_t, cq_event_discuss_message, 32, int32_t sub_type, int32_t msg_id, int64_t from_discuss, int64_t from_qq, const char *msg, int32_t font)
{
    return 0;
}

#pragma endregion

#pragma region GroupManagement

/**
 * Type=11 群事件-文件上传
 */
CQ_EVENT(int32_t, cq_event_group_upload, 28, int32_t sub_type, int32_t send_time, int64_t from_group, int64_t from_qq, const char *file_base64)
{
    return 0;
}

/**
 * Type=101 群事件-管理员变动
 * sub_type 子类型，1/被取消管理员 2/被设置管理员
 */
CQ_EVENT(int32_t, cq_event_group_admin, 24, int32_t sub_type, int32_t send_time, int64_t from_group, int64_t being_operate_qq)
{
    return 0;
}

/**
 * Type=102 群事件-群成员减少
 * sub_type 子类型，1/群员离开 2/群员被踢 3/自己(即登录号)被踢
 * from_qq 操作者QQ(仅subType为2、3时存在)
 * being_operate_qq 被操作QQ
 */
CQ_EVENT(int32_t, cq_event_group_member_decrease, 32, int32_t sub_type, int32_t send_time, int64_t from_group, int64_t from_qq, int64_t being_operate_qq)
{
    return 0;
}

/**
 * Type=103 群事件-群成员增加
 * sub_type 子类型，1/管理员已同意 2/管理员邀请
 * from_qq 操作者QQ(即管理员QQ)
 * being_operate_qq 被操作QQ(即加群的QQ)
 */
CQ_EVENT(int32_t, cq_event_group_member_increase, 32, int32_t sub_type, int32_t send_time, int64_t from_group, int64_t from_qq, int64_t being_operate_qq)
{
    return 0;
}

/**
 * Type=104 群事件-群禁言
 * sub_type 子类型，1/被解禁 2/被禁言
 * from_group 来源群号
 * from_qq 操作者QQ(即管理员QQ)
 * being_operate_qq 被操作QQ(若为全群禁言/解禁，则本参数为 0)
 * duration 禁言时长(单位 秒，仅子类型为2时可用)
 */
CQ_EVENT(int32_t, cq_event_group_ban, 40, int32_t sub_type, int32_t send_time, int64_t from_group, int64_t from_qq, int64_t being_operate_qq, int64_t duration)
{
    return 0;
}

#pragma endregion

#pragma region Notice

/**
 * Type=201 好友事件-好友添加
 */
CQ_EVENT(int32_t, cq_event_friend_add, 16, int32_t sub_type, int32_t send_time, int64_t from_qq)
{
    return 0;
}

#pragma endregion

#pragma region Request

/**
 * Type=301 请求-好友添加
 * msg 附言
 * response_flag 反馈标识(处理请求用)
 */
CQ_EVENT(int32_t, cq_event_friend_request, 24, int32_t sub_type, int32_t send_time, int64_t from_qq, const char *msg, const char *response_flag)
{
    return 0;
}

/**
 * Type=302 请求-群添加
 * sub_type 子类型，1/他人申请入群 2/自己(即登录号)受邀入群
 * msg 附言
 * response_flag 反馈标识(处理请求用)
 */
CQ_EVENT(int32_t, cq_event_group_request, 32, int32_t sub_type, int32_t send_time, int64_t from_group, int64_t from_qq, const char *msg, const char *response_flag)
{
    return 0;
}

#pragma endregion
