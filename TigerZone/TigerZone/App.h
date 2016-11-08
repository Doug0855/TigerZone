#pragma once

#include <Bengine/IMainGame.h>
#include "GameplayScreen.h"

class App : public Bengine::IMainGame
{
public:
	App();
	~App();

	// Called on initlialization
	virtual void onInit() override;
	// For adding all screens
	virtual void addScreens() override;
	// CAlled when exiting
	virtual void onExit() override;
private:
	std::unique_ptr<GameplayScreen> m_gameplayScreen = nullptr;
};

