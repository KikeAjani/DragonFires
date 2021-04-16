#include "../../../../../common/stdafx.h"
#include "collision_comp.h"
#include <assert.h>
#include "../entity.h"
#include "../../Managers/world.h"
#include ".././../../../../common/sys.h"
#include "../Messages/collision_msg.h"
#include "../Messages/new_pos_msg.h"
#include "../Messages/life_lost_msg.h"

cCollisionComp::cCollisionComp(float fRadius) : m_fRadius(fRadius)
	, m_vPos(0.0f, 0.0f)
{
}

void cCollisionComp::Slot(double fTimeDiff)
{
	fTimeSinceLastBallColl += fTimeDiff;
	// Slot detecting collisions.
	cEntity *pOwnEnt = GetOwner();
	assert(pOwnEnt != nullptr);
	cEntity *pCollEnt = nullptr;
	vec2 vColl(0.0f);
	for (cEntity* pEnt : cWorld::GetInstance().GetEntities()) {
		assert(pEnt != nullptr);
		if (pOwnEnt != pEnt) {
			cCollisionComp *pCollCompEnt = pEnt->FindComponent<cCollisionComp>();
			if (pCollCompEnt == nullptr) {
				continue;
			}
			float flimit2 = (m_fRadius + pCollCompEnt->GetRadius()) * (m_fRadius + pCollCompEnt->GetRadius());
			vColl = pCollCompEnt->GetPos() - m_vPos;
			if (vlen2(vColl) <= flimit2) {
				pCollEnt = pEnt;
				break;
			}
		}
	}


	// Sending message because we've detected collision with other entity.
	if (pCollEnt != nullptr) {
		//Ball and Bullet collision = Sub Life to Ball and Bullet. 
		if (pOwnEnt->GetEntityType() == EntityType::BALL && pCollEnt->GetEntityType() == EntityType::BULLET) {
			cLifeLostMsg msgBallBullet;
			pOwnEnt->SendMsg(msgBallBullet);
			pCollEnt->SendMsg(msgBallBullet);
		}
		else {
			// Rebound!
			cEntCollisionMsg msg(*pCollEnt, vColl);
			pOwnEnt->SendMsg(msg);
			//Player and Ball collision = Sub Life to Player, Ball rebounded last step
			if (pOwnEnt->GetEntityType() == EntityType::PLAYER && pCollEnt->GetEntityType() == EntityType::BALL) {
				//To avoid multiple hits by the same ball while both are in contact (example: push the ball with the player)
				//we ensure that it passed more than 0.3seconds since the last contact with the last ball that hit the player
				if (!(fTimeSinceLastBallColl < 0.3f && pLastBallColl == pCollEnt)) {
					cLifeLostMsg newMsg;
					pOwnEnt->SendMsg(newMsg);
					//Reset last contact info
					fTimeSinceLastBallColl = 0.0f;
				}
				pLastBallColl = pCollEnt;

			}
		}
	}

	// Rebound on margins
	__int8 uLimit = 0;
	if (m_vPos.x > SCR_WIDTH) {
		uLimit = cLimitWorldCollMsg::eType::LIMIT_X_POS;
	}
	else if (m_vPos.x < 0) {
		uLimit = cLimitWorldCollMsg::eType::LIMIT_X_NEG;
	}
	if (m_vPos.y > SCR_HEIGHT) {
		uLimit |= cLimitWorldCollMsg::eType::LIMIT_Y_POS;
	}
	else if (m_vPos.y < 0) {
		uLimit |= cLimitWorldCollMsg::eType::LIMIT_Y_NEG;
	}
	// Sending message because we've detected margin collision.
	if (uLimit != 0) {
		cLimitWorldCollMsg msg(uLimit);
		pOwnEnt->SendMsg(msg);
	}


}

void cCollisionComp::ReceiveMsg(const cMessage &message)
{
	const cNewPosMsg *pMsg = dynamic_cast<const cNewPosMsg *>(&message);
	if (pMsg != nullptr) {
		m_vPos = pMsg->GetPos();
		return;
	}
}
