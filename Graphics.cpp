
#include "Graphics.h"
#include "globals.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#define NOMINMAX
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>



Graphics::Graphics()
{
	int16_t x  = (GetSystemMetrics(SM_CXSCREEN) - globals::SCREEN_WIDTH) / 2;
	int16_t y  = (GetSystemMetrics(SM_CYSCREEN) - globals::SCREEN_HEIGHT) / 2;
	
	m_window   = SDL_CreateWindow("Game", x, y, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	TTF_Init();
	loadTextures();
	m_font      = TTF_OpenFont("font/alagard.ttf", 36);
	m_bigfont   = TTF_OpenFont("font/alagard.ttf", 80);
	m_fontColor = { 255, 255, 255, 255 };

}

void Graphics::loadTextures()
{
	loadTexture("images/Character.png");
	loadTexture("images/EnemyChar.png");
	loadTexture("images/Box.png");
	loadTexture("images/ground.png");
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	m_renderer = NULL;


	m_font = nullptr;
	m_bigfont = nullptr;
	TTF_CloseFont(m_font);
	TTF_CloseFont(m_bigfont);
	TTF_Quit();
	
}

SDL_Surface* Graphics::loadImage(const std::string& filePath)
{
	if (m_spriteSheets.count(filePath) == 0)
		m_spriteSheets[filePath] = IMG_Load(filePath.c_str());
	return m_spriteSheets[filePath];
}

SDL_Texture* Graphics::loadTexture(const std::string& filePath)
{
	if (m_spriteSheetsTex.count(filePath) == 0)
		m_spriteSheetsTex[filePath] = SDL_CreateTextureFromSurface(getRenderer(), loadImage(filePath));
		std::cout << SDL_GetError();
	return m_spriteSheetsTex[filePath];
}

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* source, SDL_Rect* destinationSource)
{
	if (SDL_RenderCopy(m_renderer, texture, source, destinationSource))
	    std::cout << SDL_GetError();
}


void Graphics::renderText( std::string text, int x, int y, int numberFont) {
	TTF_Font* font = nullptr;

	switch (numberFont)
	{case 1:
		 font = m_font;
		break;
	case 2:
		 font = m_bigfont;
		break;
	default:
		font = nullptr;
		break;
	}

	SDL_Surface* fonstSurface = TTF_RenderText_Solid(font, text.c_str(), m_fontColor);
	SDL_Texture* fonstText    = SDL_CreateTextureFromSurface(m_renderer, fonstSurface);
	
	int fontW, fontH;
	SDL_QueryTexture(fonstText, NULL, NULL, &fontW, &fontH);
	SDL_Rect fontRect = { x  , y , fontW ,fontH };

	SDL_RenderCopy(m_renderer, fonstText, NULL, &fontRect);
	SDL_FreeSurface(fonstSurface);
	SDL_DestroyTexture(fonstText);
}

SDL_Texture* Graphics::getTexture(std::string filePath)
{
	return m_spriteSheetsTex[filePath];
}

void Graphics::flip()
{
	SDL_RenderPresent(m_renderer);
}

void Graphics::clear() 
{
	SDL_RenderClear(m_renderer);
}

