#ifndef ENEMYCHARACTER_H
#define ENEMYCHARACTER_H
#include "Animation.h"
#include "globals.h"


class Character;

enum Movememt: int {
	straigh = 0,
	sinusoida,
	spiral
};

class EnemyCharacter : public Animation
{
public:
	EnemyCharacter(Graphics& graphics, std::string filePath, int sourceX, int sourceY,int width, int height, Vector2 spawnPoint, int timeToUpdate);

	virtual void update(int elapsedTime, Character& player);
	virtual void draw(Graphics& graphics);
	virtual void touchPlayer(Character& player) = 0;

	const inline int getMaxHealth() const     { return this->m_maxHealth; }
	const inline int getCurrentHealth() const { return this->m_currentHealth; }
	void setWalkSpeed(float newSpeed)          { m_walkSpeed = newSpeed; };
protected:
	Direction m_directionRL;
	Direction m_directionUD;
	float m_walkSpeed;

	int m_maxHealth;
	int m_currentHealth;

};

class Enemy : public EnemyCharacter {
public:
	Enemy();
	Enemy(Graphics& graphics, Vector2 spawnPoint, Movememt movement);

	void update(int elapsedTime, Character& player, Vector2 camera);
	void draw(Graphics& graphics);
	void touchPlayer(Character& player);

	void animationComplete(std::string currentAnimation);
	void setupAnimations();
private:
	Movememt m_movement;
	float m_startingX;
	float m_startingY;
	bool  m_shouldMoveUp;

};

#endif