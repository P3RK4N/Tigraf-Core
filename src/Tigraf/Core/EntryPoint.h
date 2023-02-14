#pragma once

#if 1

	extern void STARTUP(std::vector<Tigraf::Layer*>& layers);

	int main(int argc, char** argv)
	{
		Tigraf::Log::init();

	CORE_INFO("  TIny GRAphic Framework!");

		auto app = new Tigraf::Application({ "TIny GRAphic Framework", std::filesystem::current_path(), { argc, argv } });

	TIGRAF_CORE_ASSERT(app, "App creation was unsuccessful");

		STARTUP(app->getLayers());

		app->run();

	CORE_INFO("Application has successfully shut down!");

		std::cin.get();
	}

#endif