#pragma once
#include <sstream>
#include "Event.h"

namespace ggm
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: mMouseX(x), mMouseY(y) {}

		[[nodiscard]] float GetX() const { return mMouseX; }
		[[nodiscard]] float GetY() const { return mMouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << mMouseX << ", " << mMouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MOUSEMOVED)
		
	private:
		float mMouseX = 0, mMouseY = 0;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: mXOffset(xOffset), mYOffset(yOffset) {}

		[[nodiscard]] float GetXOffset() const { return mXOffset; }
		[[nodiscard]] float GetYOffset() const { return mYOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << mXOffset << ", " << mYOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MOUSESCROLLED)
		
	private:
		float mXOffset = 0, mYOffset = 0;
	};

	class MouseButtonEvent : public Event
	{
	public:
		int GetMouseButton() const { return mButton; }

	protected:
		MouseButtonEvent(int button)
			: mButton(button) {}

		int mButton;
		
	};

	class MousePressedEvent : public MouseButtonEvent
	{
	public:
		MousePressedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MousePressedEvent: " << mButton;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MOUSEPRESSED)
	};

	class MouseReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseReleasedEvent(int button)
			:MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseReleasedEvent: " << mButton;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MOUSERELEASED)
		
	};
	
}
