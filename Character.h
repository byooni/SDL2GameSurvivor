#ifndef CHARACTER_H
#define CHARACTER_H

#include "Animation.h"
#include "WeaponComponent.h"
#include "globals.h"




class Character : public Animation
{
public:
	Character();
	Character(Graphics& graphics, Vector2 location, Vector2 locationOnScreen);
	~Character();
	void draw(Graphics& graphics);
	void update(float timeUpdate, Vector2 camera);
	
	void end();

	void move(Direction direction);
	void gainHealth(int amount);
	void stopMove(bool x);
	void stopMoving();

	float getX() { return m_x; };
	float getY() { return m_y; };
	/*float getPosX() { return m_locationX; };
	float getPosY() { return m_locationY; };*/

	
	virtual void animationComplete(std::string currentAnimation);
	virtual void setupAnimations();

	const int getMaxHealth() const { return m_maxHealth; }
	const int getCurrentHealth() const { return m_currentHealth; }
	const Direction getDitection() const { return m_direction; }
	const WeaponComponent getWeapon() const { return m_weapon; }

private:
	bool m_end;
	float walkSpeed;
	int m_currentHealth;
	int m_maxHealth;
	float dx, dy;
	Direction m_direction;
	WeaponComponent m_weapon;
};

#endif