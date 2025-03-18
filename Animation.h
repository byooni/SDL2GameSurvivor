#ifndef ANIMATION_H
#define ANIMATION_H

#include <map>
#include <string>
#include <vector>

#include "Sprite.h"
#include "globals.h"





class Animation : public Sprite {
public:
	Animation();
	Animation(Graphics& graphics, const std::string& filePath,  int x, int y, int width, int height, float posX, float posY, float updateTime);


	void playAnimation(const std::string& animation, bool once = false);
	void update(int time, Vector2 camera);
	void draw(Graphics& graphics, int x, int y);
	

private:
	std::map<std::string, std::vector<SDL_Rect>> m_animations;
	std::map<std::string, Vector2> m_offsets;

	int m_frameIndex;
	double m_time;
	bool m_isVisible;
	
protected:
	double m_timeToUpdate;
	bool m_currentAnimationOnce;
	std::string m_currentAnimation;


	void addAnimation(int frames, std::vector<int>  x, int y, std::string name, int widht, int height, Vector2 offset);
	void resetAnimation();
	void stopAnimation();
	void setVisible(bool visible) { m_isVisible = visible; };

	virtual void setupAnimations() = 0 ;
	virtual void animationComplete(std::string ccurrentAnimation) = 0  {};
};

#endif