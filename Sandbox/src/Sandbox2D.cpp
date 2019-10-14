#include "Sandbox2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{

}

void Sandbox2D::OnAttach()
{
	m_SquareVA = Harboe::VertexArray::Create();

	float squareVertices[4 * 3] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	Harboe::Ref<Harboe::VertexBuffer> squareVertexBuffer;
	squareVertexBuffer = Harboe::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

	Harboe::BufferLayout squareLayout = {
		{ Harboe::ShaderDataType::Float3, "a_Position" }
	};

	squareVertexBuffer->SetLayout(squareLayout);

	m_SquareVA->AddVertexBuffer(squareVertexBuffer);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Harboe::Ref<Harboe::IndexBuffer> squareIndexBuffer;
	squareIndexBuffer = Harboe::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVA->SetIndexBuffer(squareIndexBuffer);

	m_FlatColorShader = Harboe::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Harboe::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Harboe::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Harboe::RenderCommand::Clear();

	Harboe::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Harboe::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Harboe::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
	
	Harboe::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Harboe::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Harboe::Event& e)
{
	m_CameraController.OnEvent(e);
}
