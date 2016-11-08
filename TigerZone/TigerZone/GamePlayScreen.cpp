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

GameplayScreen::~GameplayScreen(){
	
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

	// initialize spritebatch
	m_spriteBatch.init();

	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());

	initLevel();
}

void GameplayScreen::onExit()
{

}

void GameplayScreen::update(float deltaTime)
{
	checkInput(deltaTime);
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

	
	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_textureProgram.unuse();

}


void GameplayScreen::initLevel()
{
	
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

}

bool GameplayScreen::onExitClicked(const CEGUI::EventArgs& e) {
	m_currentState = Bengine::ScreenState::EXIT_APPLICATION;
	return true;
}