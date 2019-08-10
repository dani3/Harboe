#include <Harboe.h>

class ExampleLayer : public Harboe::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override
	{
		HB_INFO("Ex:Update");
	}

	void OnEvent(Harboe::Event& e) override
	{
		HB_TRACE("{0}", e);
	}
};

class Sandbox : public Harboe::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
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