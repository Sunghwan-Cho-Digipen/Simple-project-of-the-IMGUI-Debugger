#pragma once
#include "../Layer/Layer.h"


namespace ggm
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(bool renderDemo = true, bool renderConsole = true);
		~ImGuiLayer() = default;


		void Attach() override;
		void Detach() override;
		void OnImGuiDraw() override;
		
		void Begin();
		void End();
		
	private:
		float mTime = 0.0f;
		bool mRenderDemo = true;
		bool mRenderConsole = true;
	};
}
