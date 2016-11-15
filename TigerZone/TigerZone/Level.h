#pragma once

#include <string>
#include <vector>

#include <Bengine/SpriteBatch.h>

const int TILE_WIDTH = 64;

class Level
{
public:
	// Load the level
	Level(const std::string& fileName);
	~Level();

	void draw();

	glm::vec2 cameraPos;

	// Getters
	int getWidth() const { return m_levelData[0].size(); }
	int getHeight() const { return m_levelData.size(); }
	const std::vector<std::string>& getLevelData() const { return m_levelData; }

private:
	void displayTile(int x, int y, char tile, int rotate);
	std::vector<std::string> m_levelData;
	Bengine::SpriteBatch m_spriteBatch;

};

