#include "Game.h"
#include "GLFW/glfw3.h"

#include <iostream>

void Game::processInput(int frame) {
	// if state = 
	switch (player.m_currentState) {
	case STANDING_STATE:
		if (!m_moveKeys.empty()) {
			int key = m_moveKeys.front();
			m_moveKeys.pop();
			switch (key) {
			case GLFW_KEY_D:
				inputHandler.addAction(new Dash(frame, FACING_RIGHT));
				break;
			case GLFW_KEY_A:
				inputHandler.addAction(new Dash(frame, FACING_LEFT));

				break;
			default:
				break;
			}
		}
		if (!m_actionKeys.empty()) {
			int key = m_actionKeys.front();
			m_actionKeys.pop();
			switch (key) {
			case GLFW_KEY_SPACE:
				inputHandler.replaceAction(new Jump(frame));
				break;
			default:
				break;
			}
		}
		break;
	case DASHING_STATE:
		if (!m_actionKeys.empty()) {
			int key = m_actionKeys.front();
			m_actionKeys.pop();
			switch (key) {
			case GLFW_KEY_SPACE:
				inputHandler.replaceAction(new Jump(frame));
				break;
			default:
				break;
			}
		}
		if (!m_moveKeys.empty()) {
			int key = m_moveKeys.front();
			m_moveKeys.pop();
			switch (key) {
			case GLFW_KEY_D:
				inputHandler.addAction(new Dash(frame, FACING_RIGHT));
				break;
			case GLFW_KEY_A:
				inputHandler.addAction(new Dash(frame, FACING_LEFT));
			default:
				break;
			}
		}
		break;
	case RUNNING_STATE:
		if (!m_actionKeys.empty()) {
			int key = m_actionKeys.front();
			m_actionKeys.pop();
			switch (key) {
			case GLFW_KEY_SPACE:
				inputHandler.addAction(new Jump(frame));
				break;
			default:
				break;
			}
		}
		if (!m_moveKeys.empty()) {
			int key = m_moveKeys.front();
			m_moveKeys.pop();
			switch (key)
			{
			case GLFW_KEY_D:
				if (player.m_direction == FACING_LEFT) {
					// turn around state
					player.m_direction = FACING_RIGHT;
					player.m_velX *= -1;
				}
				break;
			case GLFW_KEY_A:
				if (player.m_direction == FACING_RIGHT) {
					// turn around state
					player.m_direction = FACING_LEFT;
					player.m_velX *= -1;
				}
				break;
			default:
				break;
			}
		}

		if (!m_pressedKeys[GLFW_KEY_D] && player.m_direction == FACING_RIGHT) {
			if (m_pressedKeys[GLFW_KEY_A]) {
				// Turn around state
				player.m_direction = FACING_LEFT;
				player.m_velX *= -1;
			}
			else {
				// Stopping state
				player.m_currentState = STANDING_STATE;
				player.m_velX = 0;
			}
			break;
		}
		if (!m_pressedKeys[GLFW_KEY_A] && player.m_direction == FACING_LEFT) {
			if (m_pressedKeys[GLFW_KEY_D]) {
				// Turn Around State
				player.m_direction = FACING_RIGHT;
				player.m_velX *= -1;
			}
			else {
				// Stopping state
				player.m_currentState = STANDING_STATE;
				player.m_velX = 0;
			}
			break;
		}
		break;
	default:
		break;
	}
}

void Game::update(float dt, int frame) {
	processInput(frame);
	inputHandler.handleAction(player);
	inputHandler.update(frame);

	// Update Enemies (handle enemy input)
	// Check Hitbox/Hurtbox
	// apply hitbox/hurtbox

	// Update Player (Velocity/Damage/LevelCollision/Etc)
	// Update Enemies (Velocity/Damage/LevelCollision/Etc)

	player.m_velY -= 1.75f;
	player.sprite.m_posY += player.m_velY * dt;
	player.sprite.m_posX += player.m_velX * dt;

	// check collision
	bool collisionX = player.sprite.m_posX + player.m_col.m_posX + player.m_col.m_width >= level.colBox.m_posX &&
		level.colBox.m_posX + level.colBox.m_width >= player.sprite.m_posX + player.m_col.m_posX;
	bool collisionY = player.sprite.m_posY + player.m_col.m_posY + player.m_col.m_height >= level.colBox.m_posY &&
		level.colBox.m_posY + level.colBox.m_height >= player.sprite.m_posY + player.m_col.m_posY;
	if (collisionX && collisionY) {
		player.sprite.m_posY = 32;
		player.m_velY = 0;
	}
}

void Game::draw() {
	// if state = play
	batcher.set(m_spriteRender);
	batcher.fill(m_spriteRender, player.sprite);
	batcher.draw(m_spriteRender);
	batcher.clear(m_spriteRender);
	batcher.set(level.m_levelRender);
	batcher.draw(level.m_levelRender);
}

void Game::init() {

	batcher.load(m_spriteRender);
	batcher.load(level.m_levelRender);
	batcher.set(level.m_levelRender);
	for (int i = 0; i < 30; i++) {
		level.m_tileMap.push_back(Tile(32 * i, 0, true));
	}
	for (auto sprite : level.m_tileMap) {
		batcher.fill(level.m_levelRender, sprite.m_sprite);
	}

	level.colBox.m_posX = 0;
	level.colBox.m_posY = 0;
	level.colBox.m_width = 32 * 30;
	level.colBox.m_height = 32;

	player.sprite.m_posX = 0;
	player.sprite.m_posY = 40;
}