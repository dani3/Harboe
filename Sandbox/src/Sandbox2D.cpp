#include "Sandbox2D.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{

}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = Harboe::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Harboe::Timestep ts)
{
	HB_PROFILE_FUNCTION();

	// Update
	{
		HB_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	// Render
	{
		HB_PROFILE_SCOPE("Renderer Prep");
		Harboe::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Harboe::RenderCommand::Clear();
	}

	{
		HB_PROFILE_SCOPE("Render Draw");
		Harboe::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Harboe::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Harboe::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 1.0f }, { 0.2f, 0.2f, 0.3f, 1.0f });
		Harboe::Renderer2D::DrawQuad({ 0.2f, -0.5f, -0.1f }, { 0.5f, 0.5f }, m_CheckerboardTexture);
		Harboe::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::End();
}

void Sandbox2D::OnEvent(Harboe::Event& e)
{
	m_CameraController.OnEvent(e);
}
