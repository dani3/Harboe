#pragma once

#include "RendererAPI.h"

namespace Harboe
{
	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RedererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RedererAPI->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RedererAPI->DrawIndexed(vertexArray);
		}

	private:
		static RendererAPI* s_RedererAPI;
	};
}