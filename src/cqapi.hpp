#pragma once
#include <Windows.h>
#include <cstdint>
#include <functional>

#define CQ_API(ReturnType, FuncName, ...)                                                             \
    extern "C" __declspec(dllimport) typedef ReturnType(__stdcall *__CQ_##FuncName##_T)(__VA_ARGS__); \
    __CQ_##FuncName##_T CQ_##FuncName;                                                                \
    static bool __CQ_API_##FuncName##_REGISTERED = add_initializer([](auto dll) {                     \
        CQ_##FuncName = reinterpret_cast<__CQ_##FuncName##_T>(GetProcAddress(dll, "CQ_" #FuncName));  \
    });

#define CQ_API_DECLARE(ReturnType, FuncName, ...) \
    extern ReturnType(__stdcall *CQ_##FuncName)(__VA_ARGS__);

using cq_bool_t = int32_t;

extern int32_t AUTH_CODE;

bool add_initializer(std::function<void(HMODULE)> fn);
void cqapi_initialize();

// Message
CQ_API_DECLARE(int32_t, sendPrivateMsg, int32_t auth_code, int64_t qq, const char *msg)
CQ_API_DECLARE(int32_t, sendGroupMsg, int32_t auth_code, int64_t group_id, const char *msg)
CQ_API_DECLARE(int32_t, sendDiscussMsg, int32_t auth_code, int64_t discuss_id, const char *msg)
CQ_API_DECLARE(int32_t, deleteMsg, int32_t auth_code, int64_t msg_id)

// Friend Operation
CQ_API_DECLARE(int32_t, sendLike, int32_t auth_code, int64_t qq)
CQ_API_DECLARE(int32_t, sendLikeV2, int32_t auth_code, int64_t qq, int32_t times)

// Group Operation
CQ_API_DECLARE(int32_t, setGroupKick, int32_t auth_code, int64_t group_id, int64_t qq, cq_bool_t reject_add_request)
CQ_API_DECLARE(int32_t, setGroupBan, int32_t auth_code, int64_t group_id, int64_t qq, int64_t duration)
CQ_API_DECLARE(int32_t, setGroupAnonymousBan, int32_t auth_code, int64_t group_id, const char *anonymous, int64_t duration)
CQ_API_DECLARE(int32_t, setGroupWholeBan, int32_t auth_code, int64_t group_id, cq_bool_t enable)
CQ_API_DECLARE(int32_t, setGroupAdmin, int32_t auth_code, int64_t group_id, int64_t qq, cq_bool_t set)
CQ_API_DECLARE(int32_t, setGroupAnonymous, int32_t auth_code, int64_t group_id, cq_bool_t enable)
CQ_API_DECLARE(int32_t, setGroupCard, int32_t auth_code, int64_t group_id, int64_t qq, const char *new_card)
CQ_API_DECLARE(int32_t, setGroupLeave, int32_t auth_code, int64_t group_id, cq_bool_t is_dismiss)
CQ_API_DECLARE(int32_t, setGroupSpecialTitle, int32_t auth_code, int64_t group_id, int64_t qq, const char *new_special_title, int64_t duration)
CQ_API_DECLARE(int32_t, setDiscussLeave, int32_t auth_code, int64_t discuss_id)

// Request
CQ_API_DECLARE(int32_t, setFriendAddRequest, int32_t auth_code, const char *response_flag, int32_t response_operation, const char *remark)
CQ_API_DECLARE(int32_t, setGroupAddRequest, int32_t auth_code, const char *response_flag, int32_t request_type, int32_t response_operation)
CQ_API_DECLARE(int32_t, setGroupAddRequestV2, int32_t auth_code, const char *response_flag, int32_t request_type, int32_t response_operation, const char *reason)

// QQ Information
CQ_API_DECLARE(int64_t, getLoginQQ, int32_t auth_code)
CQ_API_DECLARE(const char *, getLoginNick, int32_t auth_code)
CQ_API_DECLARE(const char *, getStrangerInfo, int32_t auth_code, int64_t qq, cq_bool_t no_cache)
CQ_API_DECLARE(const char *, getFriendList, int32_t auth_code, cq_bool_t reserved)
CQ_API_DECLARE(const char *, getGroupList, int32_t auth_code)
CQ_API_DECLARE(const char *, getGroupInfo, int32_t auth_code, int64_t group_id, cq_bool_t no_cache)
CQ_API_DECLARE(const char *, getGroupMemberList, int32_t auth_code, int64_t group_id)
CQ_API_DECLARE(const char *, getGroupMemberInfoV2, int32_t auth_code, int64_t group_id, int64_t qq, cq_bool_t no_cache)

// CoolQ
CQ_API_DECLARE(const char *, getCookies, int32_t auth_code)
CQ_API_DECLARE(const char *, getCookiesV2, int32_t auth_code, const char *domain)
CQ_API_DECLARE(int32_t, getCsrfToken, int32_t auth_code)
CQ_API_DECLARE(const char *, getAppDirectory, int32_t auth_code)
CQ_API_DECLARE(const char *, getRecord, int32_t auth_code, const char *file, const char *out_format)
CQ_API_DECLARE(const char *, getRecordV2, int32_t auth_code, const char *file, const char *out_format)
CQ_API_DECLARE(const char *, getImage, int32_t auth_code, const char *file)
CQ_API_DECLARE(int, canSendImage, int32_t auth_code)
CQ_API_DECLARE(int, canSendRecord, int32_t auth_code)
CQ_API_DECLARE(int32_t, addLog, int32_t auth_code, int32_t log_level, const char *category, const char *log_msg)
CQ_API_DECLARE(int32_t, setFatal, int32_t auth_code, const char *error_info)
CQ_API_DECLARE(int32_t, setRestart, int32_t auth_code) // currently ineffective
