#include "Character.h"
#include "WeaponComponent.h"
#include "Graphics.h"
#include <iostream>


Character::Character()
{
}

Character::Character(Graphics& graphics, Vector2 location, Vector2 locationOnScreen) :
	Animation(graphics, "images/Character.png", 0, 0, globals::PLAYER_SIZE, globals::PLAYER_SIZE, locationOnScreen.x, locationOnScreen.y, 100),
	dx(0),
	dy(0),
	m_direction(right), 
	m_currentHealth(3),
	m_maxHealth(3),
	m_end(false),
	walkSpeed(0.2f)
{
	//graphics.loadImage("images/Character.png");
	m_weapon = WeaponComponent{ graphics, Vector2{ 0,0 }};
	setupAnimations();
	move(m_direction);
	playAnimation("idleRight");
}

Character::~Character()
{
	
}

void Character::setupAnimations()
{
	
	Vector2 spawn{ 0,0 };
	int h = 100;
;
	int w = 125;
	addAnimation(1, std::vector<int> {1}, 1, "idleLeft", h, w, spawn);
	addAnimation(1, std::vector<int> {1}, 2, "idleRight", h, w, spawn);
	addAnimation(1, std::vector<int> {1}, 3, "idleUp", h, w, spawn);
	addAnimation(1, std::vector<int> {1}, 0, "idleDown", h, w, spawn);
	addAnimation(4, std::vector<int> {1, 0, 1, 2}, 1, "RunLeft", h, w, spawn);
	addAnimation(4, std::vector<int> {1, 0, 1, 2}, 2, "RunRight", h, w, spawn);
	addAnimation(4, std::vector<int> {1, 0, 1, 2}, 3, "RunUp", h, w, spawn);
	addAnimation(4, std::vector<int> {1, 0, 1, 2}, 0, "RunDown", h, w, spawn);
}


void Character::draw(Graphics& graphics)
{
	if (!m_end)
	    m_weapon.draw(graphics);
	Animation::draw(graphics, m_x, m_y); //рисуем относительно от экрана
}

void Character::update(float timeUpdate, Vector2 camera)
{
	m_x += dx * timeUpdate;
	m_y += dy * timeUpdate;
	if (!m_end)
	    m_weapon.update(timeUpdate, camera);
	Animation::update(timeUpdate, camera);
}

void Character::end()
{
	m_end = true;
	SDL_Rect box{ 0,0,0,0 };
	m_weapon.setBoundingBox(&box);
	Vector2 spawn{ 0,0 };
	playAnimation("idleUp", true);
}

void Character::move(Direction direction)
{
	switch (direction)
	{
	case left:
		dx = -walkSpeed;
		playAnimation("RunLeft");
		m_direction = direction;
		m_weapon.replace(-getBoundingBox()->h + m_x, m_y, m_direction);
		break;
	case right:
		dx = walkSpeed;
		playAnimation("RunRight");
		m_direction = direction;
		m_weapon.replace(getBoundingBox()->h + m_x, m_y, m_direction);
		break;
	case up:
		dy = -walkSpeed;
		playAnimation("RunUp");
		m_direction = direction;
		m_weapon.replace( m_x, -getBoundingBox()->h + m_y, m_direction);
		break;
	case down:
		dy = walkSpeed;
		playAnimation("RunDown");
		m_direction = direction;
		m_weapon.replace(m_x, getBoundingBox()->h + m_y, m_direction);
		break;
	case downR:
		playAnimation("RunDown");
		m_direction = direction;
		m_weapon.replace(getBoundingBox()->w + m_x - globals::PLAYER_SIZE, getBoundingBox()->h + m_y - globals::PLAYER_SIZE, m_direction);
		break;
	case downL:
		playAnimation("RunDown");
		m_direction = direction;
		m_weapon.replace(-getBoundingBox()->w + m_x + globals::PLAYER_SIZE, getBoundingBox()->h + m_y - globals::PLAYER_SIZE, m_direction);
		break;
	case upR:
		playAnimation("RunUp");
		m_direction = direction;
		m_weapon.replace(getBoundingBox()->w + m_x - globals::PLAYER_SIZE, -getBoundingBox()->h + m_y + globals::PLAYER_SIZE, m_direction);
		break;
	case upL:
		playAnimation("RunUp");
		m_direction = direction;
		m_weapon.replace(-getBoundingBox()->w + m_x + globals::PLAYER_SIZE, -getBoundingBox()->h + m_y  + globals::PLAYER_SIZE, m_direction);
		break;

	default:
		break;
	}
	
}

void Character::gainHealth(int amount) {
	m_currentHealth += amount;
}



void Character::stopMove(bool x)
{
	if (x)
	   dx = 0.0f;
	else 
	   dy = 0.0f;

	if (dy == 0 && dx == 0) {
		stopMoving();
	}
}

void Character::stopMoving()
{
	switch (m_direction)
	{
	case left:
		playAnimation("idleLeft");
		break;
	case right:
		playAnimation("idleRight");
		break;
	case up:
		playAnimation("idleUp");
		break;
	case down:
		playAnimation("idleDown");
		break;
	default:
		break;
	}
}

void Character::animationComplete(std::string currentAnimation) {}

