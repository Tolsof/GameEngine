#pragma once
#include <queue>

#include "levels\Level.h"
#include "player\Player.h"
#include "player\actions\Action.h"

#include "player\actions\InputHandler.h"
#include "Key.h"

struct Game {
	enum State {
		MENU_STATE = 0,
		PLAY_STATE,
		PAUSE_STATE
	};

	LEVEL current_level;
	State m_currentState;

	InputHandler inputHandler;
	bool m_pressedKeys[1024];
	std::queue<int> m_moveKeys;
	std::queue<int> m_modKeys;
	std::queue<int> m_actionKeys;
	std::vector<int> m_comboKeys;

	Level level;

	std::vector<Level> m_levels;

	Player player;

	BatchRender2D m_spriteRender;
	Batcher2D batcher;

	Game() : m_spriteRender(GL_DYNAMIC_DRAW) {}

	void processInput(int frame);
	void update(float dt, int frame);
	void draw();

	void init();
};