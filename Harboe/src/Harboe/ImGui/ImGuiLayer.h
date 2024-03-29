#pragma once

#include "Harboe/Core/Layer.h"

#include "Harboe/Events/MouseEvent.h"
#include "Harboe/Events/KeyEvent.h"
#include "Harboe/Events/ApplicationEvent.h"

namespace Harboe
{
	class HARBOE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}