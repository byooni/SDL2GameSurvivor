#pragma once

#include "Animation.h"
#include "globals.h"


class Character;

class WeaponComponent:public Animation
{
public:
	WeaponComponent();
	WeaponComponent(Graphics& graphics, Vector2 location);
	~WeaponComponent();
	void draw(Graphics& graphics);
	void update(float timeUpdate, Vector2 camera);

	void replace(float x, float y, Direction direction);

	virtual void animationComplete(std::string currentAnimation);
	virtual void setupAnimations();
private:
	//float dx, dy;
	Direction m_direction;
};

