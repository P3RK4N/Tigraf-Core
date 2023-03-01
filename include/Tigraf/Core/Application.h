#pragma once

#include "Tigraf/Core/Layer.h"
#include "Tigraf/Window/Window.h"
#include "Tigraf/Event/Event.h"

namespace Tigraf
{
	struct CommandLineArgs
	{
		int argc = 0;
		char** argv = nullptr;
	};

	struct ApplicationSpecification
	{
		std::string name{};
		std::filesystem::path workingDirectory{};
		CommandLineArgs args{};
	};

	class Application
	{
	public:
		Application
		(
			ApplicationSpecification spec = 
			{ 
				"TIny GRAphic Framework", 
				std::filesystem::current_path(), 
				{} 
			}

		);

		virtual ~Application();

		void run(); //TODO: Also make visible in entry class in entrypoint only
		void exit() { m_Running = false; } //TODO: This too

		std::string getName() { return m_ApplicationSpecification.name; }
		std::filesystem::path getWorkingDirectory() { return m_ApplicationSpecification.workingDirectory; }
		Scope<Window>& getWindow() { return m_Window; }

		void pushLayer(Layer* layer) { m_Layers.push_back(layer); }
		void popLayer() { delete m_Layers.back(); m_Layers.pop_back(); }

		std::vector<Layer*>& getLayers() { return m_Layers; }
		void setLayers(const std::vector<Layer*>& layers) { m_Layers = layers; }

	private:
		void init();
		void onUpdate();
		void onDraw();
		bool onEvent(Event& event);
		void shutdown();

	public:
		static Application* s_Instance;

	protected:
		EVENT(onResize);
		EVENT(onClose);
		EVENT(onKey);

	protected:
		ApplicationSpecification m_ApplicationSpecification{};
		bool m_Running = true;
		bool m_Minimized = false;

		std::vector<Layer*> m_Layers{};
		Scope<Window> m_Window = nullptr;
		Scope<Timer> m_Timer = nullptr;
	};
}