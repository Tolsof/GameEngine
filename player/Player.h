#pragma once
#include "../graphics/BatchRender.h"
#include "../physics/Box.h"

enum PLAYER_STATE {
	STANDING_STATE,
	RUNNING_STATE, // -> MOVING_STATE???
	DASHING_STATE,
	STOPPING_STATE
};

enum FACING {
	FACING_LEFT = -1,
	FACING_RIGHT = 1
};

struct Player
{
	Renderable2D sprite;
	PLAYER_STATE m_currentState;
	FACING m_direction = FACING_RIGHT;

	Box m_col;

	bool m_canAct = true;

	// Collision
	// Hitbox
	// Hurtbox

	float m_velX = 0;
	float m_velY = 0;

	Player();
};