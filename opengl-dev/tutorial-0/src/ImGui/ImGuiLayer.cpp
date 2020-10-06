#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ImGuiLayer.h"

#include <GLFW/glfw3.h>



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
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		//Temporary: Should eventually use ggm key codes.
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 450");
	}
	
	void ImGuiLayer::Detach()
	{
		
	}
	
	void ImGuiLayer::Update()
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(200,50);

		float time = static_cast<float>(glfwGetTime());
		io.DeltaTime = mTime > 0.0 ? (time - mTime) : (1.0f / 60.0f);
		mTime = time;
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		//EventDispatcher dispatcher();
	}

	bool ImGuiLayer::onMouseButtonPressedEvent(MousePressedEvent& e)
	{
		return false;
	}

	bool ImGuiLayer::onMouseButtonReleasedEvent(MouseReleasedEvent& e)
	{
		return false;
	}

	bool ImGuiLayer::onMouseMovedEvent(MouseMovedEvent& e)
	{
		return false;
	}

	bool ImGuiLayer::onMouseScrolledEvent(MouseScrolledEvent& e)
	{
		return false;
	}

	bool ImGuiLayer::onKeyPressedEvent(KeyPressedEvent& e)
	{
		return false;
	}

	bool ImGuiLayer::onKeyReleasedEvent(KeyReleasedEvent& e)
	{
		return false;
	}

	bool ImGuiLayer::onWindowResizedEvent(WindowResizeEvent& e)
	{
		return false;
	}




	
}
