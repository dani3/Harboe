#pragma once

#include "Core.h"

namespace Harboe
{
	class HARBOE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT.
	Application* CreateApplication();
}