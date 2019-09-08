#pragma once

#include <string>

namespace Harboe
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind();
		void Unbind();

	private:
		uint32_t m_RenderedID;
	};
}