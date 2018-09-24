#include "SpawnRandomEnemyMessage.h"
#include "Unit.h"
#include "UnitManager.h"
#include "SpriteManager.h"

SpawnRandomEnemyMessage::SpawnRandomEnemyMessage( UnitManager* unitManager, SpriteManager* spriteManager, IDType spriteId)
	:GameMessage(SPAWN_RANDOM_ENEMEY)
{
	mpUnitManager = unitManager;
	mpSpriteManager = spriteManager;
	mAiSpriteId = spriteId;
}

SpawnRandomEnemyMessage::~SpawnRandomEnemyMessage()
{
}

void SpawnRandomEnemyMessage::process()
{
	Unit* pUnit = mpUnitManager->createRandomUnit(*mpSpriteManager->getSprite(mAiSpriteId));
}
