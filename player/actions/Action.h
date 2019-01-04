#pragma once
#define BUFFER_TIME 12

#include "../Player.h"

// Notes:
/*
Should buffer time be inside an action?
Constant buffer time?
*/

enum CURRENT_ACTION_STATE {
	STARTUP_STATE,
	DURATION_STATE,
	ENDLAG_STATE
};

struct Action {
	CURRENT_ACTION_STATE m_currentState = STARTUP_STATE;

	unsigned int m_startUp;
	unsigned int m_duration;
	unsigned int m_endlag;

	bool m_complete;

	unsigned int m_startFrame;

	virtual void start_action(Player& player) = 0;
	virtual void duration_action(Player& player) = 0;
	virtual void endlag_action(Player& player) = 0;
	// run if action is removed?
	// virtual void cleanUp(Player& player) = 0;
	
	void doAction(Player& player);

	unsigned int nextFrame();
	bool shouldChange(unsigned int frame);
	bool shouldDelete(unsigned int frame);
	void changeState(unsigned int frame);
	void update(unsigned int frame);

	// If an action has any properties, it must be active for at least 1 frame
	Action(unsigned int s, unsigned int d, unsigned int e, unsigned int f)
		: m_startUp(s), m_duration(d), m_endlag(e), m_startFrame(f) {
		m_complete = false;
	}
};

struct Dash : public Action {
	FACING m_direction;

	Dash(unsigned int f, FACING d) : Action(3, 10, 0, f), m_direction(d) {}

	virtual void start_action(Player& player) override;
	virtual void duration_action(Player& player) override;
	virtual void endlag_action(Player& player) override;
};

struct Jump : public Action {
	Jump(unsigned int f) : Action(4, 1, 0, f)  {}

	virtual void start_action(Player& player) override;
	virtual void duration_action(Player& player) override;
	virtual void endlag_action(Player& player) override;
};