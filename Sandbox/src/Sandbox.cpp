#include <Harboe.h>
#include <Harboe/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public Harboe::Layer
{
public:
	ExampleLayer()
		: Layer("Example layer"), m_CameraController(1280.0f / 720.0f)
	{
		m_SquareVertexArray = Harboe::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Harboe::Ref<Harboe::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer = Harboe::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

		Harboe::BufferLayout squareLayout = {
			{ Harboe::ShaderDataType::Float3, "a_Position" },
			{ Harboe::ShaderDataType::Float2, "a_TexCoord" }
		};

		squareVertexBuffer->SetLayout(squareLayout);

		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Harboe::Ref<Harboe::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer = Harboe::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = Harboe::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);
		
		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
	
		m_Texture = Harboe::Texture2D::Create("assets/textures/Checkerboard.png");

		std::dynamic_pointer_cast<Harboe::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Harboe::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	virtual void OnUpdate(Harboe::Timestep ts) override
	{
		// Update
		m_CameraController.OnUpdate(ts);

		// Render
		Harboe::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Harboe::RenderCommand::Clear();

		Harboe::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Harboe::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Harboe::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int x = 0; x < 20; ++x)
		{
			for (int y = 0; y < 20; ++y)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Harboe::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Harboe::Renderer::Submit(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Harboe::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override 
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	virtual void OnEvent(Harboe::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
	Harboe::ShaderLibrary m_ShaderLibrary;
	Harboe::Ref<Harboe::Shader> m_FlatColorShader;
	Harboe::Ref<Harboe::VertexArray> m_SquareVertexArray;

	Harboe::Ref<Harboe::Texture2D> m_Texture;

	Harboe::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Harboe::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}
};

Harboe::Scope<Harboe::Application> Harboe::CreateApplication()
{
	return std::make_unique<Sandbox>();
}