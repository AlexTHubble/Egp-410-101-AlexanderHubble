#include "InputSystem.h"

InputSystem::InputSystem(SpriteManager* spriteManager, UnitManager* unitManager, IDType aiSpriteID)
{
	mpSpriteManager = spriteManager;
	mpUnitManager = unitManager;
	mAiSpriteID = aiSpriteID;
}

InputSystem::~InputSystem()
{
	cleanup();
}

void InputSystem::init()
{
	mpMessageManager = new GameMessageManager();
}

void InputSystem::cleanup()
{
	delete mpMessageManager;
	mpMessageManager = NULL;
}

void InputSystem::update()
{
	SDL_PumpEvents();
	int x, y;
	SDL_GetMouseState(&x, &y);

	SDL_PumpEvents();

	//if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))
	//{
	//	Vector2D pos(x, y);
	//	GameMessage* pMessage = new PlayerMoveToMessage(pos);
	//	mpMessageManager->addMessage(pMessage, 0);
	//}



	{
		//get keyboard state
		const Uint8 *state = SDL_GetKeyboardState(NULL);

		if (state[SDL_SCANCODE_A])
		{
			GameMessage* pMessage = new SpawnRandomEnemyMessage(mpUnitManager,mpSpriteManager,mAiSpriteID, 10);
			mpMessageManager->addMessage(pMessage, 0);
		}

		if (state[SDL_SCANCODE_D])
		{
			GameMessage* pMessage = new DeleteRandomUnitMessage(mpUnitManager);
			mpMessageManager->addMessage(pMessage, 0);
		}

		//if escape key was down then exit the loop
		if (state[SDL_SCANCODE_ESCAPE])
		{

			GameMessage* pMessage = new ExitGameMessage();
			mpMessageManager->addMessage(pMessage, 0);
		}
	}

	mpMessageManager->processMessagesForThisframe();
}
