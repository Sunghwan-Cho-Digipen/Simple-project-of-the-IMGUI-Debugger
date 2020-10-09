

#include "Engine.h"
#include <GLFW/glfw3.h>

#include "../Event/EngineEvent.h"
#include "../loggingSystem/Log.h"

namespace ggm
{
	Engine::Engine()
	{
		mWindow = std::unique_ptr<ggm::Window>(ggm::Window::Create());
		mWindow->SetEventCallback(std::bind(&Engine::Event, this, std::placeholders::_1));
	}
	
	Engine::~Engine()
	{
		
	}

	void Engine::Run()
	{
		while (mRunning)
		{
			glClearColor(0.f, 0.5f, 1.f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);
			mWindow->Update();

			for(auto layer : mLayerStack)
			{
				layer->Update();
			}
			
		}
	}

	void Engine::Event(ggm::Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Engine::OnWindowClosed, this, std::placeholders::_1));
		GGM_CORE_INFO("{0}", e);

		for(auto iter = mLayerStack.rbegin(); iter != mLayerStack.rend(); ++iter)
		{
			(*iter)->OnEvent(e);
			if(e.getHandled())
			{
				break;
			}
		}
	}

	void Engine::PushLayer(Layer* layer)
	{
		mLayerStack.PushLayer(layer);
	}

	void Engine::PushOverlay(Layer* layer)
	{
		mLayerStack.PushOverlay(layer);
	}

	bool Engine::OnWindowClosed(WindowCloseEvent& e)
	{
		mRunning = false;
		return true;
	}

	
}
