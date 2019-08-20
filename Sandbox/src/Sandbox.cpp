#include <Harboe.h>

class Sandbox : public Harboe::Application
{
public:
	Sandbox()
	{
		PushLayer(new Harboe::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Harboe::Application* Harboe::CreateApplication()
{
	return new Sandbox();
}