#ifndef SPRITE_H
#define SPRITE_H



#include <string>
#include <SDL.h>


class Graphics;

class Sprite
{
public:
	Sprite();
	Sprite(Graphics& graphics, const std::string& filePath, int x, int y, int width, int height, float posX, float posY);
	virtual ~Sprite();
	virtual void update();
	const SDL_Rect* getBoundingBox() const { return m_boundingBox; };
	void  setBoundingBox(SDL_Rect* newBox) {  m_boundingBox = newBox; };
	void draw(Graphics& graphics, int x, int y);

protected:
	SDL_Rect* m_boundingBox;
	SDL_Rect source;
	SDL_Texture* texture;
	float m_x, m_y;
};
#endif // SPRITE_H
