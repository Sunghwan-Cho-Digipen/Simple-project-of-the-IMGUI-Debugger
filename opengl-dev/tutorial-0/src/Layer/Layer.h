#pragma once

#include <string>

#include "../Event/Event.h"

namespace ggm
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void Attach(){}
		virtual void Detach(){}
		virtual void Update(){}
		virtual void OnEvent(Event& event){}

		[[nodiscard]] const std::string& GetName() const { return mDebugName; }
	protected:
		std::string mDebugName;
	};
}
