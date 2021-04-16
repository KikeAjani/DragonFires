#include "../../../../common/stdafx.h"
#include "world.h"
#include "../../../../common/core.h"
#include "../../../../common/sys.h"
#include "../../../../common/font.h"
#include "../Entities/Entity.h"
#include "../Entities/Components/linear_vel_comp.h"
#include "../Entities/Components/collision_comp.h"
#include "../Entities/Components/render_comp.h"
#include "../Entities/Components/input_movement_comp.h"
#include "../Entities/Components/player_life_comp.h"
#include "../Entities/Components/fire_comp.h"
#include "../Entities/Components/bullet_movement_comp.h"
#include "../Graphics/background.h"
#include "../Graphics/hud.h"

#include "graphics_engine.h"
#include <assert.h>
#include <cassert>

cWorld& cWorld::GetInstance()
{
	static cWorld world;
	return world;
}

cWorld::cWorld() : m_Entities(m_bMaxEntities)
	, m_Timer(1.0f / 60.0f)
	, m_pBackground(nullptr)
{
	m_Entities.clear();
}

void cWorld::Init()
{
	// Background creation.
	m_pBackground = new cBackground("data/test.png", vec2(128.f, 128.f));
	assert(m_pBackground != nullptr);
	// Registering renderable object in Graphics Engine.
	cGraphicsEngine::GetInstance().InsertRenderObj(*m_pBackground);

	m_pHud = new cHud();
	assert(m_pHud != nullptr);
	cGraphicsEngine::GetInstance().InsertRenderObj(*m_pHud);



	//PLAYER
	cEntity* pPlayerEnt = new cEntity(EntityType::PLAYER);
	vec2 PlayerSize(80.0f, 80.0f);
	cInputMovComp* pInputMovComp = new cInputMovComp();
	assert(pInputMovComp != nullptr);
	pInputMovComp->SetSize(PlayerSize);
	pPlayerEnt->AddComponent(*pInputMovComp);

	cLifeComponent* pLifeComp = new cLifeComponent(5);
	assert(pLifeComp != nullptr);
	pPlayerEnt->AddComponent(*pLifeComp);


	cCollisionComp* pCollComp = new cCollisionComp(40.0f);
	assert(pCollComp != nullptr);
	pPlayerEnt->AddComponent(*pCollComp);

	cRenderComp* pRenderComp = new cRenderComp("data/dragon.png", PlayerSize);
	assert(pRenderComp != nullptr);
	pPlayerEnt->AddComponent(*pRenderComp);

	cFireComp* pFireComp = new cFireComp(0.5f);
	assert(pFireComp != nullptr);
	pPlayerEnt->AddComponent(*pFireComp);

	m_Entities.push_back(pPlayerEnt);
	pPlayerEnt->Activate();





	// Init game state
	const float fMaxVelSpeed = 8.0f * 60.0f;	// Max vel. of ball. (pixels/sec.). 8 pixels x 60 slot executions per second.
	const float fRadius = 16.0F;
	for (size_t i = 0; i < m_bMaxEntities; i++) {
		cEntity *pEnt = new cEntity(EntityType::BALL);
		assert(pEnt != nullptr);


		cLifeComponent* pLifeComponent = new cLifeComponent(1);
		assert(pLifeComponent != nullptr);
		pEnt->AddComponent(*pLifeComponent);

		// Insert movement component.
		cLinearVelComp *pVelComp = new cLinearVelComp();
		assert(pVelComp != nullptr);
		pVelComp->SetPos(vec2(CORE_FRand(0.0f, SCR_WIDTH), CORE_FRand(0.0f, SCR_HEIGHT)));
		pVelComp->SetVel(vec2(CORE_FRand(-fMaxVelSpeed, +fMaxVelSpeed), CORE_FRand(-fMaxVelSpeed, +fMaxVelSpeed)));
		pEnt->AddComponent(*pVelComp);

		// Insert collision component.
		cCollisionComp *pCollComp = new cCollisionComp(fRadius);
		assert(pCollComp != nullptr);
		pEnt->AddComponent(*pCollComp);

		// Insert render component.
		cRenderComp *pRenderComp = new cRenderComp("data/Dragonballs.png", vec2(fRadius * 2.0f, fRadius * 2.0f));
		assert(pRenderComp != nullptr);
		pEnt->AddComponent(*pRenderComp);

		// Insert entity.
		m_Entities.push_back(pEnt);

		// Activation.
		pEnt->Activate();
	}
}

void cWorld::Terminate()
{
	for (cEntity* pEnt : m_Entities) {
		assert(pEnt != nullptr);
		// Deactivation.
		pEnt->Deactivate();
		delete pEnt;
	}
	m_Entities.clear();
	// Derregistering renderable object in Graphics Engine.
	cGraphicsEngine::GetInstance().DeleteRenderObj(*m_pBackground);
	delete m_pBackground;
}

void cWorld::Slot()
{
	// Calls to Timer to process logic slot.
	m_Timer.InitSlotsToProcess();
	while (m_Timer.ProcessSlots()) {
		// Call to world logic.
		EntitySlot(m_Timer.GetFixedTick());
	}
}

void cWorld::EntitySlot(double fTimeDiff)
{
	// Run entities
	for (cEntity* pEnt : m_Entities) {
		assert(pEnt != nullptr);
		if (pEnt->GetActivated()) {
			pEnt->Slot(fTimeDiff);
			if (pEnt->GetEntityType() == EntityType::PLAYER) {
				cLifeComponent *pLifeComp = pEnt->FindComponent<cLifeComponent>();
				int iTotalLifes = pLifeComp->GetLifes();
				m_pHud->SetTotalLifes(iTotalLifes);
			}
		}
		else {
			//If a entity was deactivated on the last Slot, erase it of m_Entities
			m_Entities.erase(std::remove(m_Entities.begin(), m_Entities.end(), pEnt), m_Entities.end());
		}
	}

}

void cWorld::AddBullet() {
	cInputMovComp* pInputMovComp = new cInputMovComp();
	for (cEntity *Entity : m_Entities) {
		if (Entity->GetEntityType() == EntityType::PLAYER) {
			pInputMovComp = Entity->FindComponent<cInputMovComp>();
			break;
		}
	}


	cEntity* pBullet = new cEntity(EntityType::BULLET);

	cLifeComponent* pLifeCompBullet = new cLifeComponent(1);
	assert(pLifeCompBullet != nullptr);
	pBullet->AddComponent(*pLifeCompBullet);

	
	cBulletMovementComp* cBulletMovement = new cBulletMovementComp(vec2(pInputMovComp->GetPos().x, pInputMovComp->GetPos().y+pInputMovComp->GetSize().y/6),500.0f);
	assert(cBulletMovement != nullptr);
	pBullet->AddComponent(*cBulletMovement);

	cCollisionComp* pCollComp = new cCollisionComp(20.0f);
	assert(pCollComp != nullptr);
	pBullet->AddComponent(*pCollComp);

	cRenderComp* pRenderComp = new cRenderComp("data/bullet2.png", vec2(20.0f * 2.0f, 20.0f * 2.0f));
	assert(pRenderComp != nullptr);
	pBullet->AddComponent(*pRenderComp);
	pBullet->Activate();
	m_Entities.push_back(pBullet);
}
