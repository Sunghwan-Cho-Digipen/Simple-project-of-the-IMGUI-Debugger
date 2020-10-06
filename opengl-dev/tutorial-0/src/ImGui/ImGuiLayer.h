#pragma once
#include "../Layer/Layer.h"


#include "../Event/EngineEvent.h"
#include "../Event/KeyEvent.h"
#include "../Event/MouseEvent.h"

namespace ggm
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();


		void Attach() override;
		void Detach() override;
		void Update() override;
		void OnEvent(Event& event) override;

	private:
		bool onMouseButtonPressedEvent(MousePressedEvent& e);
		bool onMouseButtonReleasedEvent(MouseReleasedEvent& e);
		bool onMouseMovedEvent(MouseMovedEvent& e);
		bool onMouseScrolledEvent(MouseScrolledEvent& e);
		bool onKeyPressedEvent(KeyPressedEvent& e);
		bool onKeyReleasedEvent(KeyReleasedEvent& e);
		//bool onKeyTypedEvent(KeyTypedEvent& e);
		bool onWindowResizedEvent(WindowResizeEvent& e);
		
		
	private:
		float mTime = 0.0f;
	};
}
