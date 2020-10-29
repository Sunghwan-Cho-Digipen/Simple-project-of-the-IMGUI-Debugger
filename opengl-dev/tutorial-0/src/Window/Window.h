#pragma once

#include <string>
#include <functional>
#include <GLFW/glfw3.h>

#include "../Event/Event.h"

namespace ggm
{
	struct WindowProps
	{
		WindowProps(const std::string& title = "GGM Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: mTitle(title), mWidth(width), mHeight(height) {}

		~WindowProps() = default;
		
		std::string mTitle = "GGM Engine";
		unsigned int mWidth = 1280;
		unsigned int mHeight = 720;

	};

	class Window
	{
	public:
		Window(const WindowProps& props);
		virtual ~Window() = default;
		using EventCallbackFunc = std::function<void(Event&)>;
		
		void Update();
		void SwapBuffers();
		
		[[nodiscard]] unsigned int GetWidth() const { return mData.Width; }
		[[nodiscard]] unsigned int GetHeight() const { return mData.Height; }

		void SetEventCallback(const EventCallbackFunc& callback) { mData.EventCallback = callback; }
		void SetGLFWInitialized(const bool isInitialized) { mGLFWInitialized = isInitialized; }

		static Window* Create(const WindowProps& props = WindowProps());

		[[nodiscard]] GLFWwindow* GetNativeWindow() const { return mWindow; }
		
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
		
	private:
		GLFWwindow* mWindow;

		struct WindowData
		{
			std::string Title = "";
			unsigned int Width = 0, Height = 0;

			EventCallbackFunc EventCallback;
		};

		WindowData mData;
		
		inline static bool mGLFWInitialized = false;
	};
}
