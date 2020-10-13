#pragma once
#include <glm/vec2.hpp>
#include "../key_mouse_codes/KeyCode.h"
#include "../key_mouse_codes/MouseCode.h"


namespace ggm
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode Key);
		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}
