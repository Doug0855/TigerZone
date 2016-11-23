#include "GameplayScreen.h"

#include <SDL\SDL.h>
#include <Bengine\IMainGame.h>
#include <Bengine/Timing.h>
#include <Bengine/ResourceManager.h>

#include "ScreenIndices.h"

GameplayScreen::GameplayScreen(Bengine::Window* window) : m_window(window)
{
	m_screenIndex = SCREEN_INDEX_GAMEPLAY;
}

GameplayScreen::~GameplayScreen()
{
	delete m_level;
}

int GameplayScreen::getNextScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

int GameplayScreen::getPreviousScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

void GameplayScreen::build()
{

}

void GameplayScreen::destroy()
{

}

void GameplayScreen::onEntry()
{

	// init shaders
	initShaders();

	// initialize spritebatch0
	m_spriteBatch.init();

	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());

	initLevel();
	m_camera.setPosition(m_level->cameraPos);
	/*
	Tile tile1(19);
	TileStack tStack;
	tStack.shuffle();
	Player player1;
	Player player2;
	std::pair<int, int> startingCoordinates = std::pair<int, int>(72, 72);
	Tile *startTile = new Tile(tile1.getNum());
	gameboard.place_tile(startingCoordinates, *startTile);
	gameId = "123";
	*/
}

void GameplayScreen::onExit()
{

}

void GameplayScreen::update(float deltaTime)
{
	checkInput(deltaTime);
	/*
		Tile currentTile = tileStack.tiles[m_i];
		if (m_i % 2 == 0) {
			// player1 turn
			std::cout << "It's your turn with tile of type " << currentTile.getType() << std::endl;
			std::vector<std::pair<int, int> > availableLocations = gameboard.display_positions(currentTile);
			std::cout << "There are " << availableLocations.size() << " available locations for this tile" << std::endl;
			for (int k = 0; k < availableLocations.size(); k++) {
				std::cout << k << ") " << availableLocations[k].first << ' ' << availableLocations[k].second << std::endl;
			}
			// Take in where the user would like to place the tile
			int placementSelection;
			std::cin >> placementSelection;
			// Create vector of that pair to pass to optimalLocation(), need to keep as param vector bc this is specific scenario where we know exact coordinates
			std::vector< std::pair<int, int> > placementLocation;
			placementLocation.push_back(availableLocations[placementSelection]);
			// Create a new pointer to a new tile of the same type as the currentTile
			Tile *tmpTile = new Tile(currentTile.getNum());
			// Properly rotate the tile so it may be placed
			std::pair<int, int> optimalLocation = gameboard.getOptimalPlacement(*tmpTile, placementLocation);
			// Place the new tile
			gameboard.place_tile(optimalLocation, *tmpTile);

			printToTextFile(gameboard);
		}
		else {
			// computer turn for solo play, player2 turn for tournament play
			std::vector<std::pair<int, int> > availableLocations = gameboard.display_positions(currentTile);
			Tile *tmpTile = new Tile(currentTile.getNum());
			std::pair<int, int> optimalLocation = gameboard.getOptimalPlacement(*tmpTile, availableLocations);
			gameboard.place_tile(optimalLocation, *tmpTile);
			std::cout << "Computer placed tile of type " << tmpTile->getType() << " at location " << optimalLocation.first << ' ' << optimalLocation.second << std::endl;

			printToTextFile(gameboard);
		}
		m_i++;
		*/
	updateLevel();
	m_camera.update();
}

void GameplayScreen::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(255.0f, 255.0f, 255.0f, 1.0f);

	m_textureProgram.use();

	// Upload texture Uniform
	GLuint textureUniform = m_textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);

	// Camera matrix
	glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
	GLuint pUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	m_spriteBatch.begin();

	m_level->draw();

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_textureProgram.unuse();

}


void GameplayScreen::initLevel()
{
	m_level = new Level("Levels/level.txt");
}

void GameplayScreen::initShaders()
{
	// compile texture
	m_textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");
	m_textureProgram.linkShaders();
}

void GameplayScreen::checkInput(float deltaTime)
{
	// Update inputmanager
	m_inputManager.update();
	const float CAMERA_SPEED = 10.0f;
	const float SCALE_SPEED = 0.1f;

	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		m_game->onSDLEvent(evnt);
		switch (evnt.type)
		{
		case SDL_QUIT:
			onExitClicked(CEGUI::EventArgs());
			break;
		case SDL_KEYDOWN:
			m_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			m_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		}
	}
	if (m_inputManager.isKeyDown(SDLK_w)) {
		m_camera.setPosition(m_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
	}
	if (m_inputManager.isKeyDown(SDLK_s)) {
		m_camera.setPosition(m_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
	}
	if (m_inputManager.isKeyDown(SDLK_a)) {
		m_camera.setPosition(m_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
	}
	if (m_inputManager.isKeyDown(SDLK_d)) {
		m_camera.setPosition(m_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
	}
	if (m_inputManager.isKeyDown(SDLK_q)) {
		m_camera.setScale(m_camera.getScale() + SCALE_SPEED);
	}
	if (m_inputManager.isKeyDown(SDLK_e)) {
		m_camera.setScale(m_camera.getScale() - SCALE_SPEED);
	}

}

void GameplayScreen::play()
{
	
}

void GameplayScreen::updateLevel()
{
	m_level = new Level("Levels/level.txt");
}

bool GameplayScreen::onExitClicked(const CEGUI::EventArgs& e) {
	m_currentState = Bengine::ScreenState::EXIT_APPLICATION;
	return true;
}

void GameplayScreen::printToTextFile(Board gameboard)
{
	std::ofstream out_data("Levels/level.txt");
	out_data << "Level:" << std::endl;
	for (auto& inner : gameboard.m_board)
	{
		for (auto& item : inner)
		{
			if (item != NULL)
				out_data << item->getRotations() << item->getType();
			else
				out_data << '0' << '.';

		}
		out_data << std::endl;
	}
	out_data.close();
}