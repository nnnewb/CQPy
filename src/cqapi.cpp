#include "cqapi.hpp"
#include <vector>
#include <functional>

/**
 * 本文件用于定义 CQP.dll 提供的 API, 参数类型和参数名保持与酷Q原生一致.
 */

int32_t AUTH_CODE;

static std::vector<std::function<void(HMODULE)>> initializers;

bool add_initializer(std::function<void(HMODULE)> fn)
{
    initializers.push_back(fn);
    return true;
}
void cqapi_initialize()
{
    const auto dll = GetModuleHandleW(L"CQP.dll");

    for (auto initializer : initializers)
    {
        initializer(dll);
    }
}

// Message
CQ_API(int32_t, sendPrivateMsg, int32_t auth_code, int64_t qq, const char *msg)
CQ_API(int32_t, sendGroupMsg, int32_t auth_code, int64_t group_id, const char *msg)
CQ_API(int32_t, sendDiscussMsg, int32_t auth_code, int64_t discuss_id, const char *msg)
CQ_API(int32_t, deleteMsg, int32_t auth_code, int64_t msg_id)

// Friend Operation
CQ_API(int32_t, sendLike, int32_t auth_code, int64_t qq)
CQ_API(int32_t, sendLikeV2, int32_t auth_code, int64_t qq, int32_t times)

// Group Operation
CQ_API(int32_t, setGroupKick, int32_t auth_code, int64_t group_id, int64_t qq, cq_bool_t reject_add_request)
CQ_API(int32_t, setGroupBan, int32_t auth_code, int64_t group_id, int64_t qq, int64_t duration)
CQ_API(int32_t, setGroupAnonymousBan, int32_t auth_code, int64_t group_id, const char *anonymous, int64_t duration)
CQ_API(int32_t, setGroupWholeBan, int32_t auth_code, int64_t group_id, cq_bool_t enable)
CQ_API(int32_t, setGroupAdmin, int32_t auth_code, int64_t group_id, int64_t qq, cq_bool_t set)
CQ_API(int32_t, setGroupAnonymous, int32_t auth_code, int64_t group_id, cq_bool_t enable)
CQ_API(int32_t, setGroupCard, int32_t auth_code, int64_t group_id, int64_t qq, const char *new_card)
CQ_API(int32_t, setGroupLeave, int32_t auth_code, int64_t group_id, cq_bool_t is_dismiss)
CQ_API(int32_t, setGroupSpecialTitle, int32_t auth_code, int64_t group_id, int64_t qq, const char *new_special_title, int64_t duration)
CQ_API(int32_t, setDiscussLeave, int32_t auth_code, int64_t discuss_id)

// Request
CQ_API(int32_t, setFriendAddRequest, int32_t auth_code, const char *response_flag, int32_t response_operation, const char *remark)
CQ_API(int32_t, setGroupAddRequest, int32_t auth_code, const char *response_flag, int32_t request_type, int32_t response_operation)
CQ_API(int32_t, setGroupAddRequestV2, int32_t auth_code, const char *response_flag, int32_t request_type, int32_t response_operation, const char *reason)

// QQ Information
CQ_API(int64_t, getLoginQQ, int32_t auth_code)
CQ_API(const char *, getLoginNick, int32_t auth_code)
CQ_API(const char *, getStrangerInfo, int32_t auth_code, int64_t qq, cq_bool_t no_cache)
CQ_API(const char *, getFriendList, int32_t auth_code, cq_bool_t reserved)
CQ_API(const char *, getGroupList, int32_t auth_code)
CQ_API(const char *, getGroupInfo, int32_t auth_code, int64_t group_id, cq_bool_t no_cache)
CQ_API(const char *, getGroupMemberList, int32_t auth_code, int64_t group_id)
CQ_API(const char *, getGroupMemberInfoV2, int32_t auth_code, int64_t group_id, int64_t qq, cq_bool_t no_cache)

// CoolQ
CQ_API(const char *, getCookies, int32_t auth_code)
CQ_API(const char *, getCookiesV2, int32_t auth_code, const char *domain)
CQ_API(int32_t, getCsrfToken, int32_t auth_code)
CQ_API(const char *, getAppDirectory, int32_t auth_code)
CQ_API(const char *, getRecord, int32_t auth_code, const char *file, const char *out_format)
CQ_API(const char *, getRecordV2, int32_t auth_code, const char *file, const char *out_format)
CQ_API(const char *, getImage, int32_t auth_code, const char *file)
CQ_API(int, canSendImage, int32_t auth_code)
CQ_API(int, canSendRecord, int32_t auth_code)
CQ_API(int32_t, addLog, int32_t auth_code, int32_t log_level, const char *category, const char *log_msg)
CQ_API(int32_t, setFatal, int32_t auth_code, const char *error_info)
CQ_API(int32_t, setRestart, int32_t auth_code) // currently ineffective
