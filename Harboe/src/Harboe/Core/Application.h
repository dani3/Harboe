#pragma once

#include "Core.h"

#include "Window.h"
#include "Harboe/Core/LayerStack.h"
#include "Harboe/Events/Event.h"
#include "Harboe/Events/ApplicationEvent.h"

#include "Harboe/Core/Timestep.h"

#include "Harboe/ImGui/ImGuiLayer.h"

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
		bool OnWindowResize(WindowResizeEvent& e);

		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;

		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;

	};

	// To be defined in CLIENT.
	Scope<Application> CreateApplication();
}
