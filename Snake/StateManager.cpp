#include "StateManager.h"



StateManager::StateManager(SharedContext *l_shared) : m_shared(l_shared)
{
	RegisterState<State_Intro>(StateType::Intro);
	RegisterState<State_MainMenu>(StateType::MainMenu);
	RegisterState<State_Game>(StateType::Game);
	RegisterState<State_Pause>(StateType::Pause);
}


StateManager::~StateManager()
{
	for (auto &itr : m_states) {
		itr.second->OnDestroy(); // Second is the 'BaseState' obj
		delete itr.second;
	}
}

void StateManager::Update(const sf::Time & l_time)
{
	if (m_states.empty()) 
		return;

	auto itr = m_states.end(); // .end is an iterator PAST the end. .back is the value of the true last element
								// .begin is an iterator pointing to the first element. front is value of first elem
	while (itr != m_states.begin() && itr->second->IsTranscendent)
		itr--;

	for (; itr != m_states.end(); itr++)
		itr->second->Update(l_time);

	// NOTE I did this is a different way to the example.
}

void StateManager::Draw()
{
	if (m_states.empty())
		return;
	
	// Find the most recently placed opaque state
	auto itr = m_states.end();
	while (itr != m_states.begin() && itr->second->IsTransparent) {
		itr--; // Can't see this, check the one placed before
	}

	// Now we're either at the first placed state (transparent or not)
	// Or the most recently placed visible state

	// Draw this state, and all the transparent ones on top of it
	for (; itr != m_states.end(); itr++)
		itr->second->Draw();

	// NOTE I did this is a different way to the example.
}

void StateManager::ProcessRequests()
{
	while (m_toRemove.begin != m_toRemove.end) { // There's stil states to remove
		RemoveState(*m_toRemove.begin);
		m_toRemove.erase(m_toRemove.begin);
	}
}

SharedContext * StateManager::GetSharedContext()
{
	return m_shared;
}

bool StateManager::HasState(const StateType & l_type)
{
	// Search through all the states we have
	for (auto itr = m_states.begin(); itr != m_states.end(); ++itr) { // .end is PAST the end. .back is the true last element
		if (itr->first == l_type) {	// If we find a match
			// Check if we're about to remove it.
			auto removed = std::find(m_toRemove.begin(), m_toRemove.end(), l_type);
			if (removed == m_toRemove.end())
				return true;	// no plans to remove this state. Yes it still exists
			return false;	// This state did exist but it'll be removed shortly
		} // else no match, check if the next state we have is the one asked for
	}
	return false;	// l_type isn't an existing state if there aren't any!
}

void StateManager::Remove(const StateType & l_type)
{
	m_toRemove.push_back(l_type);
}
