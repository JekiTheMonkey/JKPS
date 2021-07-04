#pragma once

#include "Command.hpp"
#include "CommandQueue.hpp"
#include "KeyCombination.hpp"

#include <SFML/Window/Event.hpp>

#include <vector>
#include <map>
#include <string>
#include <algorithm>


class User
{
	public:
		enum Action
		{
			ChangeMode,
			IncreaseKeys,
			DecreaseKeys,
			ResetStatistics,
			Button0,
			Button1,
			Button2,
			Button3,
			Button4,
			Button5,
			Button6,
			Button7,
			Button8,
			Button9,
			ViewKey,
			ActionCount
		};


	public:
		User();

		void handleEvent(const sf::Event& event, CommandQueue& commands);
		void handleRealtimeInput(CommandQueue& commands);

		sf::Keyboard::Key getAssignedKey(Action action) const;


	private:
		void initializeActions();
		static bool isRealtimeAction(Action action);


	private:
		std::map<KeyCombination, Action> mKeyBinding;
		std::map<Action, Command> mActionBinding;
};