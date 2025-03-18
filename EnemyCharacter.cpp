#include "EnemyCharacter.h"
#include "Character.h"

#include <iostream>




EnemyCharacter::EnemyCharacter(Graphics& graphics, std::string filePath, int sourceX, int sourceY, int width, int height, Vector2 spawnPoint, int timeToUpdate)
	:Animation(graphics, filePath, sourceX, sourceY, width, height, spawnPoint.x, spawnPoint.y, timeToUpdate),
	m_directionRL(left),
	m_maxHealth(0),
	m_currentHealth(0),
	m_walkSpeed(0.5f)
{
}

void EnemyCharacter::update(int elapsedTime, Character& player)
{
	

	Animation::update(elapsedTime, Vector2{ static_cast<int>(player.getX()),static_cast<int>(player.getY()) });
}

void EnemyCharacter::draw(Graphics& graphics)
{
	Animation::draw(graphics, m_x, m_y);
}


Enemy::Enemy(Graphics& graphics, Vector2 spawnPoint, Movememt movement) :
	EnemyCharacter(graphics, "images/EnemyChar.png", 0, 0, 16, 16, spawnPoint, 140),
	m_startingX(spawnPoint.x),
	m_startingY(spawnPoint.y),
	m_shouldMoveUp(false),
	m_movement(movement)
{
	setupAnimations();
	playAnimation("RunLeft");
}

void Enemy::update(int elapsedTime, Character& player, Vector2 camera)
{
	m_directionRL = player.getX() + globals::SCREEN_WIDTH  / 2 - globals::PLAYER_SIZE > m_x ? right : left;
	m_directionUD = player.getY() + globals::SCREEN_HEIGHT / 2 - globals::PLAYER_SIZE > m_y ? up    : down;

	float dx = player.getX() + globals::SCREEN_WIDTH / 2 - globals::PLAYER_SIZE - m_x;
	float dy = player.getY() + globals::SCREEN_HEIGHT / 2 - globals::PLAYER_SIZE - m_y;
	float distance = std::sqrt(dx * dx + dy * dy);
	abs(dx) < abs(dy)
		? playAnimation(m_directionUD == up ? "RunDown" : "RunUp")
		: playAnimation(m_directionRL == right ? "RunRight" : "RunLeft");
	
	float angle;
	float perpendicularAngle;
	float freq = 10.0f;
	float magnitude = 0.4f;

	
	if (distance > 0) {
		

		switch (m_movement)
		{
		case straigh:
			m_x += (dx / distance) * m_walkSpeed;
			m_y += (dy / distance) * m_walkSpeed;

			break;
		case sinusoida:
			m_x += (dx / distance) * m_walkSpeed;
			m_y += (dy / distance) * m_walkSpeed;
			angle = std::atan2(dy, dx);
			perpendicularAngle = angle + M_PI / 2;
			if (abs(dx) < abs(dy)) {
				m_x += magnitude * std::sin(freq * elapsedTime) * std::cos(perpendicularAngle);
			}
			else {
				m_y += magnitude * std::sin(freq * elapsedTime) * std::sin(perpendicularAngle);
			}

			break;
		case spiral:
			m_x += (dx / distance) * m_walkSpeed;
			m_y += (dy / distance) * m_walkSpeed;
			angle = std::atan2(dy, dx);
			perpendicularAngle = angle + 3.1415927f / 2;
			m_x += std::cos(perpendicularAngle);
			m_y += std::sin(perpendicularAngle);
			
			break;
		default:
			break;
		}
	}

	EnemyCharacter::update(elapsedTime, player);
}

void Enemy::draw(Graphics& graphics)
{
	EnemyCharacter::draw(graphics);
}

void Enemy::touchPlayer(Character& player)
{
	player.gainHealth(-1);
}

void Enemy::animationComplete(std::string currentAnimation)
{
}

void Enemy::setupAnimations()
{
	Vector2 spawn{ 0,0 };
	//addAnimation(3, 2, 32, "RunLeft", 16, 16, Vector2(0, 0));
	//addAnimation(3, 2, 48, "RunRight", 16, 16, Vector2(0, 0));
	addAnimation(4, std::vector<int> {0, 1, 2, 3}, 2, "RunLeft", 16, 16, spawn);
	addAnimation(4, std::vector<int> {0, 1, 2, 3}, 6, "RunRight", 16, 16, spawn);
	addAnimation(4, std::vector<int> {0, 1, 2, 3}, 4, "RunUp", 16, 16, spawn);
	addAnimation(4, std::vector<int> {0, 1, 2, 3}, 0, "RunDown", 16, 16, spawn);
}


