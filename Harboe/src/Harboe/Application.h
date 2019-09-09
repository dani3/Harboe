#pragma once

#include "Core.h"

#include "Window.h"
#include "Harboe/LayerStack.h"
#include "Harboe/Events/Event.h"
#include "Harboe/Events/ApplicationEvent.h"
#include "Harboe/Renderer/Shader.h"
#include "Harboe/Renderer/Buffer.h"

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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;

		LayerStack m_LayerStack;

		unsigned int m_VertexArray;

		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;

	private:
		static Application* s_Instance;

	};

	// To be defined in CLIENT.
	Application* CreateApplication();
}
