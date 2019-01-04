#include "InputHandler.h"
#include <iostream>

void InputHandler::addAction(Action* action) {
	// Do some stuff
	m_actionQueue.push_back(action);
	// Do some stuff
}
void InputHandler::replaceAction(Action* action) {
	if (!m_actionQueue.empty())
		m_actionQueue.pop_front();
	m_actionQueue.push_front(action);
}
void InputHandler::update(unsigned int frame) {
	// Check if should clear actions
	if (!m_actionQueue.empty()) {
		m_actionQueue.front()->update(frame);
		if (m_actionQueue.front()->m_complete) {
			m_actionQueue.pop_front();
			// Clear out any old actions
			while (!m_actionQueue.empty()) {
 				if (m_actionQueue.front()->shouldDelete(frame)) {
					m_actionQueue.pop_front();
				}
				else {
					// Make action current
					m_actionQueue.front()->m_startFrame = frame;
					break;
				}
			}
		}
	}
}
void InputHandler::handleAction(Player& player) {
	if (!m_actionQueue.empty())
		m_actionQueue.front()->doAction(player);
}