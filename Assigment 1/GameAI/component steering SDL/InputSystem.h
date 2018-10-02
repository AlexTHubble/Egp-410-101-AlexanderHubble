#pragma once
#include <sstream>
#include <SDL.h>


#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"
#include "GraphicsBufferManager.h"
#include "GraphicsSystem.h"
#include "GameMessageManager.h"
#include "Game.h"
#include "SpawnRandomEnemyMessage.h"
#include "DeleteRandomUnitMessage.h"
#include "ExitGameMessage.h"
//#include "SpriteManager.h"
//#include "UnitManager.h"


class InputSystem : public Trackable
{
public:
	InputSystem(SpriteManager* spriteManager, UnitManager* unitManager, IDType aiSpriteID);
	~InputSystem();

	void init();
	void cleanup();
	void update();

private:
	GameMessageManager * mpMessageManager;
	UnitManager * mpUnitManager;
	SpriteManager * mpSpriteManager;
	IDType mAiSpriteID;
};