#include <Harboe.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Harboe::Layer
{
public:
	ExampleLayer()
		: Layer("Example layer"), m_Camera(-1.6f, 1.6, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Harboe::VertexArray::Create());

		float vertices[7 * 3] = {
			-0.5f, -0.5f, 0.0f, 0.2f, 0.1f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f,	0.0f, 0.5f, 0.8f, 1.0f
		};

		Harboe::Ref<Harboe::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Harboe::VertexBuffer::Create(vertices, sizeof(vertices)));

		Harboe::BufferLayout layout = {
			{ Harboe::ShaderDataType::Float3, "a_Position" },
			{ Harboe::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Harboe::Ref<Harboe::IndexBuffer> indexBuffer;
		indexBuffer.reset(Harboe::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVertexArray.reset(Harboe::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Harboe::Ref<Harboe::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(Harboe::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		Harboe::BufferLayout squareLayout = {
			{ Harboe::ShaderDataType::Float3, "a_Position" },
			{ Harboe::ShaderDataType::Float2, "a_TexCoord" }
		};

		squareVertexBuffer->SetLayout(squareLayout);

		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Harboe::Ref<Harboe::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(Harboe::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1);
				color = v_Color;
			}
		)";

		m_Shader.reset(Harboe::Shader::Create(vertexSrc, fragmentSrc));

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

		m_FlatColorShader.reset(Harboe::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));
		
		m_TextureShader.reset(Harboe::Shader::Create("assets/shaders/Texture.glsl"));
	
		m_Texture = Harboe::Texture2D::Create("assets/textures/Checkerboard.png");

		std::dynamic_pointer_cast<Harboe::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Harboe::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	virtual void OnUpdate(Harboe::Timestep timestep) override
	{
		if (Harboe::Input::IsKeyPressed(HB_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * timestep;
		else if (Harboe::Input::IsKeyPressed(HB_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * timestep;

		if (Harboe::Input::IsKeyPressed(HB_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * timestep;
		else if (Harboe::Input::IsKeyPressed(HB_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * timestep;

		if (Harboe::Input::IsKeyPressed(HB_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * timestep;

		if (Harboe::Input::IsKeyPressed(HB_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * timestep;

		Harboe::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Harboe::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Harboe::Renderer::BeginScene(m_Camera);

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

		m_Texture->Bind();
		Harboe::Renderer::Submit(m_TextureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Harboe::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override 
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	virtual void OnEvent(Harboe::Event& event) override
	{

	}

private:
	Harboe::Ref<Harboe::Shader> m_Shader;
	Harboe::Ref<Harboe::Shader> m_FlatColorShader;
	Harboe::Ref<Harboe::Shader> m_TextureShader;

	Harboe::Ref<Harboe::VertexArray> m_VertexArray;
	Harboe::Ref<Harboe::VertexArray> m_SquareVertexArray;

	Harboe::Ref<Harboe::Texture2D> m_Texture;

	Harboe::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;

	float m_CameraMoveSpeed = 1.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
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