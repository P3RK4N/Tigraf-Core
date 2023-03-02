#include "Tigraf/Core/Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Tigraf
{
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;

	void Log::init(const char* appName)
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("Tigraf");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt(appName);
		s_ClientLogger->set_level(spdlog::level::trace);

#ifdef TIGRAF_DISABLE_CONSOLE
		s_CoreLogger->sinks().clear();
		s_ClientLogger->sinks().clear();
#endif
	}

}