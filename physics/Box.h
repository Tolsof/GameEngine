#pragma once

enum BOX_TYPE {
	COLLISION_BOX,
	HIT_BOX,
	HURT_BOX
};

struct CollisionProperties {
	BOX_TYPE m_type;
	bool m_damageable;

	unsigned int m_priority;
};

struct Box {
	float m_posX, m_posY;
	float m_width, m_height;
};

struct Circle {
	float& m_posX, m_posY;
	float radius;

	CollisionProperties m_properties;

	Circle(float x, float y, float r)
		: m_posX(x), m_posY(y), radius(r) {}
};