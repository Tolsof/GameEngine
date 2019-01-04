#pragma once

#include <list>
#include <queue>

#include "Action.h"

// TODO: Rename @addAction & @replaceAction

class InputHandler {
private:
	std::list<Action*> m_actionQueue;
public:
	// Add action places an action at the back of the queue
	// Acts as a buffer
	void addAction(Action* action);
	// Replace action places an action at the front of the queue
	// Overrides action that is currently being used
	void replaceAction(Action* action);
	void update(unsigned int frame);
	void handleAction(Player& player);
};