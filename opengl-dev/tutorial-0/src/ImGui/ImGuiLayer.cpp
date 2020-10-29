
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ImGuiLayer.h"
#include "../Engine/Engine.h"
#include "../Event/Event.h"
#include ""

#define GGM_BIND_EVENT_FUNC(function) std::bind(&function, this, std::placeholders::_1)

namespace ggm
{
	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
	{
		
	}

	ImGuiLayer::~ImGuiLayer()
	{
		
	}

	void ImGuiLayer::Attach()
	{
		// Setup Dear ImGui context IMGUI_CHECKVERSION();
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;// Enable Docking
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
		////io.ConfigFlags |= ImGuiconfigFlags_ViewportsNoTaskBarIcons;
		////io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;
		
		// Setup Dear ImGui style
		ImGui:: StyleColorsDark();
		
		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		//if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) //Uncomment
		//{
		//	style.WindowRounding = 0.0f;
		//	//style.Colors(ImGuiCol_WindowBg].w = 1.0f;
		//	
		//}
		

		glewInit();
		
		Engine& engine = Engine::GetEngine();
		ImGui_ImplGlfw_InitForOpenGL(engine.GetWindow().GetNativeWindow(), false);
		ImGui_ImplOpenGL3_Init("#version 410");
		
	}
	
	void ImGuiLayer::Detach()
	{
		
	}
	
	void ImGuiLayer::Update()
	{
		ImGuiIO& io = ImGui::GetIO();
		Engine& engine = Engine::GetEngine();
		io.DisplaySize = ImVec2(static_cast<float>(engine.GetWindow().GetWidth()),static_cast<float>(engine.GetWindow().GetHeight()));

		float time = static_cast<float>(glfwGetTime());
		io.DeltaTime = mTime > 0.0 ? (time - mTime) : (1.0f / 60.0f);
		mTime = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	
	
}
