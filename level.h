#pragma once
#include "Graphics.h"
#include <unordered_map>
#include <cmath>
#include "Sprite.h"

class SDL_Texture;
class Level
{
public:
	Level();
	Level(Graphics& graphics, std::string mapName);
	~Level();

	void loadMapTexture(SDL_Texture* texture);

	void draw(Graphics& graphics);
	void update(float timeUpdate, Vector2 camera);
	

	
	
	std::map<int, std::vector<float>> generateChunk(int chunkX, int chunkY);
	void generateMap(Graphics& graphics, std::map<int, std::vector<float>>& map, int chunkX, int chunkY);


private:
	SDL_Texture* m_mapTexture;
	
	Vector2 m_camera;
	
	std::string m_mapName;
	std::map<int, std::vector<float>> m_chunk;
	std::unordered_map<std::string, std::map<int, std::vector<float>>> m_map;
};

