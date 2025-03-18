#include "GameEngine.h"
#include "Animation.h"
#include "globals.h"
#include "EnemyCharacter.h"


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


#define NOMINMAX
//#include <windows.h>
#include <thread>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

const Uint32 FPS = 60;
const Uint32 MAX_FRAME_TIME = 6 * 1000 / FPS;
const Uint32 MAX_UNITS      = 100;
const float MAX_UNITS_SPEED = 4.0f;
Uint32   enemiesCount = 1;
float newspeed = 0.5f;
int   currentScorePoints = 0;
int   scorePoints = 0;


GameEngine::GameEngine()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m_enemies.reserve(MAX_UNITS);

	/*Mix_Chunk* chargeSfx = Mix_LoadWAV("res/sfx/charge.mp3");
	Mix_Chunk* swingSfx = Mix_LoadWAV("res/sfx/swing.mp3");
	Mix_Chunk* holeSfx = Mix_LoadWAV("res/sfx/hole.mp3");*/
	while (true)
	{
		if (gameLoop()) {
			restart();
		}
		else {
			return ;
		}
	}
	
}

GameEngine::~GameEngine()
{
	TTF_Quit();
}

bool GameEngine::gameLoop()
{
	SDL_Event event;

	Vector2 spawnloc{ (globals::SCREEN_WIDTH - globals::PLAYER_SIZE) / 2, (globals::SCREEN_HEIGHT - globals::PLAYER_SIZE) / 2 };
	m_player = Character(m_graphics, spawnloc, spawnloc);
	m_level  = Level(m_graphics, "images/ground.png");
	
	m_endGame = false;
	m_restart = false;
	bool isHover = false;

	Uint32 lastUpdateTime = SDL_GetTicks();
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				if (!m_endGame) {
					if (event.key.repeat == 0) {
						keyHandler(event.key, true);
					}
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					m_restart = true;
					quit      = true;
				}
				
				break;
			case SDL_KEYUP:
				keyHandler(event.key, false);
				break;
			case SDL_MOUSEMOTION:
				
				//std::cout << "X" << event.motion.x << std::endl;
				//std::cout << "Y" << event.motion.y << std::endl;
				break;
			default:
				break;
			}
		}



		const Uint32 currentTime = SDL_GetTicks();
		Uint32 elapsedTime = currentTime - lastUpdateTime;
		
		update(std::min(elapsedTime, MAX_FRAME_TIME));
		lastUpdateTime = currentTime;
		if (m_player.getCurrentHealth() <= 0) {
			m_player.end();
			m_endGame = true;
		}

		draw(m_graphics);
	}


	if (m_restart)
		return true;

	return false;
}

void GameEngine::restart()
{
	enemiesCount = 1;
	newspeed = 0.5f;
	currentScorePoints = 0;
	scorePoints = 0;
	m_enemies.clear();
	
}

void GameEngine::update(float time)
{
	m_camera.x = m_player.getX() + globals::SCREEN_WIDTH / 2 - globals::SCREEN_WIDTH + globals::PLAYER_SIZE;
	m_camera.y = m_player.getY() + globals::SCREEN_HEIGHT / 2 - globals::SCREEN_HEIGHT + globals::PLAYER_SIZE;

	m_level.update(time, m_camera);
	m_player.update(time, m_camera);
	

	if (scorePoints > currentScorePoints) {
		enemiesCount = enemiesCount + 1;
		currentScorePoints += 500;
		newspeed = static_cast<float>(enemiesCount / 10.f);

	}

	chekInputs();
	chekEnemies(m_graphics, time);
	
}


void GameEngine::draw(Graphics& graphics) 
{
	graphics.clear();
	
	m_level.draw(graphics);

	std::for_each(std::begin(m_enemies), std::end(m_enemies), [&](Enemy character) { character.draw(graphics); });

	m_player.draw(graphics);

	std::string score{ "Score: " + std::to_string(scorePoints) };
	if (!m_endGame) {
		graphics.renderText(score, 0, 0, 1);
	}
	else {
		graphics.renderText(score, (globals::SCREEN_WIDTH - score.size() - 300) / 2,
			                       (globals::SCREEN_HEIGHT) / 2,
			                        2);
	}

	graphics.flip();
}


void GameEngine::keyHandler(SDL_KeyboardEvent key, bool isDown) {
	switch (key.keysym.scancode)
	{
	case SDL_SCANCODE_A:
		if (isDown) {
			m_player.move(Direction::left);
			m_heldKeys[SDL_SCANCODE_A] = true;
		}
		else {
			m_heldKeys[SDL_SCANCODE_A] = false;
		}
		break;
	case SDL_SCANCODE_W:
		if (isDown) {
			m_player.move(Direction::up);
			m_heldKeys[SDL_SCANCODE_W] = true;
		}
		else {
			m_heldKeys[SDL_SCANCODE_W] = false;
		}

		break;
	case SDL_SCANCODE_S:
		if (isDown) {
			m_player.move(Direction::down);
			m_heldKeys[SDL_SCANCODE_S] = true;
		}
		else {
			m_heldKeys[SDL_SCANCODE_S] = false;
		}		
		break;
	case SDL_SCANCODE_D:
		if (isDown) {
			m_player.move(Direction::right);
			m_heldKeys[SDL_SCANCODE_D] = true;
		}
		else {
			m_heldKeys[SDL_SCANCODE_D] = false;
		}
		break;
	default:
		break;
	};
}

void GameEngine::chekInputs()
{
	if (m_heldKeys[SDL_SCANCODE_W])
		m_player.move(Direction::up);
	else if (m_heldKeys[SDL_SCANCODE_S])
		m_player.move(Direction::down);
	else if (m_heldKeys[SDL_SCANCODE_A])
		m_player.move(Direction::left);
	else if (m_heldKeys[SDL_SCANCODE_D])
		m_player.move(Direction::right);


	if (!m_heldKeys[SDL_SCANCODE_S] && !m_heldKeys[SDL_SCANCODE_W])
		m_player.stopMove(false);

	if (!m_heldKeys[SDL_SCANCODE_D] && !m_heldKeys[SDL_SCANCODE_A])
		m_player.stopMove(true);
}

void GameEngine::chekEnemies(Graphics& graphics, float timeUpdate)
{
	auto func = [&](Enemy& enemy) {
		enemy.update(timeUpdate, m_player, m_camera);
		enemy.setWalkSpeed(std::min(newspeed, MAX_UNITS_SPEED));
		if (SDL_HasIntersection(enemy.getBoundingBox(), m_player.getBoundingBox())) {
			enemy.touchPlayer(m_player);
		}
		if (SDL_HasIntersection(enemy.getBoundingBox(), m_player.getWeapon().getBoundingBox())) {
			scorePoints += 100;
			return true;
		}
		else
			return false;
	};
	m_enemies.erase(std::remove_if(m_enemies.begin(), m_enemies.end(), func), m_enemies.end());

	int enemyCurrent = std::min(enemiesCount, MAX_UNITS);
	if (m_enemies.size() < enemyCurrent) {
		Vector2 enemySpawn{ static_cast<int>(m_player.getX() + rand() % globals::SCREEN_WIDTH), static_cast<int>(m_player.getY() - 100) };
		while (enemyCurrent != m_enemies.size()) {
			int side = rand() % 4;

			switch (side) {
			case 0: // Слева
				enemySpawn.x = m_player.getX() - 100;
				enemySpawn.y = m_player.getY() + rand() % globals::SCREEN_HEIGHT;
				break;
			case 1: // Справа
				enemySpawn.x = m_player.getX() + globals::SCREEN_WIDTH + 100;
				enemySpawn.y = m_player.getY() + rand() % globals::SCREEN_HEIGHT;
				break;
			case 2: // Сверху
				enemySpawn.x = m_player.getX() + rand() % globals::SCREEN_WIDTH;
				enemySpawn.y = m_player.getY() - 100;
				break;
			case 3: // Снизу
				enemySpawn.x = m_player.getX() + rand() % globals::SCREEN_WIDTH;
				enemySpawn.y = m_player.getY() + globals::SCREEN_HEIGHT + 100;
				break;
			}
			Enemy enemy = Enemy(graphics, enemySpawn, static_cast<Movememt>(rand() % 3));
			enemy.setWalkSpeed(std::min(newspeed, MAX_UNITS_SPEED));
			m_enemies.push_back(enemy);
		}
	}
}