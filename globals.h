#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>



namespace globals {
	const int16_t SCREEN_WIDTH  = 1200;
	const int16_t SCREEN_HEIGHT = 1024;
	const int16_t CHUNK_SIZE    = 32;
	const int16_t PLAYER_SIZE   = 20;
	const int16_t SPRITE_SCALE  = 6;
	const int16_t TILE_SIZE     = 62;
}

enum Direction {
	left,
	right,
	up,
	down,
	upL,
	upR,
	downR,
	downL,
};

struct Vector2 {
	int x, y;
	Vector2() :x(0), y(0) {}
	Vector2(int x, int y) :x(x), y(y) {}
	Vector2 zero() { return Vector2(0, 0);
	}
};