#pragma once
#include "../Layer/Layer.h"
#include "../Event/EngineEvent.h"
#include "../Event/KeyEvent.h"
#include "../Event/MouseEvent.h"

namespace ggm
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();


		void Attach() override;
		void Detach() override;
		void OnImGuiDraw() override;
		void Begin();
		void End();
		
	private:
		float mTime = 0.0f;
	};
}
