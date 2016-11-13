#include "Level.h"

#include <Bengine/BengineErrors.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <Bengine/ResourceManager.h>

Level::Level(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName);

	// Error checking
	if (file.fail()) Bengine::fatalError("Failed to open " + fileName);

	// Throw away the first string in tmp
	std::string temp;

	file >> temp;

	std::getline(file, temp); // Throw away the rest of the first line

	// Read the level data
	while (std::getline(file, temp)) m_levelData.emplace_back(temp);

	m_spriteBatch.init();
	m_spriteBatch.begin();	

	// Render all the tiles
	for (int y = 0; y < m_levelData.size(); y++)
	{
		for (int x = 0; x < m_levelData[y].size(); x+=2)
		{
			// Grab the tile
			int rotate = m_levelData[y][x];
			char tile = m_levelData[y][x+1];


			// Process the tile
			switch (tile)
			{
			case'.':
				break;
			default:
				displayTile(x, y, tile, rotate);
				break;
			}
		}
	}

	m_spriteBatch.end();
}


Level::~Level()
{
}

void Level::draw()
{
	m_spriteBatch.renderBatch();
}

void Level::displayTile(int x, int y, char tile, int rotate)
{
	std::stringstream ss;
	std::string s;
	ss << tile;
	ss >> s;

	// Get the destRect
	glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	Bengine::ColorRGBA8 whiteColor(255, 255, 255, 255);

	m_spriteBatch.draw(destRect,
		uvRect,
		Bengine::ResourceManager::getTexture("Textures/"+s+ ".png").id,
		0.0f,
		whiteColor,
		rotate * (3.14159265 / 2));
}