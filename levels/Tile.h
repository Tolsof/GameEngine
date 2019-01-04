#pragma once
#include "../graphics/BatchRender.h"

struct Tile {
	bool m_collision;
	Renderable2D m_sprite;

	Tile(float pos_x, float pos_y, bool col)
		: m_sprite(pos_x, pos_y, 32, 32), m_collision(col) {}
};