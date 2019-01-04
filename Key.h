#pragma once

struct Key {
	int m_value;
	unsigned int m_pressedFrame;

	Key(int v, unsigned int f) : m_value(v), m_pressedFrame(f) {}
};