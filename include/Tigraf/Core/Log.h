#pragma once
#pragma warning (disable:4506)

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Tigraf
{
	class Log
	{
	public:
		Log()	{}
		~Log()	{}

		static void init(const char* appName);
		inline static std::shared_ptr<spdlog::logger>& getCoreLogger()   { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_ClientLogger; }

		inline static void setCustomCoreLogger(std::shared_ptr<spdlog::logger>& logger) { s_CoreLogger = logger; }
		inline static void setCustomClientLogger(std::shared_ptr<spdlog::logger>& logger) { s_ClientLogger = logger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

#ifdef TIGRAF_DEBUG

	#define REPLACE_CORE_LOG_SINK(sink)										\
				::Tigraf::Log::getCoreLogger()->sinks().clear();			\
				::Tigraf::Log::getCoreLogger()->sinks().emplace_back(sink)

	//TODO: Add TIGRAF_ prefix to macros used by client
	#define REPLACE_LOG_SINK(sink)											\
		::Tigraf::Log::getClientLogger()->sinks().clear();					\
		::Tigraf::Log::getClientLogger()->sinks().emplace_back(sink)
		
	#ifdef TIGRAF_CORE

		#define CORE_TRACE(...)				::Tigraf::Log::getCoreLogger()->trace(__VA_ARGS__)
		#define CORE_INFO(...)				::Tigraf::Log::getCoreLogger()->info(__VA_ARGS__)
		#define CORE_WARN(...)				::Tigraf::Log::getCoreLogger()->warn(__VA_ARGS__)
		#define CORE_ERROR(...)				::Tigraf::Log::getCoreLogger()->error(__VA_ARGS__)

	#elif defined TIGRAF_CLIENT

		#define TRACE(...)					::Tigraf::Log::getClientLogger()->trace(__VA_ARGS__)
		#define INFO(...)					::Tigraf::Log::getClientLogger()->info(__VA_ARGS__)
		#define WARN(...)					::Tigraf::Log::getClientLogger()->warn(__VA_ARGS__)
		#define ERROR(...)					::Tigraf::Log::getClientLogger()->error(__VA_ARGS__)
	
	#endif

#else 

	#define CORE_REPLACE_LOG_SINK(sink)
	#define REPLACE_LOG_SINK(sink)

	#define CORE_TRACE(...)	
	#define CORE_INFO(...)	
	#define CORE_WARN(...)	
	#define CORE_ERROR(...)	

	#define TRACE(...)	
	#define INFO(...)	
	#define WARN(...)	
	#define ERROR(...)	

#endif