#include <Harboe.h>

#include "imgui/imgui.h"

class ExampleLayer : public Harboe::Layer
{
public:
	ExampleLayer()
		: Layer("Example layer") {}

	void OnUpdate() override
	{
		if (Harboe::Input::IsKeyPressed(HB_KEY_TAB))
		{
			HB_TRACE("Tab key is pressed");
		}
	}

	virtual void OnImGuiRender() override 
	{

	}

	void OnEvent(Harboe::Event& event) override
	{
		if (event.GetEventType() == Harboe::EventType::KeyPressed)
		{
			Harboe::KeyPressedEvent& e = (Harboe::KeyPressedEvent&) event;
			HB_TRACE("{0}", (char) e.GetKeyCode());
		}
	}
};

class Sandbox : public Harboe::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Harboe::Application* Harboe::CreateApplication()
{
	return new Sandbox();
}