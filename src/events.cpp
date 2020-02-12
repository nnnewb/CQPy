#include <Windows.h>
#include <mutex>
#include <pybind11/embed.h>

#include "api.hpp"
#include "logging.hpp"
#include "compatible.hpp"

namespace py = pybind11;
using namespace cqpy;

static std::mutex lock{};

template <typename... Args>
inline int32_t py_callback(const std::string &py_func, Args... args) {
    auto guard = std::lock_guard(lock);

    try {
        auto m = py::module::import("cqpy._callback");
        return m.attr(py_func.c_str())(args...).template cast<int32_t>();
    } catch (const py::error_already_set &e) {
        logging::error(e.what());
        return -1;
    }
}

#pragma region LifeCycle

// 返回 API 版本和 App ID
CQ_EXPORT(const char *, AppInfo, 0) { return "9," APP_ID; }

// 初始化
CQ_EXPORT(int32_t, Initialize, 4, int32_t auth_code) {
    AUTH_CODE = auth_code;
    cqapi_initialize();
    return 0;
}

// 启用插件
CQ_EXPORT(int32_t, cq_event_enable, 0) {
    py::initialize_interpreter();
    // 设置 AUTH_CODE，但是暂时还不能使用酷Q的API
    auto CQP = py::module::import("CQP");
    CQP.attr("AUTH_CODE") = AUTH_CODE;
    // 初始化 Python 解释器环境，把数据目录加入 python path
    auto raw_app_dir = std::string(CQ_getAppDirectory(AUTH_CODE));
    auto app_dir =
        py::bytes(raw_app_dir).attr("decode")("gb18030").cast<py::str>();
    auto sys = py::module::import("sys");
    sys.attr("path").attr("append")(app_dir);
    // 初始化完成
    logging::info("Python interpreter initialized.");
    return py_callback("on_enable");
}

// 禁用插件
CQ_EXPORT(int32_t, cq_event_disable, 0) {
    logging::info("Interpreter has exited.");
    auto result = py_callback("on_disable");
    py::finalize_interpreter();
    return result;
}

// 酷Q启动
CQ_EXPORT(int32_t, cq_event_coolq_start, 0) { return 0; }

// 酷Q退出
CQ_EXPORT(int32_t, cq_event_coolq_exit, 0) { return 0; }

#pragma endregion

#pragma region Message

/**
 * Type=21 私聊消息
 * sub_type 子类型，11/来自好友 1/来自在线状态 2/来自群 3/来自讨论组
 */
CQ_EXPORT(int32_t, cq_event_private_message, 24, int32_t sub_type, int32_t msg_id, int64_t from_qq, const char *msg, int32_t font) {
    return py_callback("on_private_msg", sub_type, msg_id, from_qq, py::bytes(msg), font);
}

/**
 * Type=2 群消息
 */
CQ_EXPORT(int32_t, cq_event_group_message, 36, int32_t sub_type, int32_t msg_id, int64_t from_group, int64_t from_qq, const char *from_anonymous_base64, const char *msg, int32_t font) {
    return py_callback("on_group_msg", sub_type, msg_id, from_group, from_qq, py::bytes(from_anonymous_base64), py::bytes(msg), font);
}

/**
 * Type=4 讨论组消息
 */
CQ_EXPORT(int32_t, cq_event_discuss_message, 32, int32_t sub_type, int32_t msg_id, int64_t from_discuss, int64_t from_qq, const char *msg, int32_t font) {
    return py_callback("on_discuss_msg", sub_type, msg_id, from_discuss, from_qq, py::bytes(msg), font);
}

#pragma endregion

#pragma region GroupManagement

/**
 * Type=11 群事件-文件上传
 */
CQ_EXPORT(int32_t, cq_event_group_upload, 28, int32_t sub_type, int32_t send_time, int64_t from_group, int64_t from_qq, const char *file_base64) {
    return py_callback("on_group_upload", sub_type, send_time, from_group, from_qq, py::bytes(file_base64));
}

/**
 * Type=101 群事件-管理员变动
 * sub_type 子类型，1/被取消管理员 2/被设置管理员
 */
CQ_EXPORT(int32_t, cq_event_group_admin, 24, int32_t sub_type, int32_t send_time, int64_t from_group, int64_t being_operate_qq) {
    return py_callback("on_group_admin", sub_type, send_time, from_group, being_operate_qq);
}

/**
 * Type=102 群事件-群成员减少
 * sub_type 子类型，1/群员离开 2/群员被踢 3/自己(即登录号)被踢
 * from_qq 操作者QQ(仅subType为2、3时存在)
 * being_operate_qq 被操作QQ
 */
CQ_EXPORT(int32_t, cq_event_group_member_decrease, 32, int32_t sub_type, int32_t send_time, int64_t from_group, int64_t from_qq, int64_t being_operate_qq) {
    return py_callback("on_group_member_decrease", sub_type, send_time, from_group, from_qq, being_operate_qq);
}

/**
 * Type=103 群事件-群成员增加
 * sub_type 子类型，1/管理员已同意 2/管理员邀请
 * from_qq 操作者QQ(即管理员QQ)
 * being_operate_qq 被操作QQ(即加群的QQ)
 */
CQ_EXPORT(int32_t, cq_event_group_member_increase, 32, int32_t sub_type, int32_t send_time, int64_t from_group, int64_t from_qq, int64_t being_operate_qq) {
    return py_callback("on_group_member_increase", sub_type, send_time, from_group, from_qq, being_operate_qq);
}

/**
 * Type=104 群事件-群禁言
 * sub_type 子类型，1/被解禁 2/被禁言
 * from_group 来源群号
 * from_qq 操作者QQ(即管理员QQ)
 * being_operate_qq 被操作QQ(若为全群禁言/解禁，则本参数为 0)
 * duration 禁言时长(单位 秒，仅子类型为2时可用)
 */
CQ_EXPORT(int32_t, cq_event_group_ban, 40, int32_t sub_type, int32_t send_time, int64_t from_group, int64_t from_qq, int64_t being_operate_qq, int64_t duration) {
    return py_callback("on_group_ban", sub_type, send_time, from_group, from_qq, being_operate_qq, duration);
}

#pragma endregion

#pragma region Notice

/**
 * Type=201 好友事件-好友添加
 */
CQ_EXPORT(int32_t, cq_event_friend_add, 16, int32_t sub_type, int32_t send_time, int64_t from_qq) {
    return py_callback("on_friend_add", sub_type, send_time, from_qq);
}

#pragma endregion

#pragma region Request

/**
 * Type=301 请求-好友添加
 * msg 附言
 * response_flag 反馈标识(处理请求用)
 */
CQ_EXPORT(int32_t, cq_event_friend_request, 24, int32_t sub_type, int32_t send_time, int64_t from_qq, const char *msg, const char *response_flag) {
    return py_callback("on_friend_request", sub_type, send_time, from_qq, py::bytes(msg), py::bytes(response_flag));
}

/**
 * Type=302 请求-群添加
 * sub_type 子类型，1/他人申请入群 2/自己(即登录号)受邀入群
 * msg 附言
 * response_flag 反馈标识(处理请求用)
 */
CQ_EXPORT(int32_t, cq_event_group_request, 32, int32_t sub_type, int32_t send_time, int64_t from_group, int64_t from_qq, const char *msg, const char *response_flag) {
    return py_callback("on_group_request", sub_type, send_time, from_group, from_qq, py::bytes(msg), py::bytes(response_flag));
}

#pragma endregion
