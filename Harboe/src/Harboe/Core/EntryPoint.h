#pragma once

#ifdef HB_PLATFORM_WINDOWS

extern Harboe::Scope<Harboe::Application> Harboe::CreateApplication();

int main(int argc, char** argv)
{
	Harboe::Log::Init();

	HB_PROFILE_BEGIN_SESSION("Startup", "HarboeProfile-Startup.json");
	auto app = Harboe::CreateApplication();
	HB_PROFILE_END_SESSION();

	HB_PROFILE_BEGIN_SESSION("Startup", "HarboeProfile-Runtime.json");
	app->Run();
	HB_PROFILE_END_SESSION();
}

#endif
