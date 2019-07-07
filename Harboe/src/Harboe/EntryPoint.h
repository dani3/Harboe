#pragma once

#ifdef HB_PLATFORM_WINDOWS

extern Harboe::Application* Harboe::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Harboe::CreateApplication();
	app->Run();
	delete app;
}

#endif