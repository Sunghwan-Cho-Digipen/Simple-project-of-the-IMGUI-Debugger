#pragma once

#include <sstream>
#include <string>
#include "../Event/Event.h"

namespace ggm
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer") : mDebugName(name)
		{};
		virtual ~Layer() = default;

		virtual void Attach(){}
		virtual void Detach(){}
		virtual void Update(){}
		virtual void OnImGuiDraw() {}
		virtual void OnEvent([[maybe_unused]]Event& event){}

		[[nodiscard]] const std::string& GetName() const { return mDebugName; }
	protected:
		std::string mDebugName;
	};
}
