#pragma once

#include "Harboe.h"

class Sandbox2D : public Harboe::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Harboe::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Harboe::Event& e) override;

private:
	Harboe::Ref<Harboe::Shader> m_FlatColorShader;
	Harboe::Ref<Harboe::VertexArray> m_SquareVA;

	Harboe::Ref<Harboe::Texture2D> m_CheckerboardTexture;

	Harboe::OrthographicCameraController m_CameraController;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};
