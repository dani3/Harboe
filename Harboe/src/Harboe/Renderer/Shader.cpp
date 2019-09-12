#include "hbpch.h"
#include "Shader.h"

#include "Harboe/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Harboe
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				HB_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
				return nullptr;
			}

			case RendererAPI::API::OpenGL:
			{
				return new OpenGLShader(vertexSrc, fragmentSrc);
			}
		}

		HB_CORE_ASSERT(false, "Unknown RendererAPI");

		return nullptr;
	}
}
