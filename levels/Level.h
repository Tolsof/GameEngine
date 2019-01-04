#pragma once
#include "../graphics/BatchRender.h"
#include "Tile.h"
#include <vector>
#include "glm\glm.hpp"
#include "../physics/Box.h"

enum LEVEL
{
	LEVEL_ONE
};

struct Level {
	BatchRender2D m_levelRender;
	std::vector<Tile> m_tileMap;

	int m_width, m_height;

	Box colBox;

	// Camera
	// Enemies
	// Boss
	// Triggers?

	Level() : m_levelRender(GL_STATIC_DRAW) {}

	void init();
};