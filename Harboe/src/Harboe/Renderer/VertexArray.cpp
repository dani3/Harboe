#include "hbpch.h"

#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Harboe
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:
			{
				HB_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
				return nullptr;
			}

			case RendererAPI::OpenGL:
			{
				return new OpenGLVertexArray();
			}
		}

		HB_CORE_ASSERT(false, "Unknown RendererAPI");

		return nullptr;
	}
}