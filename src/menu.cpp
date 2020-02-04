#include <cstdint>
#include <filesystem>
#include <fstream>

#include <Windows.h>

#include "macro.hpp"
#include "cqapi.hpp"
#include "logging.hpp"

using namespace cqpy;

CQ_EXPORT(int32_t, open_settings, 0)
{
	auto settings_path = std::string(CQ_getAppDirectory(AUTH_CODE)) + "\\settings.json";
	if (!std::filesystem::exists(settings_path)) 
	{
		auto of = std::ofstream(settings_path);
		of << "{}" << std::endl;
		logging::debug("settings.json 不存在，现在创建。");
	}

	ShellExecute(nullptr, nullptr, settings_path.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
	return 0;
}
