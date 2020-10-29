#pragma once

#include "Input.h"

namespace ggm
{
	class WindowsInput : public Input
	{
	public:
		
	protected:
		bool isKeyPressedImpl(int keycode) override;
		bool isMousePressedImpl(int button) override;
		std::pair<float, float> getMousePositionImpl() override;
		float getMouseXImpl() override;
		float getMouseYImpl() override;
	private:
	};
}
