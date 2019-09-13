#include <Harboe.h>

#include "imgui/imgui.h"

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

		std::shared_ptr<Harboe::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Harboe::VertexBuffer::Create(vertices, sizeof(vertices)));

		Harboe::BufferLayout layout = {
			{ Harboe::ShaderDataType::Float3, "a_Position" },
			{ Harboe::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Harboe::IndexBuffer> indexBuffer;
		indexBuffer.reset(Harboe::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVertexArray.reset(Harboe::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<Harboe::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(Harboe::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		Harboe::BufferLayout squareLayout = {
			{ Harboe::ShaderDataType::Float3, "a_Position" }
		};

		squareVertexBuffer->SetLayout(squareLayout);

		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Harboe::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(Harboe::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		std::string blueShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection* vec4(a_Position, 1.0);
			}
		)";

		std::string blueShaderfragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1);
			}
		)";

		m_BlueShader.reset(Harboe::Shader::Create(blueShaderVertexSrc, blueShaderfragmentSrc));
	}

	virtual void OnUpdate() override
	{
		if (Harboe::Input::IsKeyPressed(HB_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed;
		else if (Harboe::Input::IsKeyPressed(HB_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed;

		if (Harboe::Input::IsKeyPressed(HB_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed;
		else if (Harboe::Input::IsKeyPressed(HB_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed;

		if (Harboe::Input::IsKeyPressed(HB_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed;

		if (Harboe::Input::IsKeyPressed(HB_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed;

		Harboe::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Harboe::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Harboe::Renderer::BeginScene(m_Camera);

		Harboe::Renderer::Submit(m_BlueShader, m_SquareVertexArray);
		Harboe::Renderer::Submit(m_Shader, m_VertexArray);

		Harboe::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override 
	{

	}

	virtual void OnEvent(Harboe::Event& event) override
	{

	}

private:
	std::shared_ptr<Harboe::Shader> m_Shader;
	std::shared_ptr<Harboe::Shader> m_BlueShader;
	std::shared_ptr<Harboe::VertexArray> m_VertexArray;

	std::shared_ptr<Harboe::VertexArray> m_SquareVertexArray;

	Harboe::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;

	float m_CameraMoveSpeed = 0.025f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 2.0f;
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