#include "hbpch.h"
#include "Application.h"

#include "Harboe/Events/ApplicationEvent.h"

namespace Harboe
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}
