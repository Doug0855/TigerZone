#pragma once

#include "Level.h"
#include "Tile_Structure/Tile.h"
#include "Tile_Structure/Block.h"
#include "Tile_Structure/Face.h"
#include "Tile_Structure/TileStack.h"
#include "Game.h"
#include "Board.h"
#include <Bengine/IGameScreen.h>
#include <Bengine/InputManager.h>
#include <vector>
#include <Bengine/SpriteBatch.h>
#include <Bengine/GLSLProgram.h>
#include <Bengine/Camera2D.h>
#include <Bengine/GLTexture.h>
#include <Bengine/Window.h>

#include <Bengine/GUI.h>

class GameplayScreen : public Bengine::IGameScreen
{
public:
	GameplayScreen(Bengine::Window* window);
	~GameplayScreen();

	virtual int getNextScreenIndex() const override;

	virtual int getPreviousScreenIndex() const override;

	virtual void build() override;

	virtual void destroy() override;

	virtual void onEntry() override;

	virtual void onExit() override;

	virtual void update(float deltaTime) override;

	virtual void draw() override;

	Board gameboard;

private:
	void initLevel(); /// sets up level
	void initShaders(); // inits shaders
	void checkInput(float deltaTime);
	void play();
	void updateLevel();
	bool onExitClicked(const CEGUI::EventArgs& e);
	void printToTextFile(Board gameboard);

	int m_i = 0;
	std::string gameId;
	Player player1;
	Player player2;
	TileStack tileStack;
	Tile* currentTile;

	Level* m_level;

	Bengine::InputManager m_inputManager;

	Bengine::SpriteBatch m_spriteBatch;
	Bengine::SpriteBatch m_backgroundSpriteBatch;

	Bengine::GLSLProgram m_textureProgram;
	Bengine::GLTexture m_texture;

	Bengine::Camera2D m_camera;
	Bengine::Camera2D m_backgroundCamera;


	Bengine::Window* m_window;
};