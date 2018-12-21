#include "EventManager.h"

EventManager::EventManager() : m_hasFocus(true)
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
	if (m_bindings.find(l_binding->m_name) != m_bindings.end())
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

void EventManager::SetFocus(const bool & l_focus)
{
	m_hasFocus = l_focus;
}
