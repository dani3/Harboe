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

	Harboe::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Harboe::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Harboe::Renderer2D::EndScene();
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
