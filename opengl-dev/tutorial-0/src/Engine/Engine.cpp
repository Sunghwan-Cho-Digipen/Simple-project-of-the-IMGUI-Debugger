

#include "Engine.h"
#include "Time.h"
#include <GLFW/glfw3.h>

#include "../Event/EngineEvent.h"
#include "../loggingSystem/Log.h"

namespace ggm
{
	Engine* Engine::sEngine = nullptr;
	
	Engine::Engine()
	{
		GGM_CORE_ASSERT(!sEngine, "Engine already exists!");
		sEngine = this;
		mWindow = std::unique_ptr<ggm::Window>(ggm::Window::Create());
		mWindow->SetEventCallback(std::bind(&Engine::Event, this, std::placeholders::_1));
		mImGuiLayer = new ImGuiLayer();
		PushOverlay(mImGuiLayer);
	}

	void Engine::Run()
	{
		while (mRunning)
		{
			glClearColor(0.f, 0.5f, 1.f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);

			float time = (float)glfwGetTime();
			Time deltatime = time - mLastFrameTime;
			mLastFrameTime = time;
			
			for(auto layer : mLayerStack)
			{
				layer->Update(deltatime);
			}

			mImGuiLayer->Begin();
			for(Layer* layer : mLayerStack)
			{
				layer->OnImGuiDraw();
			}
			mImGuiLayer->End();
			mWindow->Update();
			
			mWindow->SwapBuffers();
		}
	}

	void Engine::Event(ggm::Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Engine::OnWindowClosed, this, std::placeholders::_1));
		GGM_CORE_TRACE("{0}", e);

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
		layer->Attach();
	}

	void Engine::PushOverlay(Layer* layer)
	{
		mLayerStack.PushOverlay(layer);
		layer->Attach();
	}

	bool Engine::OnWindowClosed([[maybe_unused]]WindowCloseEvent& e)
	{
		mRunning = false;
		return true;
	}

	
}
