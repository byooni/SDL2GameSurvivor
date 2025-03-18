#include "Sprite.h"
#include "Graphics.h"
#include "globals.h"

#include <SDL_image.h>

Sprite::Sprite()
{
}

Sprite::Sprite(Graphics& graphics, const std::string& filePath,  int x, int y, int width, int height, float posX, float posY) : m_x(posX), m_y(posY)
{
	source.x = x;
	source.y = y;
	source.w = width;
	source.h = height;

	texture = graphics.getTexture(filePath);//SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
	if (texture == NULL)
		printf("Error unable to load Image");

	m_boundingBox = new SDL_Rect{ static_cast<int>(m_x + globals::SCREEN_WIDTH / 2 - source.w), 
		                          static_cast<int>(m_y + globals::SCREEN_HEIGHT / 2 - source.h), 
		                          source.w * globals::SPRITE_SCALE, 
		                          source.h * globals::SPRITE_SCALE };
}

Sprite::~Sprite()
{
	m_boundingBox = nullptr;
	delete m_boundingBox;
}

void Sprite::update()
{
	
}



void Sprite::draw(Graphics& graphics, int x, int y)
{
	SDL_Rect destinationRect{ x, y ,source.w * globals::SPRITE_SCALE , source.h * globals::SPRITE_SCALE };
	graphics.blitSurface(texture, &source, &destinationRect);
}


