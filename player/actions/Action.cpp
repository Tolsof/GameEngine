#include "Action.h"
#include <iostream>

//#include "../Player.h"

void Action::doAction(Player & player) {
	switch (m_currentState)
	{
	case STARTUP_STATE:
		start_action(player);
		break;
	case DURATION_STATE:
		duration_action(player);
		break;
	case ENDLAG_STATE:
		endlag_action(player);
		break;
	default:
		break;
	}
}

unsigned int Action::nextFrame() {
	unsigned int f;
	switch (m_currentState)
	{
	case STARTUP_STATE:
		f = m_startUp;
		break;
	case DURATION_STATE:
		f = m_duration;
		break;
	case ENDLAG_STATE:
		f = m_endlag;
		break;
	default:
		break;
	}
	unsigned int nf = m_startFrame + f;
	return nf;
}
bool Action::shouldChange(unsigned int frame) {
	bool b = frame == nextFrame();
	return b;
}
bool Action::shouldDelete(unsigned int frame) {
	bool b = frame > m_startFrame + BUFFER_TIME;
	return b;
}
void Action::changeState(unsigned int frame) {
	switch (m_currentState)
	{
	case STARTUP_STATE:
		m_currentState = DURATION_STATE;
		m_startFrame = frame;
		break;
	case DURATION_STATE:
		m_currentState = ENDLAG_STATE;
		m_startFrame = frame;
		break;
	case ENDLAG_STATE:
		m_complete = true;
		break;
	default:
		break;
	}
}
void Action::update(unsigned int frame) {
	if (shouldChange(frame))
		changeState(frame);
}

void Dash::start_action(Player& player) {
	player.m_currentState = DASHING_STATE;
	player.m_velX = 0;
	player.m_direction = m_direction;
}

void Dash::duration_action(Player& player) {
	player.m_velX = 425 * player.m_direction;
}

void Dash::endlag_action(Player& player) {
	player.m_velX = 275 * player.m_direction;
	player.m_currentState = RUNNING_STATE;
}

void Jump::start_action(Player& player) {}
void Jump::duration_action(Player& player) {
	player.m_velY = 500;
}
void Jump::endlag_action(Player& player) {}