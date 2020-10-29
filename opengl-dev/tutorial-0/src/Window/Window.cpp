#include "Window.h"
#include "../loggingSystem/Log.h"

#include "../Event/EngineEvent.h"
#include "../Event/KeyEvent.h"
#include "../Event/MouseEvent.h"

namespace ggm
{
	Window::Window(const WindowProps& props)
	{
		Init(props);
	}

	static void GLFWErrorCallback(int error, const char* description)
	{
		GGM_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}
	
	void Window::Update()
	{
		glfwPollEvents();
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(mWindow);
	}
	
	Window* Window::Create(const WindowProps& props)
	{
		return new Window(props);
	}

	void Window::Init(const WindowProps& props)
	{
		mData.Title = props.mTitle;
		mData.Width = props.mWidth;
		mData.Height = props.mHeight;

		GGM_CORE_TRACE("Creating Window {0} ({1}, {2})", mData.Title, mData.Width, mData.Height);
		
		if(mGLFWInitialized == false)
		{
			int success = glfwInit();
			GGM_CORE_ASSERT(success,"Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			mGLFWInitialized = true;
		}

		mWindow = glfwCreateWindow(static_cast<int>(props.mWidth), static_cast<int>(props.mHeight), props.mTitle.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(mWindow);
		glfwSetWindowUserPointer(mWindow, &mData);

		//Set GLFW callbacks
		glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
			
		});

		glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, [[maybe_unused]]int scancode, int action, [[maybe_unused]] int mods)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
			case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
			case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
			case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(mWindow, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			
			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});
		
		glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, [[maybe_unused]] int mods)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
			case GLFW_PRESS:
				{
					MousePressedEvent event(button);
					data.EventCallback(event);
					break;
				}
			case GLFW_RELEASE:
				{
					MouseReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
			data.EventCallback(event);
		});
		
	}

	void Window::Shutdown()
	{
		glfwDestroyWindow(mWindow);
	}

}
