#include "EventManager.h"

EventManager::EventManager() : 
	m_currentState(StateType(0)), 
	m_hasFocus(true)
{
	LoadBindings();
}


EventManager::~EventManager()
{
	for (auto &itr : m_bindings) {
		delete itr.second;
		itr.second = nullptr;
	}
}

bool EventManager::AddBinding(Binding * l_binding)
{
	if (!l_binding || m_bindings.find(l_binding->m_name) != m_bindings.end())
		return false;

	return m_bindings.emplace(l_binding->m_name, l_binding).second;
}

bool EventManager::RemoveBinding(std::string l_name)
{
	auto itr = m_bindings.find(l_name);
	if (itr == m_bindings.end())
		return false;

	delete itr->second;
	m_bindings.erase(itr);
	return true;
}

void EventManager::SetCurrentState(StateType l_state) {
	m_currentState = l_state;
}


void EventManager::SetFocus(const bool & l_focus)
{
	m_hasFocus = l_focus;
}

void EventManager::HandleEvent(sf::Event & l_event)
{
	// Iterate through each binding & event type
	for (auto &b_itr : m_bindings) {
		Binding* bind = b_itr.second;
		for (auto &e_itr : bind->m_events) {
			EventType sfmlEvent = (EventType)l_event.type;	// Compare the event that came in
			if (e_itr.first != sfmlEvent) { continue; }		// to each event we have bound

			// Keyboard button pressed
			if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp) {
				if (e_itr.second.m_code == l_event.key.code) {
					// Matching event/keystroke.          
					// Increase count.          
					if (bind->m_details.m_keyCode != -1) {
						bind->m_details.m_keyCode = e_itr.second.m_code;
					}
					++(bind->c);
					break;
				}
				// Mouse button pressed
			}
			else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp) {
				if (e_itr.second.m_code == l_event.mouseButton.button) {
					// Matching event/mouse button.          
					// Increase count.          
					bind->m_details.m_mouse.x = l_event.mouseButton.x;
					bind->m_details.m_mouse.y = l_event.mouseButton.y;
					if (bind->m_details.m_keyCode != -1) {
						bind->m_details.m_keyCode = e_itr.second.m_code;
					}
					++(bind->c);
					break;
				}
			}
			else {
				// No need for additional checking.   
				if (sfmlEvent == EventType::MouseWheel) {
					bind->m_details.m_mouseWheelDelta = l_event.mouseWheel.delta;
				}
				else if (sfmlEvent == EventType::WindowResized) {
					bind->m_details.m_size.x = l_event.size.width;
					bind->m_details.m_size.y = l_event.size.height;
				}
				else if (sfmlEvent == EventType::TextEntered) {
					bind->m_details.m_textEntered = l_event.text.unicode;
				}
				++(bind->c);
			}
		}
	}
}


void EventManager::Update() {
	if (!m_hasFocus) { return; }
	for (auto &b_itr : m_bindings) {
		Binding* bind = b_itr.second;
		for (auto &e_itr : bind->m_events) {
			switch (e_itr.first) {
			case(EventType::Keyboard):
				if (sf::Keyboard::isKeyPressed(
					sf::Keyboard::Key(e_itr.second.m_code)))
				{
					if (bind->m_details.m_keyCode != -1) {
						bind->m_details.m_keyCode = e_itr.second.m_code;
					}
					++(bind->c);
				}
				break;
			case(EventType::Mouse):
				if (sf::Mouse::isButtonPressed(
					sf::Mouse::Button(e_itr.second.m_code)))
				{
					if (bind->m_details.m_keyCode != -1) {
						bind->m_details.m_keyCode = e_itr.second.m_code;
					}
					++(bind->c);
				}
				break;
			case(EventType::Joystick):
				// Up for expansion.
				break;
			}
		}

		// If all triggers have happened to set off the event, call the method for the event
		if (bind->m_events.size() == bind->c) {
			// All callbacks for the current state
			auto stateCallbacks = m_callbacks.find(m_currentState);
			// StateType starts at 1, so (0) is invalid. These callbacks will be global ones, used everywhere, like window
			auto otherCallbacks = m_callbacks.find(StateType(0));

			if (stateCallbacks != m_callbacks.end()) {
				// Found the current state
				auto callItr = stateCallbacks->second.find(bind->m_name);
				if (callItr != stateCallbacks->second.end()) {
					// Found the name. Pass in event info
					callItr->second(&bind->m_details);
				}
			}

			if (otherCallbacks != m_callbacks.end()) {
				// Found the first state type
				auto callItr = otherCallbacks->second.find(bind->m_name);
				if (callItr != otherCallbacks->second.end()) {
					// Found the name. Pass in event info
					callItr->second(&bind->m_details);
				}
			}
		}
		bind->c = 0;
		bind->m_details.Clear();
	}
}

void EventManager::LoadBindings() {
	std::string delimiter = ":";

	// Find the keys config file
	std::ifstream bindings;
	bindings.open("keys.cfg");
	if (!bindings.is_open()) {
		std::cout << "! Failed loading keys.cfg." << std::endl;
		return;
	}

	// Read line by line
	std::string line;
	while (std::getline(bindings, line)) {
		std::stringstream keystream(line);
		std::string callbackName;
		keystream >> callbackName;	// First callbackName is Window_close rn
		Binding* bind = new Binding(callbackName); //Create a new binding, only hold the name in m_name right now
		while (!keystream.eof()) {	// Checking the stuff this Window_close is set up as
			std::string keyval;	
			keystream >> keyval;	// First value is 0:0 rn
			int start = 0;
			int end = keyval.find(delimiter);
			if (end == std::string::npos) {
				break;	// No more actions for this callback. Add what we have
			}
			EventType type = EventType(
				stoi(keyval.substr(start, end - start))); // Event type is the no. before the :
			int code = stoi(keyval.substr(end + delimiter.length(),
				keyval.find(delimiter, end + delimiter.length()))); // `code` is the no. after the :
			EventInfo eventInfo;
			eventInfo.m_code = code;	// Put the code into the event info
			bind->BindEvent(type, eventInfo); //event type and a eventinfo, containing the code
		}
		if (!AddBinding(bind)) { delete bind; }
		bind = nullptr;
	}
	bindings.close();
}
