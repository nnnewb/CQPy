#include <cstdint>
#include <functional>
#include <pybind11/embed.h>

#include "api.hpp"

namespace py = pybind11;

#ifdef _MSC_VER
#define CQPY_API(ReturnType, CQ_API_FUNC, ...) \
    m.def(#CQ_API_FUNC, std::function<ReturnType __stdcall(__VA_ARGS__)>(CQ_##CQ_API_FUNC))
#else
#define CQPY_API(ReturnType, CQ_API_FUNC, ...) \
    m.def(#CQ_API_FUNC, std::function<ReturnType(__VA_ARGS__)>(CQ##CQ_API_FUNC))
#endif

PYBIND11_EMBEDDED_MODULE(CQP, m) {
    m.attr("APP_ID") = py::bytes(APP_ID);
    m.attr("AUTH_CODE") = nullptr;

    // Message
    CQPY_API(int32_t, sendPrivateMsg, int32_t auth_code, int64_t qq, const char *msg);
    CQPY_API(int32_t, sendGroupMsg, int32_t auth_code, int64_t group_id, const char *msg);
    CQPY_API(int32_t, sendDiscussMsg, int32_t auth_code, int64_t discuss_id, const char *msg);
    CQPY_API(int32_t, deleteMsg, int32_t auth_code, int64_t msg_id);

    // Friend Operation
    CQPY_API(int32_t, sendLike, int32_t auth_code, int64_t qq);
    CQPY_API(int32_t, sendLikeV2, int32_t auth_code, int64_t qq, int32_t times);

    // Group Operation
    CQPY_API(int32_t, setGroupKick, int32_t auth_code, int64_t group_id, int64_t qq, cq_bool_t reject_add_request);
    CQPY_API(int32_t, setGroupBan, int32_t auth_code, int64_t group_id, int64_t qq, int64_t duration);
    CQPY_API(int32_t, setGroupAnonymousBan, int32_t auth_code, int64_t group_id, const char *anonymous, int64_t duration);
    CQPY_API(int32_t, setGroupWholeBan, int32_t auth_code, int64_t group_id, cq_bool_t enable);
    CQPY_API(int32_t, setGroupAdmin, int32_t auth_code, int64_t group_id, int64_t qq, cq_bool_t set);
    CQPY_API(int32_t, setGroupAnonymous, int32_t auth_code, int64_t group_id, cq_bool_t enable);
    CQPY_API(int32_t, setGroupCard, int32_t auth_code, int64_t group_id, int64_t qq, const char *new_card);
    CQPY_API(int32_t, setGroupLeave, int32_t auth_code, int64_t group_id, cq_bool_t is_dismiss);
    CQPY_API(int32_t, setGroupSpecialTitle, int32_t auth_code, int64_t group_id, int64_t qq, const char *new_special_title, int64_t duration);
    CQPY_API(int32_t, setDiscussLeave, int32_t auth_code, int64_t discuss_id);

    // Request
    CQPY_API(int32_t, setFriendAddRequest, int32_t auth_code, const char *response_flag, int32_t response_operation, const char *remark);
    CQPY_API(int32_t, setGroupAddRequest, int32_t auth_code, const char *response_flag, int32_t request_type, int32_t response_operation);
    CQPY_API(int32_t, setGroupAddRequestV2, int32_t auth_code, const char *response_flag, int32_t request_type, int32_t response_operation, const char *reason);

    // QQ Information
    CQPY_API(int64_t, getLoginQQ, int32_t auth_code);
    // NOTE:
    // Some C/C++ function that return const char* or std::string will been assume as return an utf-8 string and caused UnicodeDecodeError.
    // So I add explicit type conversion for those function to avoid it.
    m.def("getLoginNick", [](int32_t auth_code) { return py::bytes(CQ_getLoginNick(auth_code)); });
    m.def("getStrangerInfo", [](int32_t auth_code, int64_t qq, cq_bool_t no_cache) { return py::bytes(CQ_getStrangerInfo(auth_code, qq, no_cache)); });
    m.def("getFriendList", [](int32_t auth_code, cq_bool_t reserved) { return py::bytes(CQ_getFriendList(auth_code, reserved)); });
    m.def("getGroupList", [](int32_t auth_code) { return py::bytes(CQ_getGroupList(auth_code)); });
    m.def("getGroupInfo", [](int32_t auth_code, int64_t group_id, cq_bool_t no_cache) { return py::bytes(CQ_getGroupInfo(auth_code, group_id, no_cache)); });
    m.def("getGroupMemberList", [](int32_t auth_code, int64_t group_id) { return py::bytes(CQ_getGroupMemberList(auth_code, group_id)); });
    m.def("getGroupMemberInfoV2", [](int32_t auth_code, int64_t group_id, int64_t qq, cq_bool_t no_cache) { return py::bytes(CQ_getGroupMemberInfoV2(auth_code, group_id, qq, no_cache)); });

    // CoolQ
    m.def("getCookies", [](int32_t auth_code) { return py::bytes(CQ_getCookies(auth_code)); });
    m.def("getCookiesV2", [](int32_t auth_code, const char *domain) { return py::bytes(CQ_getCookiesV2(auth_code, domain)); });
    CQPY_API(int32_t, getCsrfToken, int32_t auth_code);
    m.def("getAppDirectory", [](int32_t auth_code) { return py::bytes(CQ_getAppDirectory(auth_code)); });
    m.def("getRecord", [](int32_t auth_code, const char *file, const char *out_format) { return py::bytes(CQ_getRecord(auth_code, file, out_format)); });
    m.def("getRecordV2", [](int32_t auth_code, const char *file, const char *out_format) { return py::bytes(CQ_getRecordV2(auth_code, file, out_format)); });
    m.def("getImage", [](int32_t auth_code, const char *file) { return py::bytes(CQ_getImage(auth_code, file)); });
    CQPY_API(int, canSendImage, int32_t auth_code);
    CQPY_API(int, canSendRecord, int32_t auth_code);
    CQPY_API(int32_t, addLog, int32_t auth_code, int32_t log_level, const char *category, const char *log_msg);
    CQPY_API(int32_t, setFatal, int32_t auth_code, const char *error_info);
    CQPY_API(int32_t, setRestart, int32_t auth_code); // currently ineffective;
}