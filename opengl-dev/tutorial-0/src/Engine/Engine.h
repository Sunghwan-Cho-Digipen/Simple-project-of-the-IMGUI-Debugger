#pragma once
#include <memory>
#include "../Event/Event.h"
#include "../Event/EngineEvent.h"
#include "../Window/Window.h"
//#include "../Layer/Layer.h"
//#include "../Layer/LayerStack.h"
namespace ggm
{
	class Engine
	{
	public:
		Engine();
		virtual ~Engine();

		void Run();

		void Event(Event& e);

		/*void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);*/
	private:
		bool OnWindowClosed(WindowCloseEvent& e);
		std::unique_ptr<Window> mWindow;
		bool mRunning = true;

		//LayerStack mLayerStack;
	};

}



