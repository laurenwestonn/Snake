#pragma once
#include "BaseState.h"
#include <unordered_map>
#include <functional>
#include "Window.h"
#include "EventManager.h"
#include "SharedContext.h"
#include "State_Intro.h"
#include "State_MainMenu.h"
#include "State_Game.h"
#include "State_Pause.h"

enum class StateType {
	Intro = 1,
	MainMenu,
	Game,
	Pause,
	Gameover,
	Credits
};

using StateContainer = std::vector<std::pair<StateType, BaseState*>>;
using TypeContainer = std::vector<StateType>;
using StateFactory = std::unordered_map<StateType, std::function<BaseState* (void)>>;

class StateManager
{
public:
	StateManager(SharedContext *l_shared);
	~StateManager();

	void Update(const sf::Time& l_time);
	void Draw();

	void ProcessRequests(); // ensures no states are removed that are being used

	SharedContext* GetSharedContext();
	bool HasState(const StateType& l_type);

	void SwitchTo(const StateType& l_type);
	void Remove(const StateType& l_type);

private:

	void CreateState(const StateType& l_type);
	void RemoveState(const StateType& l_type);

	// Lambda expression. Each state factory links a state to a fn
	template<class T>
	void RegisterState(const StateType& l_type) {
		m_stateFactory[l_type] = [this]() -> BaseState*
		{
			return new T(this);
		};
	}

	SharedContext* m_shared;
	StateContainer m_states;
	TypeContainer m_toRemove;
	StateFactory m_stateFactory;
};

