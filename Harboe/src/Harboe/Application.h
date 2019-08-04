#pragma once

#include "Core.h"

#include "Window.h"
#include "Harboe/LayerStack.h"
#include "Harboe/Events/Event.h"
#include "Harboe/Events/ApplicationEvent.h"

namespace Harboe
{
	class HARBOE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT.
	Application* CreateApplication();
}
