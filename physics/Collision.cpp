#include "Collision.h"

bool Collision::checkCollision(Renderable2D r1, Box a
	, Renderable2D r2, Box b) {
	bool collisionX = r1.m_posX + a.m_posX + a.m_width >= b.m_posX &&
		b.m_posX + b.m_width >= r1.m_posX + a.m_posX;
	// Collision y-axis?
	bool collisionY = r1.m_posY + a.m_posY + a.m_height >= b.m_posY &&
		b.m_posY + b.m_height >= r1.m_posY + b.m_posY;

	return collisionX && collisionY;
}