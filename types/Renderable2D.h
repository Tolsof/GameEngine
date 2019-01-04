#pragma once

struct VertexData {
	float vertices = 3 * 4 * sizeof(float);
};

struct Renderable2D {
	float m_posX, m_posY;
	unsigned int m_width, m_height;
	unsigned int m_spriteFrame;

	Renderable2D(float x, float y, unsigned int w, unsigned int h) :
		m_posX(x), m_posY(y), m_width(w), m_height(h) {
		m_spriteFrame = 0;
	}
};