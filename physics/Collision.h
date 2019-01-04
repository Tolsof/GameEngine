#pragma once
#include "Box.h"
#include "../graphics/BatchRender.h"

struct Collision {
	bool checkCollision(Renderable2D r1, Box a
		, Renderable2D r2, Box b);

	bool geometryCollision(Renderable2D r1, Box a, Box level);
};

