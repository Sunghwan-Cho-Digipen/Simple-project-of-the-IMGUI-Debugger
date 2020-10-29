#include "Engine/Engine.h"
#include "loggingSystem/Log.h"
#include "ImGui/ImGuiLayer.h"


class ExampleLayer : public ggm::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{}

	void Update() override
	{
		if(startCount <= count)
		{
			GGM_INFO("ExampleLayer::Update");
		}
		++startCount;
	}

	void OnEvent(ggm::Event& event) override
	{
		GGM_INFO("{0}", event);
	}

private:
	static constexpr int count = 10;
	int startCount = 0;
};

class Prototype_engine : public ggm::Engine
{
public:
	Prototype_engine()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new ggm::ImGuiLayer());
	}

	~Prototype_engine()
	{

	}
};

int main()
{
	ggm::Log::Init();
	GGM_CORE_WARN("Initialized Log");
	int a = 8;
	GGM_INFO("Hello! Var={0}", a);
	
	Prototype_engine* engine = new Prototype_engine();
	engine->Run();
	delete engine;
	return 0;
}