#include "Application.h"
#include "Harboe/Events/ApplicationEvent.h"
#include "Harboe/Log.h"

namespace Harboe
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(100, 200);
		HB_TRACE(e);

		while (true);
	}
}
