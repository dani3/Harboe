#include "hbpch.h"

#include "OpenGLContext.h"

#include "Harboe/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace Harboe
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		HB_CORE_ASSERT(windowHandle, "Window handle is null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);

		// Initialize Glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HB_CORE_ASSERT(status, "Failed to initialize Glad");

		HB_CORE_INFO("OpenGL Info:");
		HB_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		HB_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		HB_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}