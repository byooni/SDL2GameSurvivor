
#ifndef GRAPHICS_HEADER
#define GRAPHICS_HEADER

#include <SDL.h>
#include "globals.h"
#include <map>
#include <string>
#include <vector>


struct SDL_Window;
struct SDL_Renderer;



class Graphics {
public:
	Graphics();
	
	~Graphics();
	SDL_Surface* loadImage(const std::string& filePath);
	SDL_Texture* loadTexture(const std::string& filePath);
	void blitSurface(SDL_Texture* texture, SDL_Rect* source, SDL_Rect* destinationSource);
	void renderText( std::string text, int x, int y, int numberFont);
	SDL_Texture* getTexture(std::string filePath);
	void loadTextures();
	void flip();
	void clear();


	SDL_Renderer* getRenderer() const { return m_renderer;};

private:
	
	TTF_Font* m_font;
	TTF_Font* m_bigfont;
	SDL_Color m_fontColor;
	std::map<std::string, SDL_Surface*> m_spriteSheets;
	std::map<std::string, SDL_Texture*> m_spriteSheetsTex;
	SDL_Window*   m_window;
	SDL_Renderer* m_renderer;
};

#endif

