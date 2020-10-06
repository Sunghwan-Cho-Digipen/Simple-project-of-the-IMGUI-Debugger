#pragma once
#include <sstream>
#include "Event.h"


namespace ggm
{
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : mWidth(width), mHeight(height)
		{}

		unsigned int GetWidth() const { return mWidth; }
		unsigned int GetHeight() const { return mHeight; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << mWidth << ", " << mHeight;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WINDOWRESIZE)
		
	private:
		unsigned int mWidth = 0, mHeight = 0;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;
		EVENT_CLASS_TYPE(WINDOWCLOSE)
	};

	class EngineTickEvent : public Event
	{
	public:
		EngineTickEvent() = default;

		EVENT_CLASS_TYPE(ENGINETICK)
	};

	class EngineUpdateEvent : public Event
	{
	public:
		EngineUpdateEvent() = default;

		EVENT_CLASS_TYPE(ENGINEUPDATE)
	};

	//class EngineRenderEvent : public Event
	//{
	//public:
	//	EngineRenderEvent() = default;

	//	EVENT_CLASS_TYPE(ENGINERENDER)
	//};
	
}
