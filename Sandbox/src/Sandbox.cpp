#include <Harboe.h>

class Sandbox : public Harboe::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Harboe::Application* Harboe::CreateApplication()
{
	return new Sandbox();
}