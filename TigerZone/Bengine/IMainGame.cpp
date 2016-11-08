#include "IMainGame.h"
#include "Timing.h"

#include "ScreenList.h"
#include "IGameScreen.h"

#include <algorithm>

namespace Bengine {

    IMainGame::IMainGame() {
        m_screenList = std::make_unique<ScreenList>(this);
    }

    IMainGame::~IMainGame() {
        // Empty
    }

    void IMainGame::run() {

        if (!init()) return;

		// Some helpful constants.
		const float DESIRED_FPS = 60.0f; // FPS the game is designed to run at
		const int MAX_PHYSICS_STEPS = 6; // Max number of physics steps per frame
		const float MS_PER_SECOND = 1000; // Number of milliseconds in a second
		const float DESIRED_FRAMETIME = MS_PER_SECOND / DESIRED_FPS; // The desired frame time per frame
		const float MAX_DELTA_TIME = 1.0f; // Maximum size of deltaTime

        FpsLimiter fpsLimiter;
		fpsLimiter.setMaxFPS(DESIRED_FPS);
		float previousTicks = SDL_GetTicks();

        // Game loop
        m_isRunning = true;
        while (m_isRunning) {
			fpsLimiter.begin();

			// Calculate the frame time in milliseconds
			float newTicks = SDL_GetTicks();
			float frameTime = newTicks - previousTicks;
			previousTicks = newTicks; // Store newTicks in previousTicks so we can use it next frame

			// get total delta time
			float totalDeltaTime = frameTime / DESIRED_FRAMETIME;

            inputManager.update();

			int i = 0; // This counter makes sure we don't spiral to death
			// Loop while we still have steps to process
			while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS)
			{
				// the delata time should be the smaller of the totalDeltaTime and MAX_DELTA_TIME
				float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
				// Call the custom update and draw method
				update(deltaTime);
				// since we took a step that is length deltaTime, subtract from totalDeltaTime
				totalDeltaTime -= deltaTime;
				// increment our frame counter so we can limit to MAX_PHSYSICS_STEPS
				i++;
			}
            if (m_isRunning) {
                draw();

				m_fps = fpsLimiter.end();
                m_window.swapBuffer();
            }
        }

    }

    void IMainGame::exitGame() {
        m_currentScreen->onExit();
        if (m_screenList) {
            m_screenList->destroy();
            m_screenList.reset();
        }
        m_isRunning = false;
    }

    void IMainGame::onSDLEvent(SDL_Event& evnt) {
        switch (evnt.type) {
            case SDL_QUIT:
                exitGame();
                break;
            case SDL_MOUSEMOTION:
                inputManager.setMouseCoords((float)evnt.motion.x, (float)evnt.motion.y);
                break;
            case SDL_KEYDOWN:
                inputManager.pressKey(evnt.key.keysym.sym);
                break;
            case SDL_KEYUP:
                inputManager.releaseKey(evnt.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
                inputManager.pressKey(evnt.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                inputManager.releaseKey(evnt.button.button);
                break;
        }
    }

    bool IMainGame::init() {
        Bengine::init();

        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

        if (!initSystems()) return false;

        onInit();
        addScreens();

        m_currentScreen = m_screenList->getCurrent();
        m_currentScreen->onEntry();
        m_currentScreen->setRunning();

        return true;
    }

    bool IMainGame::initSystems() {
		m_window.create("Default", 1280, 720, 0);
        return true;
    }


    void IMainGame::update(float deltaTime) {
        if (m_currentScreen) {
            switch (m_currentScreen->getState()) {
                case ScreenState::RUNNING:
                    m_currentScreen->update(deltaTime);
                    break;
                case ScreenState::CHANGE_NEXT:
                    m_currentScreen->onExit();
                    m_currentScreen = m_screenList->moveNext();
                    if (m_currentScreen) {
                        m_currentScreen->setRunning();
                        m_currentScreen->onEntry();
                    }
                    break;
                case ScreenState::CHANGE_PREVIOUS:
                    m_currentScreen->onExit();
                    m_currentScreen = m_screenList->movePrevious();
                    if (m_currentScreen) {
                        m_currentScreen->setRunning();
                        m_currentScreen->onEntry();
                    }
                    break;
                case ScreenState::EXIT_APPLICATION:
                    exitGame();
                    break;
                default:
                    break;
            }
        } else {
            exitGame();
        }
    }

    void IMainGame::draw() {
        glViewport(0, 0, m_window.getScreenWidth(), m_window.getScreenHeight());
        if (m_currentScreen && m_currentScreen->getState() == ScreenState::RUNNING) {
            m_currentScreen->draw();
        }
    }
}