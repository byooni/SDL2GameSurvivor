#include "level.h"
#include "globals.h"


Level::Level()
{
}
Level::~Level()
{

}


Level::Level(Graphics& graphics, std::string mapName) :  m_mapName(mapName)
{
	loadMapTexture(graphics.getTexture(mapName));//загрузка спрайтов локации
}


void Level::loadMapTexture(SDL_Texture* texture)
{
	m_mapTexture = texture;//SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(m_mapName));
}

void Level::draw(Graphics& graphics)
{
	// Определяем видимые чанки
	Vector2 startChunk, endChunk;
	startChunk.x = (m_camera.x / globals::TILE_SIZE) / globals::CHUNK_SIZE - 1;
	startChunk.y = (m_camera.y / globals::TILE_SIZE) / globals::CHUNK_SIZE - 1;
	endChunk.x   = (m_camera.x + globals::SCREEN_WIDTH) / globals::TILE_SIZE / globals::CHUNK_SIZE + 1;
	endChunk.y   = (m_camera.y + globals::SCREEN_HEIGHT) / globals::TILE_SIZE / globals::CHUNK_SIZE + 1;

	// Генерация и отрисовка видимых чанков
	for (int Y = startChunk.y; Y <= endChunk.y; ++Y) {
		for (int X = startChunk.x; X <= endChunk.x; ++X) {
			std::string chunkKey = std::to_string(X) + "," + std::to_string(Y);
			if (m_map.find(chunkKey) == m_map.end()) {
				m_map[chunkKey] = generateChunk(X, Y);
			}
			generateMap(graphics, m_map[chunkKey], X, Y);
		}
	}
}

void Level::update(float timeUpdate , Vector2 camera)
{
	m_camera = camera;
	
}


std::map<int, std::vector<float>> Level::generateChunk(int chunkX, int chunkY)
{
	std::map<int, std::vector<float>> genmap;
	genmap[globals::CHUNK_SIZE] = { std::vector<float>(globals::CHUNK_SIZE) };
	for (int y = 0; y < globals::CHUNK_SIZE; ++y) {
		for (int x = 0; x < globals::CHUNK_SIZE; ++x) {
			int worldX = chunkX * globals::CHUNK_SIZE + x;
			int worldY = chunkY * globals::CHUNK_SIZE + y;
			genmap[y].push_back((float)rand() / RAND_MAX); //noise(worldX, worldY)
		}
	}
	return genmap;
}

void Level::generateMap(Graphics& graphics, std::map<int, std::vector<float>>& map, int chunkX, int chunkY)
{
	for (int y = 0; y < globals::CHUNK_SIZE; ++y) {
		for (int x = 0; x < globals::CHUNK_SIZE; ++x) {
			float value = map[y][x];

			SDL_Color color;
			SDL_Rect soursceRect;
			int spriteSize = 62;
			if (value < 0.2f) {
				soursceRect = { 2 * spriteSize, 2 * spriteSize, spriteSize, spriteSize }; // Трава
			}
			else if (value < 0.5f) {
				soursceRect = { 5 * spriteSize,  2 * spriteSize, spriteSize, spriteSize }; // Трава
			}
			else if (value < 0.7f) {
				soursceRect = { 0  , 2 * spriteSize, spriteSize, spriteSize }; // Трава
			}
			else if (value < 0.9f) {
				soursceRect = { 7 * spriteSize, 2 * spriteSize, spriteSize, spriteSize }; // Трава
			}
			else {
				soursceRect = {0 , 3 * spriteSize, spriteSize, spriteSize }; // земля
			}

			
			int screenX = (chunkX * globals::CHUNK_SIZE + x) * globals::TILE_SIZE - m_camera.x;
			int screenY = (chunkY * globals::CHUNK_SIZE + y) * globals::TILE_SIZE - m_camera.y;
			SDL_Rect rect = { screenX, screenY, globals::TILE_SIZE, globals::TILE_SIZE };
			graphics.blitSurface(m_mapTexture, &soursceRect, &rect);
		}
	}
}
