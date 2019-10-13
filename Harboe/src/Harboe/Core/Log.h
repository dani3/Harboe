#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

// Core log macros
#define HB_CORE_TRACE(...)      ::Harboe::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HB_CORE_INFO(...)       ::Harboe::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HB_CORE_WARN(...)       ::Harboe::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HB_CORE_ERROR(...)      ::Harboe::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HB_CORE_FATAL(...)      ::Harboe::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define HB_TRACE(...)           ::Harboe::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HB_INFO(...)            ::Harboe::Log::GetClientLogger()->info(__VA_ARGS__)
#define HB_WARN(...)            ::Harboe::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HB_ERROR(...)           ::Harboe::Log::GetClientLogger()->error(__VA_ARGS__)
#define HB_FATAL(...)           ::Harboe::Log::GetClientLogger()->fatal(__VA_ARGS__)

namespace Harboe
{
	class HARBOE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}