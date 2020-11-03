#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "spdlog/sinks/base_sink.h"
#include "ImGuiConsole.h"

namespace ggm
{
    template<class Mutex>
    class ImGuiConsoleSink : public spdlog::sinks::base_sink<std::mutex>
	{
    public:
        explicit ImGuiConsoleSink(bool forceFlush = false, uint8_t bufferCapacity = 10)
            : mMessageBufferCapacity(forceFlush ? 1 : bufferCapacity), mMessageBuffer(std::vector<std::shared_ptr<ImGuiConsole::Message>>(forceFlush ? 1 : bufferCapacity))
        {
        }
        ImGuiConsoleSink(const ImGuiConsoleSink&) = delete;
        ImGuiConsoleSink& operator=(const ImGuiConsoleSink&) = delete;
        virtual ~ImGuiConsoleSink() = default;

    protected:
        void sink_it_(const spdlog::details::log_msg& msg) override
        {
            spdlog::memory_buf_t formatted;
        	
            formatter_->format(msg, formatted); 
            *(mMessageBuffer.begin() + mMessagesBuffered) = std::make_shared<ImGuiConsole::Message>(fmt::to_string(formatted), GetMessageLevel(msg.level));
            if (++mMessagesBuffered == mMessageBufferCapacity)
            {
                flush_();
            }
        }

        void flush_() override
        {
            for (const auto& message : mMessageBuffer)
            {
                ImGuiConsole::addMessage(message);
            }
            mMessagesBuffered = 0;
        }
    	
    private:
    	static ImGuiConsole::Message::ELevel GetMessageLevel(const spdlog::level::level_enum level)
    	{
            switch (level)
            {
            case spdlog::level::level_enum::trace:
            	return ImGuiConsole::Message::ELevel::TRACE;
            case spdlog::level::level_enum::debug:
            	return ImGuiConsole::Message::ELevel::DEBUG;
            case spdlog::level::level_enum::info:
            	return ImGuiConsole::Message::ELevel::INFO;
            case spdlog::level::level_enum::warn:
            	return ImGuiConsole::Message::ELevel::WARN;
            case spdlog::level::level_enum::err:
            	return ImGuiConsole::Message::ELevel::Error;
            case spdlog::level::level_enum::critical:
            	return ImGuiConsole::Message::ELevel::CRITICAL;
            case spdlog::level::level_enum::off:
            	return ImGuiConsole::Message::ELevel::OFF;
            default:
                return ImGuiConsole::Message::ELevel::INVALID;
            }
    	}
    private:
        uint8_t mMessagesBuffered = 0;
        uint8_t mMessageBufferCapacity;
        std::vector<std::shared_ptr<ImGuiConsole::Message>> mMessageBuffer;
    };

}

#include "spdlog/details/null_mutex.h"
#include <mutex>
namespace ggm
{
    using ImGuiConsoleSink_mt = ImGuiConsoleSink<std::mutex>;                  // multi-threaded
    using ImGuiConsoleSink_st = ImGuiConsoleSink<spdlog::details::null_mutex>; // single threaded
}