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

int main()
{
	Sandbox* sandbox = new Sandbox();

	sandbox->Run();

	delete sandbox;
}