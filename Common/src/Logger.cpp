#include "pch.h"
#include "Logger.h"
#include "Config.h"

namespace Logger
{

path getLogsDirPath()
{
	return getWorkingDirPath() / "logs";
}

void init(string loggerName, bool truncate)
{
	Config::init(); // TODO: Remove
	if(config->log_level == "off")
		return;

	try
	{
		auto processName = getCurrentProcessPath().stem().string();
		auto fileName = fmt::format("{}.{}.log", loggerName, processName);
		auto path = getLogsDirPath() / fileName;

		logger = spdlog::basic_logger_mt(loggerName, path.wstring(), truncate);
		logger->set_pattern("[%H:%M:%S.%e] [%l]\t%v");
		logger->set_level(spdlog::level::from_str(config->log_level));
		logger->flush_on(spdlog::level::debug);
	} catch(const std::exception&)
	{
		// Now if we can't open log file, something must be really wrong, hence we exit.
		/*
		auto message = stow(string(ex.what()));
		MessageBox(NULL, message.c_str(), L"Failed to initialize the log file", MB_ICONERROR | MB_OK);
		exit(1);
		*/

		// EDIT:

		// Actually, it might be the case that multiple instances of the same process are launched
		// simultaneously. In this case it is very likely that they will fail at opening the file.
		// Example: QtWebEngineProcess.exe - issues ACCESS DENIED
	}
}

}

shared_ptr<spdlog::logger> logger = spdlog::null_logger_mt("null");

string errorCodeToString(const cpr::ErrorCode& errorCode) {
	switch (errorCode)
	{
	case cpr::ErrorCode::OK:
		return "OK";
	case cpr::ErrorCode::CONNECTION_FAILURE:
		return "Connection Failure";
	case cpr::ErrorCode::EMPTY_RESPONSE:
		return "Empty response";
	case cpr::ErrorCode::HOST_RESOLUTION_FAILURE:
		return "Host resolution failure";
	case cpr::ErrorCode::INTERNAL_ERROR:
		return "Internal error";
	case cpr::ErrorCode::INVALID_URL_FORMAT:
		return "Invalid url format";
	case cpr::ErrorCode::NETWORK_RECEIVE_ERROR:
		return "Network recieve error";
	case cpr::ErrorCode::NETWORK_SEND_FAILURE:
		return "Network send failure";
	case cpr::ErrorCode::OPERATION_TIMEDOUT:
		return "Operation timed out";
	case cpr::ErrorCode::PROXY_RESOLUTION_FAILURE:
		return "Proxy resolution failure";
	case cpr::ErrorCode::SSL_CONNECT_ERROR:
		return "SSL connect error";
	case cpr::ErrorCode::SSL_LOCAL_CERTIFICATE_ERROR:
		return "SSL local certificate error";
	case cpr::ErrorCode::SSL_REMOTE_CERTIFICATE_ERROR:
		return "SSL remote certificate error";
	case cpr::ErrorCode::SSL_CACERT_ERROR:
		return "SSL cacert error";
	case cpr::ErrorCode::GENERIC_SSL_ERROR:
		return "Generic SSL error";
	case cpr::ErrorCode::UNSUPPORTED_PROTOCOL:
		return "Unsupported protocol";
	case cpr::ErrorCode::REQUEST_CANCELLED:
		return "Request cancelled";
	case cpr::ErrorCode::TOO_MANY_REDIRECTS:
		return "Too many redirects";
	case cpr::ErrorCode::UNKNOWN_ERROR:
		return "Unknown error";
	default:
		return "Unknown enum value, check errorCodeToString function";
	}
}
