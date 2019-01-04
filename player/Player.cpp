#include "Player.h"

Player::Player() 
	: sprite(0.0f, 0.0f, 32, 32) {
	m_col.m_posX = 0;
	m_col.m_posY = 0;
	m_col.m_height = 32;
	m_col.m_width = 32;
}