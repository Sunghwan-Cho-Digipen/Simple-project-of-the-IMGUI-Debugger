#pragma once
#include <glm/vec2.hpp>
#include "../key_mouse_codes/KeyCode.h"
#include "../key_mouse_codes/MouseCode.h"


namespace ggm
{
	class Input
	{
	public:
		static bool IsKeyPressed(int Keycode) { return mInput->isKeyPressedImpl(Keycode); }
		static bool isMousePressed(int button) { return mInput->isMousePressedImpl(button); }
		static std::pair<float, float> GetMousePosition() { return mInput->getMousePositionImpl(); }
		static float GetMouseX() { return mInput->getMouseXImpl(); }
		static float GetMouseY() { return mInput->getMouseYImpl(); }
		virtual ~Input()
		{
			delete mInput;
			mInput = nullptr;
		};
	protected:
		virtual bool isKeyPressedImpl(int keycode) = 0;
		virtual bool isMousePressedImpl(int button) = 0;
		virtual std::pair<float, float> getMousePositionImpl() = 0;
		virtual float getMouseXImpl() = 0;
		virtual float getMouseYImpl() = 0;
		
	private:
		static Input* mInput;
	};
}
