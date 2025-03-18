#include "WeaponComponent.h"
#include "Character.h"
#include "Graphics.h"
#include <iostream>

WeaponComponent::WeaponComponent()
{
}

WeaponComponent::WeaponComponent(Graphics& graphics, Vector2 location) :
	Animation(graphics, "images/Box.png", 0, 0, 16, 16, location.x, location.y, 100),
	m_direction(right)
{
	//graphics.loadImage("images/Box.png");

	setupAnimations();
	playAnimation("idle");
}

WeaponComponent::~WeaponComponent()
{
}

void WeaponComponent::draw(Graphics& graphics)
{
	Animation::draw(graphics, m_x, m_y);
}

void WeaponComponent::update(float timeUpdate, Vector2 camera)
{
	
	Animation::update(timeUpdate, camera);
}

void WeaponComponent::replace(float x, float y, Direction direction)
{
	m_x = x;
	m_y = y;
	switch (direction)
	{
	case left:
		playAnimation("idle");

		break;
	case right:
		playAnimation("idle");
		break;
	case up:
		playAnimation("idle");
		break;
	case down:
		playAnimation("idle");
		break;
	default:
		break;
	}

}

void WeaponComponent::animationComplete(std::string currentAnimation)
{
}

void WeaponComponent::setupAnimations()
{
	Vector2 spawn{ 0, 0 };
	addAnimation(3, std::vector<int> {0,1,2}, 0, "idle", 100, 100, spawn);
}
