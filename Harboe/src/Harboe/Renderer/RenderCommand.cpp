#include "hbpch.h"

#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Harboe
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}