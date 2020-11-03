#pragma once

namespace ggm
{
	class ImGuiConsole
	{
	public:
		class Message
		{
		public:
			enum class ELevel : int8_t
			{
				INVALID = -1,
				TRACE = 0,
				DEBUG = 1,
				INFO = 2,
				WARN = 3,
				Error = 4, // I cannot use ERROR because of the #define ERROR;;;;
				CRITICAL = 5,
				OFF = 6, // Display nothing
			};
			struct Color
			{
				float r, g, b, a;
			};
		public:
			const std::string mMessage;
			const ELevel mLEVEL;
			static std::vector<ELevel> sLevels;
		public:
			Message(const std::string message = "", ELevel level = ELevel::INVALID);
			void OnImGuiDraw() const;
			static ELevel GetLowerLevel(ELevel level);
			static ELevel GetHigherLevel(ELevel level);
			static const char* GetLevelName(ELevel level);
		private:
			static Color getRenderColor(ELevel level);
			
		};
	public:
		~ImGuiConsole() = default;
		static void addMessage(std::shared_ptr<Message> message);
		static void OnImGuiRender(bool* show);
		static void Clear();
	protected:
		ImGuiConsole() = default;
	private:
		struct ImGuiRendering
		{
			static void ImGuiRenderHeader();
			static void ImGuiRenderSettings();
			static void ImGuiRenderMessages();
		};
	private:
		static float sDisplayScale;
		static uint16_t sMessageBufferCapacity;
		static uint16_t sMessageBufferSize;
		static uint16_t sMessageBufferBegin;
		static Message::ELevel sMessageBufferRenderFilter;
		static std::vector<std::shared_ptr<Message>> sMessageBuffer;
		static bool sAllowScrollingToBottom;
		static bool sRequestScrollToBottom;
	};
}
