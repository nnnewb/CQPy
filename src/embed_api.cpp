#include <cstdint>
#include <functional>
#include <pybind11/embed.h>

#include "cqapi.hpp"

namespace py = pybind11;

PYBIND11_EMBEDDED_MODULE(_embed, m)
{
	m.attr("APP_ID") = py::bytes(APP_ID);
	m.attr("AUTH_CODE") = nullptr;
	// Message
	CQPY_API(int32_t, CQ_sendPrivateMsg, cq_send_private_msg, int32_t auth_code, int64_t qq, const char* msg);
	CQPY_API(int32_t, CQ_sendGroupMsg, cq_send_group_msg, int32_t auth_code, int64_t group_id, const char* msg);
	CQPY_API(int32_t, CQ_sendDiscussMsg, cq_send_discuss_msg, int32_t auth_code, int64_t discuss_id, const char* msg);
	CQPY_API(int32_t, CQ_deleteMsg, cq_delete_msg, int32_t auth_code, int64_t msg_id);

	// Friend Operation
	CQPY_API(int32_t, CQ_sendLike, cq_send_like, int32_t auth_code, int64_t qq);
	CQPY_API(int32_t, CQ_sendLikeV2, cq_send_like_v2, int32_t auth_code, int64_t qq, int32_t times);

	// Group Operation
	CQPY_API(int32_t, CQ_setGroupKick, cq_set_group_kick, int32_t auth_code, int64_t group_id, int64_t qq, cq_bool_t reject_add_request);
	CQPY_API(int32_t, CQ_setGroupBan, cq_set_group_ban, int32_t auth_code, int64_t group_id, int64_t qq, int64_t duration);
	CQPY_API(int32_t, CQ_setGroupAnonymousBan, cq_set_group_anonymous_ban, int32_t auth_code, int64_t group_id, const char* anonymous, int64_t duration);
	CQPY_API(int32_t, CQ_setGroupWholeBan, cq_set_group_whole_ban, int32_t auth_code, int64_t group_id, cq_bool_t enable);
	CQPY_API(int32_t, CQ_setGroupAdmin, cq_set_group_admin, int32_t auth_code, int64_t group_id, int64_t qq, cq_bool_t set);
	CQPY_API(int32_t, CQ_setGroupAnonymous, cq_set_group_anonymous, int32_t auth_code, int64_t group_id, cq_bool_t enable);
	CQPY_API(int32_t, CQ_setGroupCard, cq_set_group_card, int32_t auth_code, int64_t group_id, int64_t qq, const char* new_card);
	CQPY_API(int32_t, CQ_setGroupLeave, cq_set_group_leave, int32_t auth_code, int64_t group_id, cq_bool_t is_dismiss);
	CQPY_API(int32_t, CQ_setGroupSpecialTitle, cq_set_group_special_title, int32_t auth_code, int64_t group_id, int64_t qq, const char* new_special_title, int64_t duration);
	CQPY_API(int32_t, CQ_setDiscussLeave, cq_set_discuss_leave, int32_t auth_code, int64_t discuss_id);

	// Request
	CQPY_API(int32_t, CQ_setFriendAddRequest, cq_set_friend_add_request, int32_t auth_code, const char* response_flag, int32_t response_operation, const char* remark);
	CQPY_API(int32_t, CQ_setGroupAddRequest, cq_set_group_add_request, int32_t auth_code, const char* response_flag, int32_t request_type, int32_t response_operation);
	CQPY_API(int32_t, CQ_setGroupAddRequestV2, cq_set_group_add_request_v2, int32_t auth_code, const char* response_flag, int32_t request_type, int32_t response_operation, const char* reason);

	// QQ Information
	CQPY_API(int64_t, CQ_getLoginQQ, cq_get_login_qq, int32_t auth_code);
    //	CQPY_API(const char*, CQ_getLoginNick, cq_get_login_nick, int32_t auth_code);
    m.def("cq_get_login_nick", [](int32_t auth_code){
        return py::bytes(CQ_getLoginNick(auth_code));
    });
    //	CQPY_API(const char*, CQ_getStrangerInfo, cq_get_stranger_info, int32_t auth_code, int64_t qq, cq_bool_t no_cache);
    m.def("cq_get_stranger_info", [](int32_t auth_code, int64_t qq, cq_bool_t no_cache){
        return py::bytes(CQ_getStrangerInfo(auth_code, qq, no_cache));
    });
    //	CQPY_API(const char*, CQ_getFriendList, cq_get_friend_list, int32_t auth_code, cq_bool_t reserved);
    m.def("cq_get_friend_list", []( int32_t auth_code, cq_bool_t reserved){
        return py::bytes(CQ_getFriendList(auth_code, reserved));
    });
    //	CQPY_API(const char*, CQ_getGroupList, cq_get_group_list, int32_t auth_code);
    m.def("cq_get_group_list", []( int32_t auth_code){
        return py::bytes(CQ_getGroupList(auth_code))    ;
    });
    //	CQPY_API(const char*, CQ_getGroupInfo, cq_get_group_info, int32_t auth_code, int64_t group_id, cq_bool_t no_cache);
    m.def("cq_get_group_info",[](int32_t auth_code, int64_t group_id, cq_bool_t no_cache){
        return py::bytes(CQ_getGroupInfo(auth_code, group_id, no_cache));
    });
    //	CQPY_API(const char*, CQ_getGroupMemberList, cq_get_group_member_list, int32_t auth_code, int64_t group_id);
    m.def("cq_get_group_member_list", []( int32_t auth_code, int64_t group_id){
        return py::bytes(CQ_getGroupMemberList(auth_code, group_id));
    });
    //	CQPY_API(const char*, CQ_getGroupMemberInfoV2, cq_get_group_member_info_v2, int32_t auth_code, int64_t group_id, int64_t qq, cq_bool_t no_cache);
    m.def("cq_get_group_member_info_v2", [](int32_t auth_code, int64_t group_id, int64_t qq, cq_bool_t no_cache){
        return py::bytes(CQ_getGroupMemberInfoV2(auth_code, group_id, qq, no_cache));
    });

	// CoolQ
    //	CQPY_API(const char*, CQ_getCookies, cq_get_cookies, int32_t auth_code);
    m.def("cq_get_cookies", [](int32_t auth_code){
        return py::bytes(CQ_getCookies(auth_code));
    });
    //	CQPY_API(const char*, CQ_getCookiesV2, cq_get_cookies_v2, int32_t auth_code, const char* domain);
    m.def("cq_get_cookies_v2", [](int32_t auth_code,const char* domain){
        return py::bytes(CQ_getCookiesV2(auth_code,domain));
    });
	CQPY_API(int32_t, CQ_getCsrfToken, cq_get_csrf_token, int32_t auth_code);
    //	CQPY_API(const char*, CQ_getAppDirectory, cq_get_app_directory, int32_t auth_code);
    m.def("cq_get_app_directory", [](int32_t auth_code){
        return py::bytes(CQ_getAppDirectory(auth_code));
    });
    //	CQPY_API(const char*, CQ_getRecord, cq_get_record, int32_t auth_code, const char* file, const char* out_format);
    m.def("cq_get_record", [](int32_t auth_code, const char* file, const char* out_format){
        return py::bytes(CQ_getRecord(auth_code, file, out_format));
    });
    //	CQPY_API(const char*, CQ_getRecordV2, cq_get_record_v2, int32_t auth_code, const char* file, const char* out_format);
    m.def("cq_get_record_v2", [](int32_t auth_code, const char* file, const char* out_format){
        return py::bytes(CQ_getRecordV2(auth_code, file, out_format));
    });
    //	CQPY_API(const char*, CQ_getImage, cq_get_image, int32_t auth_code, const char* file);
    m.def("cq_get_image",[](int32_t auth_code, const char* file){
        return py::bytes(CQ_getImage(auth_code, file));
    });
	CQPY_API(int, CQ_canSendImage, cq_can_send_image, int32_t auth_code);
	CQPY_API(int, CQ_canSendRecord, cq_can_send_record, int32_t auth_code);
	CQPY_API(int32_t, CQ_addLog, cq_add_log, int32_t auth_code, int32_t log_level, const char* category, const char* log_msg);
	CQPY_API(int32_t, CQ_setFatal, cq_set_fatal, int32_t auth_code, const char* error_info);
	CQPY_API(int32_t, CQ_setRestart, cq_set_restart, int32_t auth_code); // currently ineffective;
}