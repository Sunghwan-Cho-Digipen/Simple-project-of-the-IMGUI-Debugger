#include "../Window/Window.h"
#include "WindowsInput.h"
#include <GLFW/glfw3.h>
#include "../Engine/Engine.h"

namespace ggm
{
	Input* Input::mInput = new WindowsInput();
	
	bool WindowsInput::isKeyPressedImpl(int keycode)
	{
		GLFWwindow* window = Engine::GetEngine().GetWindow().GetNativeWindow();
		const int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	
	bool WindowsInput::isMousePressedImpl(int button)
	{
		GLFWwindow* window = Engine::GetEngine().GetWindow().GetNativeWindow();
		const int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::getMousePositionImpl()
	{
		GLFWwindow* window = Engine::GetEngine().GetWindow().GetNativeWindow();
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return { static_cast<float>(xPos) ,static_cast<float>(yPos) };
	}
	
	float WindowsInput::getMouseXImpl()
	{
		auto [x, y] = getMousePositionImpl();
		return x;
	}
	
	float WindowsInput::getMouseYImpl()
	{
		auto [x, y] = getMousePositionImpl();
		return y;
	}
	
}
