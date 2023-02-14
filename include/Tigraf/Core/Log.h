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

		static void init();
		inline static std::shared_ptr<spdlog::logger>& getCoreLogger()   { return s_CoreLogger;   }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

#ifdef TIGRAF_DEBUG

	#ifdef TIGRAF_CORE

		#define CORE_TRACE(...)		::Tigraf::Log::getCoreLogger()->trace(__VA_ARGS__)
		#define CORE_INFO(...)		::Tigraf::Log::getCoreLogger()->info(__VA_ARGS__)
		#define CORE_WARN(...)		::Tigraf::Log::getCoreLogger()->warn(__VA_ARGS__)
		#define CORE_ERROR(...)		::Tigraf::Log::getCoreLogger()->error(__VA_ARGS__)

	#elif defined TIGRAF_CLIENT
		
		#define TRACE(...)		::Tigraf::Log::getClientLogger()->trace(__VA_ARGS__)
		#define INFO(...)		::Tigraf::Log::getClientLogger()->info(__VA_ARGS__)
		#define WARN(...)		::Tigraf::Log::getClientLogger()->warn(__VA_ARGS__)
		#define ERROR(...)		::Tigraf::Log::getClientLogger()->error(__VA_ARGS__)
	
	#endif

#else 

	#define CORE_TRACE(...)	
	#define CORE_INFO(...)	
	#define CORE_WARN(...)	
	#define CORE_ERROR(...)	

	#define TRACE(...)	
	#define INFO(...)	
	#define WARN(...)	
	#define ERROR(...)	

#endif