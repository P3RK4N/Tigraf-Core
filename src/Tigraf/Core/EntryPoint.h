#pragma once

	extern void TIGRAF_STARTUP(std::vector<Tigraf::Layer*>& layers);
	extern const char* TIGRAF_APP_NAME;

	class EntryPoint
	{
	private:
		static Tigraf::Application* s_ApplicationInstance;

	public:
		static void Init(int argc = 0, char** argv = nullptr)
		{
			Tigraf::Log::init(TIGRAF_APP_NAME);

			//TODO: Take care of argc and argv
			//for(int i = 0; i < argc; i++) CORE_INFO("Arg {}: {}", i, argv[i]);
			//CORE_INFO("Working Directory: {}", std::filesystem::current_path());

			if(s_ApplicationInstance) s_ApplicationInstance->exit();

			s_ApplicationInstance = new Tigraf::Application({ TIGRAF_APP_NAME, std::filesystem::current_path(), { argc, argv } });

			TIGRAF_CORE_ASSERT(s_ApplicationInstance, "App creation was unsuccessful");

			TIGRAF_STARTUP(s_ApplicationInstance->getLayers());
		}

		static void Run() 
		{ 
			TIGRAF_CORE_ASSERT(s_ApplicationInstance, "Application is not initialised!");

			CORE_INFO("\n\n##########################\n\t{}\n##########################\n", TIGRAF_APP_NAME);

			s_ApplicationInstance->run(); 
		}
	};

	Tigraf::Application* EntryPoint::s_ApplicationInstance = nullptr;


#if defined(TIGRAF_WINDOWS) && defined(TIGRAF_DISABLE_CONSOLE)
#include <Windows.h>

	int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
	{
		EntryPoint::Init(__argc, __argv);
		EntryPoint::Run();

		CORE_TRACE("Press any key to exit: ");
		std::cin.get();

	}

#else

	int main(int argc, char** argv)
	{

		EntryPoint::Init(argc, (char**)argv);
		EntryPoint::Run();

		CORE_TRACE("Press any key to exit: ");
		std::cin.get();

		
	}

#endif
