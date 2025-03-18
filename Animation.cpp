#include "Animation.h"
#include "Graphics.h"
#include "Sprite.h"
#include <iostream>

Animation::Animation()
{
}

Animation::Animation(Graphics& graphics, const std::string& filePath,  int x, int y, int width, int height, float posX, float posY, float updateTime)
	: Sprite(graphics, filePath, x, y, width, height, posX, posY), 
	m_frameIndex(0),
	m_time(0),
	m_isVisible(true),
	m_timeToUpdate(updateTime),
	m_currentAnimationOnce(false),
	m_currentAnimation("")
{
	
}

void Animation::playAnimation(const std::string& animation, bool once)
{
	m_currentAnimationOnce = once;
	if (m_currentAnimation != animation) {
		m_currentAnimation = animation;
		m_frameIndex       = 0;
	}

}

void Animation::stopAnimation()
{
	m_frameIndex = 0;
	animationComplete(m_currentAnimation);
}


void Animation::update(int time, Vector2 camera)
{
	Sprite::update();
	for (auto it = m_offsets.begin(); it != m_offsets.end(); it++) {
		(*it).second = camera;
	}

	m_time += time;
	if (m_time > m_timeToUpdate) {
		m_time -= m_timeToUpdate;
		if (m_frameIndex < m_animations[m_currentAnimation].size() - 1) {
			m_frameIndex ++;

		} else {
			if (m_currentAnimationOnce) 
				setVisible(false);

			stopAnimation();
		}
	}
}

void Animation::draw(Graphics& graphics, int x, int y)
{
	if (m_isVisible) {
		m_boundingBox->x = m_x - m_offsets[m_currentAnimation].x;
		m_boundingBox->y = m_y - m_offsets[m_currentAnimation].y;
		m_boundingBox->w = source.w * globals::SPRITE_SCALE;
		m_boundingBox->h = source.h * globals::SPRITE_SCALE;

		
		SDL_Rect sourceRect = m_animations[m_currentAnimation][m_frameIndex];
		graphics.blitSurface(texture, &sourceRect, m_boundingBox);

	}
}


void Animation::addAnimation(int frames, std::vector<int>  x, int y, std::string name, int widht, int height, Vector2 offset)
{
	std::vector<SDL_Rect> rectangles;
	for (int i = 0; i < frames; i++) {
		SDL_Rect newRect = { x[i] * widht, y * height, widht, height};
		rectangles.push_back(newRect);
	}

	m_animations.insert(std::pair <std::string, std::vector<SDL_Rect> > (name, rectangles));
	m_offsets.insert(std::pair <std::string, Vector2> (name, offset));
		
}

void Animation::resetAnimation()
{
	m_animations.clear();
	m_offsets.clear();
}



