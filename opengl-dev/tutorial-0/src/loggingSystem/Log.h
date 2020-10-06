#pragma once


#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace ggm
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger; }
		
	private:
		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;
		
	};	
}

///Core Log Macros
#define GGM_CORE_ASSERT(x, ...) { if(!(x)) { GGM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define GGM_CORE_ERROR(...)			::ggm::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GGM_CORE_WARN(...)			::ggm::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GGM_CORE_INFO(...)			::ggm::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GGM_CORE_TRACE(...)			::ggm::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GGM_CORE_CRITICAL(...)		::ggm::Log::GetCoreLogger()->critical(__VA_ARGS__)

///Client Log Macros
#define GGM_ERROR(...)				::ggm::Log::GetClientLogger()->error(__VA_ARGS__)
#define GGM_WARN(...)				::ggm::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GGM_INFO(...)				::ggm::Log::GetClientLogger()->info(__VA_ARGS__)
#define GGM_TRACE(...)				::ggm::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GGM_FATAL_CRITICAL(...)		::ggm::Log::GetClientLogger()->critical(__VA_ARGS__)
#define GGM_ASSERT(x, ...) { if(!(x)) { GGM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
