#include <cstdint>
#include <functional>
#include <pybind11/embed.h>

#include "api.hpp"

namespace py = pybind11;

PYBIND11_EMBEDDED_MODULE(CQP, m) {
    m.attr("APP_ID") = py::bytes(APP_ID);
    m.attr("AUTH_CODE") = nullptr;
    // Message
    CQPY_API(int32_t, CQ_sendPrivateMsg, int32_t auth_code, int64_t qq, const char *msg);
    CQPY_API(int32_t, CQ_sendGroupMsg, int32_t auth_code, int64_t group_id, const char *msg);
    CQPY_API(int32_t, CQ_sendDiscussMsg, int32_t auth_code, int64_t discuss_id, const char *msg);
    CQPY_API(int32_t, CQ_deleteMsg, int32_t auth_code, int64_t msg_id);

    // Friend Operation
    CQPY_API(int32_t, CQ_sendLike, int32_t auth_code, int64_t qq);
    CQPY_API(int32_t, CQ_sendLikeV2, int32_t auth_code, int64_t qq, int32_t times);

    // Group Operation
    CQPY_API(int32_t, CQ_setGroupKick, int32_t auth_code, int64_t group_id, int64_t qq, cq_bool_t reject_add_request);
    CQPY_API(int32_t, CQ_setGroupBan, int32_t auth_code, int64_t group_id, int64_t qq, int64_t duration);
    CQPY_API(int32_t, CQ_setGroupAnonymousBan, int32_t auth_code, int64_t group_id, const char *anonymous, int64_t duration);
    CQPY_API(int32_t, CQ_setGroupWholeBan, int32_t auth_code, int64_t group_id, cq_bool_t enable);
    CQPY_API(int32_t, CQ_setGroupAdmin, int32_t auth_code, int64_t group_id, int64_t qq, cq_bool_t set);
    CQPY_API(int32_t, CQ_setGroupAnonymous, int32_t auth_code, int64_t group_id, cq_bool_t enable);
    CQPY_API(int32_t, CQ_setGroupCard, int32_t auth_code, int64_t group_id, int64_t qq, const char *new_card);
    CQPY_API(int32_t, CQ_setGroupLeave, int32_t auth_code, int64_t group_id, cq_bool_t is_dismiss);
    CQPY_API(int32_t, CQ_setGroupSpecialTitle, int32_t auth_code, int64_t group_id, int64_t qq, const char *new_special_title, int64_t duration);
    CQPY_API(int32_t, CQ_setDiscussLeave, int32_t auth_code, int64_t discuss_id);

    // Request
    CQPY_API(int32_t, CQ_setFriendAddRequest, int32_t auth_code, const char *response_flag, int32_t response_operation, const char *remark);
    CQPY_API(int32_t, CQ_setGroupAddRequest, int32_t auth_code, const char *response_flag, int32_t request_type, int32_t response_operation);
    CQPY_API(int32_t, CQ_setGroupAddRequestV2, int32_t auth_code, const char *response_flag, int32_t request_type, int32_t response_operation, const char *reason);

    // QQ Information
    CQPY_API(int64_t, CQ_getLoginQQ, int32_t auth_code);
    m.def("cq_get_login_nick", [](int32_t auth_code) { return py::bytes(CQ_getLoginNick(auth_code)); });
    m.def("cq_get_stranger_info", [](int32_t auth_code, int64_t qq, cq_bool_t no_cache) { return py::bytes(CQ_getStrangerInfo(auth_code, qq, no_cache)); });
    m.def("cq_get_friend_list", [](int32_t auth_code, cq_bool_t reserved) { return py::bytes(CQ_getFriendList(auth_code, reserved)); });
    m.def("cq_get_group_list", [](int32_t auth_code) { return py::bytes(CQ_getGroupList(auth_code)); });
    m.def("cq_get_group_info", [](int32_t auth_code, int64_t group_id, cq_bool_t no_cache) { return py::bytes(CQ_getGroupInfo(auth_code, group_id, no_cache)); });
    m.def("cq_get_group_member_list", [](int32_t auth_code, int64_t group_id) { return py::bytes(CQ_getGroupMemberList(auth_code, group_id)); });
    m.def("cq_get_group_member_info_v2", [](int32_t auth_code, int64_t group_id, int64_t qq, cq_bool_t no_cache) { return py::bytes(CQ_getGroupMemberInfoV2(auth_code, group_id, qq, no_cache)); });

    // CoolQ
    m.def("cq_get_cookies", [](int32_t auth_code) { return py::bytes(CQ_getCookies(auth_code)); });
    m.def("cq_get_cookies_v2", [](int32_t auth_code, const char *domain) { return py::bytes(CQ_getCookiesV2(auth_code, domain)); });
    CQPY_API(int32_t, CQ_getCsrfToken, int32_t auth_code);
    m.def("cq_get_app_directory", [](int32_t auth_code) { return py::bytes(CQ_getAppDirectory(auth_code)); });
    m.def("cq_get_record", [](int32_t auth_code, const char *file, const char *out_format) { return py::bytes(CQ_getRecord(auth_code, file, out_format)); });
    m.def("cq_get_record_v2", [](int32_t auth_code, const char *file, const char *out_format) { return py::bytes(CQ_getRecordV2(auth_code, file, out_format)); });
    m.def("cq_get_image", [](int32_t auth_code, const char *file) { return py::bytes(CQ_getImage(auth_code, file)); });
    CQPY_API(int, CQ_canSendImage, int32_t auth_code);
    CQPY_API(int, CQ_canSendRecord, int32_t auth_code);
    CQPY_API(int32_t, CQ_addLog, int32_t auth_code, int32_t log_level, const char *category, const char *log_msg);
    CQPY_API(int32_t, CQ_setFatal, int32_t auth_code, const char *error_info);
    CQPY_API(int32_t, CQ_setRestart, int32_t auth_code); // currently ineffective;
}