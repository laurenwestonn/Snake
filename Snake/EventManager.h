#pragma once
#include <string>
#include <SFML\Graphics.hpp>
#include <unordered_map>
#include <functional>

class EventManager {

	enum class EventType {
		KeyDown = sf::Event::KeyPressed,
		KeyUp = sf::Event::KeyReleased,
		MButtonDown = sf::Event::MouseButtonPressed,
		MButtonUp = sf::Event::MouseButtonReleased,
		MouseWheel = sf::Event::MouseWheelMoved,
		WindowResized = sf::Event::Resized,
		GainedFocus = sf::Event::GainedFocus,
		LostFocus = sf::Event::LostFocus,
		MouseEntered = sf::Event::MouseEntered,
		MouseLeft = sf::Event::MouseLeft,
		Closed = sf::Event::Closed,
		TextEntered = sf::Event::TextEntered,
		Keyboard = sf::Event::Count + 1,
		Mouse,
		Joystick
	};

	struct EventInfo {

		union {
			int m_code;
		};

		EventInfo() { m_code = 0; }
		EventInfo(int l_event) { m_code = l_event; }
	};

	struct EventDetails {
		EventDetails(const std::string &l_bindName) : m_name(l_bindName) {
			Clear();
		}

		std::string m_name;

		sf::Vector2i m_size;
		sf::Uint32 m_textEntered;
		sf::Vector2i m_mouse;
		int m_mouseWheelDelta;
		int m_keyCode;

		void Clear() {
			m_size = sf::Vector2i(0, 0);
			m_textEntered = 0;
			m_mouse = sf::Vector2i(0, 0);
			int m_mouseWheelDela = 0;
			m_keyCode = -1;
		}
	};

	using Callbacks = std::unordered_map <std::string, std::function<void(EventDetails*)>>;
	using Events = std::vector<std::pair<EventType, EventInfo>>;

	struct Binding {

		Events m_events;
		std::string m_name;
		int cnt;
		EventDetails m_details;

		Binding(const std::string &l_name) : m_name(l_name), m_details(l_name), cnt(0) {}

		void BindEvent(EventType l_type, EventInfo l_info = EventInfo())
		{
			m_events.emplace_back(l_type, l_info);
		}
	};

	using Bindings = std::unordered_map<std::string, Binding*>;


public:
	EventManager();
	~EventManager();

	bool AddBinding(Binding *l_binding);
	bool RemoveBinding(std::string l_name);
	void SetFocus(const bool &l_focus);

	void HandleEvent(sf::Event &l_event);
	void Update();

	template<class T>
	bool AddCallback(const std::string &l_name,
		void(T::*l_func) (EventDetails*), T* l_instance)
	{
		auto temp = std::bind(l_func, l_instance, stf::placeholders::_1);
		return m_callbacks.emplace(l_name, temp).second;
	}

	void RemoveCallback(const std::string &l_name)
	{
		m_callbacks.erase(l_name);
	}

	sf::Vector2i GetMousePos(sf::RenderWindow *l_wind = nullptr)
	{
		return (l_wind ? sf::Mouse::getPosition(*l_wind) : sf::Mouse::getPosition());
	}

	private:
		void LoadBindings();    
		Bindings m_bindings;  
		Callbacks m_callbacks;   
		bool m_hasFocus;
};