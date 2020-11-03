
#include <memory>
#include <vector>

#include "../loggingSystem/Log.h"
#include "ImGuiConsole.h"
#include "ImGui/imgui.h"
#include "ImGui/backends/imgui_impl_glfw.h"
#include "ImGui/backends/imgui_impl_opengl3.h"

namespace ggm
{
	float ImGuiConsole::sDisplayScale = 1.0f;
	uint16_t ImGuiConsole::sMessageBufferCapacity = 200;
	uint16_t ImGuiConsole::sMessageBufferSize = 0;
	uint16_t ImGuiConsole::sMessageBufferBegin = 0;
	ImGuiConsole::Message::ELevel ImGuiConsole::sMessageBufferRenderFilter = ImGuiConsole::Message::ELevel::TRACE;
	std::vector<std::shared_ptr<ImGuiConsole::Message>> ImGuiConsole::sMessageBuffer(sMessageBufferCapacity);
	bool ImGuiConsole::sAllowScrollingToBottom = true;
	bool ImGuiConsole::sRequestScrollToBottom = false;

	std::vector<ImGuiConsole::Message::ELevel> ImGuiConsole::Message::sLevels
	{
		ImGuiConsole::Message::ELevel::TRACE,
		ImGuiConsole::Message::ELevel::DEBUG, //Might have some bugs
		ImGuiConsole::Message::ELevel::INFO,
		ImGuiConsole::Message::ELevel::WARN,
		ImGuiConsole::Message::ELevel::Error,
		ImGuiConsole::Message::ELevel::CRITICAL,
		ImGuiConsole::Message::ELevel::OFF
	};

	void ImGuiConsole::OnImGuiRender(bool* show)
	{
		ImGui::SetNextWindowSize(ImVec2(640, 480), ImGuiCond_FirstUseEver);
		ImGui::Begin("Console", show);
		{
			ImGuiRendering::ImGuiRenderHeader();
			ImGui::Separator();
			ImGuiRendering::ImGuiRenderMessages();
		}
		ImGui::End();
	}

	void ImGuiConsole::addMessage(std::shared_ptr<Message> message)
	{
		if (message->mLEVEL == Message::ELevel::INVALID)
		{
			return;
		}

		*(sMessageBuffer.begin() + sMessageBufferBegin) = message;

		if(++sMessageBufferBegin == sMessageBufferCapacity)
		{
			sMessageBufferBegin = 0;
		}
		if(sMessageBufferSize < sMessageBufferCapacity)
		{
			++sMessageBufferSize;
		}

		sRequestScrollToBottom = sAllowScrollingToBottom;
	}

	void ImGuiConsole::Clear()
	{
		for (auto message = sMessageBuffer.begin(); message != sMessageBuffer.end(); ++message)
		{
			*message = std::make_shared<Message>();
		}
		sMessageBufferBegin = 0;
	}


	ImGuiConsole::Message::Message(const std::string message, ELevel level) : mMessage(message), mLEVEL(level)
	{
	}

	void ImGuiConsole::Message::OnImGuiDraw() const
	{
		if(mLEVEL != ELevel::INVALID && mLEVEL >= ImGuiConsole::sMessageBufferRenderFilter)
		{
			const Color color = getRenderColor(mLEVEL);
			ImGui::PushStyleColor(ImGuiCol_Text, { color.r, color.g, color.b, color.a });
			ImGui::TextUnformatted(mMessage.c_str());
			ImGui::PopStyleColor();
		}
	}

	void ImGuiConsole::ImGuiRendering::ImGuiRenderHeader()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		const float innerSpacing = style.ItemInnerSpacing.x;
		
		// Text change level
		ImGui::AlignTextToFramePadding();
		ImGui::Text("Display");

		ImGui::SameLine(0.0f, 2.0f * innerSpacing);

		// Buttons to quickly change level left
		if (ImGui::ArrowButton("##MessageRenderFilter_L", ImGuiDir_Left))
		{
			sMessageBufferRenderFilter = Message::GetLowerLevel(sMessageBufferRenderFilter);
		}

		ImGui::SameLine(0.0f, innerSpacing);

		// Dropdown with levels
		ImGui::PushItemWidth(ImGui::CalcTextSize("Critical").x * 1.36f);
		if (ImGui::BeginCombo("##MessageRenderFilter", Message::GetLevelName(sMessageBufferRenderFilter), ImGuiComboFlags_NoArrowButton))
		{
			for (auto level = Message::sLevels.begin(); level != Message::sLevels.end(); level++)
			{
				const bool isSelected = (sMessageBufferRenderFilter == *level);
				
				if (ImGui::Selectable(Message::GetLevelName(*level), isSelected))
				{
					sMessageBufferRenderFilter = *level;
				}
				
				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();

		ImGui::SameLine(0.0f, innerSpacing);

		// Buttons to quickly change level right
		if (ImGui::ArrowButton("##MessageRenderFilter_R", ImGuiDir_Right))
		{
			sMessageBufferRenderFilter = Message::GetHigherLevel(sMessageBufferRenderFilter);
		}

		ImGui::SameLine(0.0f, innerSpacing);

		// Button for advanced settings
		ImGui::SameLine(0.0f, ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize("Settings").x - style.WindowPadding.x / 2.0f);
		if (ImGui::Button("Settings"))
		{
			ImGui::OpenPopup("SettingsPopup");
		}
		if (ImGui::BeginPopup("SettingsPopup"))
		{
			ImGuiRenderSettings();
			ImGui::EndPopup();
		}
		
	}

	void ImGuiConsole::ImGuiRendering::ImGuiRenderSettings()
	{
		const float maxWidth = ImGui::CalcTextSize("Scroll to bottom").x * 1.1f;
		const float innerSpacing = ImGui::GetStyle().ItemInnerSpacing.x + ImGui::CalcTextSize(" ").x;

		// Checkbox for scrolling lock
		ImGui::AlignTextToFramePadding();
		ImGui::Text("Scroll to bottom");
		ImGui::SameLine(0.0f, innerSpacing + maxWidth - ImGui::CalcTextSize("Scroll to bottom").x);
		ImGui::Checkbox("##ScrollToBottom", &sAllowScrollingToBottom);

		ImGui::SameLine(0.0f, innerSpacing);

		// Button to clear the console
		ImGui::SameLine(0.0f, ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize("Clear console").x + 1.0f);
		if (ImGui::Button("Clear console"))
		{
			ImGuiConsole::Clear();
		}
		
		// Slider for font scale
		ImGui::AlignTextToFramePadding();
		ImGui::Text("Display scale");
		ImGui::SameLine(0.0f, innerSpacing + maxWidth - ImGui::CalcTextSize("Display scale").x);
		ImGui::PushItemWidth(maxWidth * 1.25f / 1.1f);
		ImGui::SliderFloat("##DisplayScale", &sDisplayScale, 0.5f, 4.0f, "%.1f");
		ImGui::PopItemWidth();
	}

	void ImGuiConsole::ImGuiRendering::ImGuiRenderMessages()
	{
		ImGui::BeginChild("ScrollRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
		{
			ImGui::SetWindowFontScale(sDisplayScale);

			auto messageStart = sMessageBuffer.begin() + sMessageBufferBegin;
			if (*messageStart) // If contains old message here
			{
				for (auto message = messageStart; message != sMessageBuffer.end(); ++message)
				{
					(*message)->OnImGuiDraw();
				}
			}
			
			if (sMessageBufferBegin != 0) // Skipped first messages in vector
			{
				for (auto message = sMessageBuffer.begin(); message != messageStart; ++message)
				{
					(*message)->OnImGuiDraw();
				}
			}
			
			if (sRequestScrollToBottom && ImGui::GetScrollMaxY() > 0)
			{
				ImGui::SetScrollY(ImGui::GetScrollMaxY());
				sRequestScrollToBottom = false;
			}
		}
		ImGui::EndChild();
	}

	ImGuiConsole::Message::ELevel ImGuiConsole::Message::GetLowerLevel(ELevel level)
	{
		switch (level)
		{
		case ImGuiConsole::Message::ELevel::OFF:
			return ImGuiConsole::Message::ELevel::CRITICAL;
		case ImGuiConsole::Message::ELevel::CRITICAL:
			return ImGuiConsole::Message::ELevel::Error;
		case ImGuiConsole::Message::ELevel::Error:
			return ImGuiConsole::Message::ELevel::WARN;
		case ImGuiConsole::Message::ELevel::WARN:
			return ImGuiConsole::Message::ELevel::DEBUG; //Might have some bugs
		case ImGuiConsole::Message::ELevel::DEBUG:
			return ImGuiConsole::Message::ELevel::INFO;
		case ImGuiConsole::Message::ELevel::INFO:
		case ImGuiConsole::Message::ELevel::TRACE:
			return ImGuiConsole::Message::ELevel::TRACE;
		default:
			return ImGuiConsole::Message::ELevel::INVALID;
		}
	}

	ImGuiConsole::Message::ELevel ImGuiConsole::Message::GetHigherLevel(ELevel level)
	{
		switch (level)
		{
		case ImGuiConsole::Message::ELevel::TRACE:
			return ImGuiConsole::Message::ELevel::INFO;
		case ImGuiConsole::Message::ELevel::INFO:
			return ImGuiConsole::Message::ELevel::DEBUG; //Might have some bugs
		case ImGuiConsole::Message::ELevel::DEBUG:
			return ImGuiConsole::Message::ELevel::WARN;
		case ImGuiConsole::Message::ELevel::WARN:
			return ImGuiConsole::Message::ELevel::Error;
		case ImGuiConsole::Message::ELevel::Error:
			return ImGuiConsole::Message::ELevel::CRITICAL;
		case ImGuiConsole::Message::ELevel::CRITICAL:
		case ImGuiConsole::Message::ELevel::OFF:
			return ImGuiConsole::Message::ELevel::OFF;
		default:
			return ImGuiConsole::Message::ELevel::INVALID;
		}
	}

	const char* ImGuiConsole::Message::GetLevelName(ELevel level)
	{
		switch (level)
		{
		case ImGuiConsole::Message::ELevel::TRACE:
			return "Trace";
		case ImGuiConsole::Message::ELevel::INFO:
			return "Info";
		case ImGuiConsole::Message::ELevel::DEBUG:
			return "Debug";
		case ImGuiConsole::Message::ELevel::WARN:
			return "Warning";
		case ImGuiConsole::Message::ELevel::Error:
			return "Error";
		case ImGuiConsole::Message::ELevel::CRITICAL:
			return "Critical";
		case ImGuiConsole::Message::ELevel::OFF:
			return "None";
		default:
			return "Unknown name";
		}
	}

	ImGuiConsole::Message::Color ImGuiConsole::Message::getRenderColor(ELevel level)
	{
		switch (level)
		{
		case ImGuiConsole::Message::ELevel::TRACE:
			return { 0.75f, 0.75f, 0.75f, 1.00f }; // White-ish gray
		case ImGuiConsole::Message::ELevel::INFO:
			return { 0.00f, 0.50f, 0.00f, 1.00f }; // Green
		case ImGuiConsole::Message::ELevel::DEBUG:
			return { 0.00f, 0.50f, 0.50f, 1.00f }; // Cyan
		case ImGuiConsole::Message::ELevel::WARN:
			return { 1.00f, 1.00f, 0.00f, 1.00f }; // Yellow
		case ImGuiConsole::Message::ELevel::Error:
			return { 1.00f, 0.00f, 0.00f, 1.00f }; // Red
		case ImGuiConsole::Message::ELevel::CRITICAL:
		default:
			return { 1.00f, 1.00f, 1.00f, 1.00f };
		}
	}

}