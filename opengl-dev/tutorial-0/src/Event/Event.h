#pragma once

#include <string>
#include <functional>
#include <spdlog/fmt/bundled/format.h>

namespace ggm
{
	enum class EEventType
	{
		NONE = 0,
		WINDOWCLOSE,
		WINDOWRESIZE,
		WINDOWFOCUS,
		WINDOWLOSTFOCUS,
		WINDOWMOVED,
		ENGINETICK,
		ENGINEUPDATE,
		//ENGINERENDER,
		KEYPRESSED,
		KEYRELEASED,
		MOUSEPRESSED,
		MOUSERELEASED,
		MOUSEMOVED,
		MOUSESCROLLED
	};

#define EVENT_CLASS_TYPE(type) static EEventType GetStaticType() { return EEventType::##type; }\
							   virtual EEventType GetEventType() const override { return GetStaticType(); }\
							   virtual const char* GetName() const override { return #type; }
	
	class Event
	{
		friend class EventDispatcher;
	public:
		[[nodiscard]] virtual EEventType GetEventType() const = 0;
		[[nodiscard]] virtual const char* GetName() const = 0;
		[[nodiscard]] virtual std::string ToString() const { return GetName(); }
		[[nodiscard]] virtual bool getHandled() const { return mHandled; }
		virtual ~Event() = default;
	protected:
		bool mHandled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFunc = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event)
			: mEvent(event)
		{}

		template<typename T>
		bool Dispatch(EventFunc<T> func)
		{
			if (mEvent.GetEventType() == T::GetStaticType())
			{
				mEvent.mHandled = func(*static_cast<T*>(&mEvent));
				return true;
			}
			return false;
		}
		
	private:
		Event& mEvent;

	};
	
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}


////https://fmt.dev/latest/api.html#formatting-user-defined-types
//template<>
//struct fmt::formatter<ggm::Event> : formatter<string_view>
//{
//	constexpr auto parse(ggm::Event& e ,format_parse_context& ctx)
//	{
//		string_view name = e.ToString();
//	}
//};