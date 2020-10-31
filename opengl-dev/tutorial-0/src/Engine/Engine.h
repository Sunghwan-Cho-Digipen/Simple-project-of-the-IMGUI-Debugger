#pragma once
#include <memory>
#include "../Event/Event.h"
#include "../Event/EngineEvent.h"
#include "../ImGui/ImGuiLayer.h"
#include "../Window/Window.h"
#include "../Layer/Layer.h"
#include "../Layer/LayerStack.h"

namespace ggm
{
	class Engine
	{
	public:
		Engine();
		virtual ~Engine() = default;

		void Run();

		void Event(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static Engine& GetEngine() { return *sEngine; }
		Window& GetWindow() { return *mWindow; }
		
	private:
		bool OnWindowClosed([[maybe_unused]]WindowCloseEvent& e);
		std::unique_ptr<Window> mWindow;
		ImGuiLayer* mImGuiLayer;
		bool mRunning = true;

		LayerStack mLayerStack;
		float mLastFrameTime = 0.0f;
	private:
		static Engine* sEngine;
		
	};

}



