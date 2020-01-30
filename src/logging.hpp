#pragma once

#include <fstream>
#include <string>
#include "cqapi.hpp"
#include <json/json.h>

namespace cqpy 
{
	namespace logging {
		enum Level {
			DEBUG = 0,
			INFO = 10,
			INFOSUCCESS = 11,
			INFORECV = 12,
			INFOSEND = 13,
			WARNING = 20,
			ERR = 30,
			FATAL = 40,
		};

		inline void debug(const std::string& msg)
		{
			CQ_addLog(AUTH_CODE, Level::DEBUG, APP_ID, msg.c_str());
		}

		inline void info(const std::string& msg)
		{
			CQ_addLog(AUTH_CODE, Level::INFO, APP_ID, msg.c_str());
		}

		inline void warning(const std::string& msg)
		{
			CQ_addLog(AUTH_CODE, Level::WARNING, APP_ID, msg.c_str());
		}

		inline void error(const std::string& msg)
		{
			CQ_addLog(AUTH_CODE, Level::ERR, APP_ID, msg.c_str());
		}

		inline void fatal(const std::string& msg)
		{
			CQ_addLog(AUTH_CODE, Level::FATAL, APP_ID, msg.c_str());
		}
	}
}
