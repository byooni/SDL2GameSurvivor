#pragma once

#include "Character.h"
#include "Graphics.h"
#include "level.h"

#include <unordered_map>
#include <cmath>


struct SDL_KeyboardEvent;
struct SDL_Rect;
struct SDL_Window;
struct SDL_Renderer;
class Level;
class Enemy;


class GameEngine {
public:
	GameEngine();
	~GameEngine();

private:
	bool gameLoop();
	void restart();
	void keyHandler(SDL_KeyboardEvent key, bool isDown);
	void update(float time);
	void chekInputs();
	void chekEnemies(Graphics& graphics, float timeUpdate);
	void draw(Graphics& graphics);
	void drawHud(Graphics& graphics);

	//SDL_Window* m_window;
	//SDL_Renderer* m_renderer;
	Graphics   m_graphics;
	std::vector<Enemy> m_enemies;
	Level      m_level;
	Character  m_player;
	Vector2    m_camera;
	bool      m_endGame;
	bool      m_restart;
	
	std::map<SDL_Scancode, bool> m_heldKeys;
	

};