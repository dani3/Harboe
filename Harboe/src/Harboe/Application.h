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

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() const { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;

	};

	// To be defined in CLIENT.
	Application* CreateApplication();
}
