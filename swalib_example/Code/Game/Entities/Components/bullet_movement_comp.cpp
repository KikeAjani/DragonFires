#include "bullet_movement_comp.h"
#include <assert.h>
#include "../Messages/new_pos_msg.h"
#include "../entity.h"
#include "input_movement_comp.h"
cBulletMovementComp::cBulletMovementComp(vec2 InitialPosition,float Velocity)
{
	m_vPos = InitialPosition;
	m_fVel = Velocity;

}

void cBulletMovementComp::Slot(double fTimeDiff)
{
	// Update position
	m_vPos.y += m_fVel * static_cast<float>(fTimeDiff);

	// Sending message because we've updated position.
	cNewPosMsg msg(m_vPos);
	cEntity* pEnt = GetOwner();
	assert(pEnt != nullptr);
	pEnt->SendMsg(msg);
}


void cBulletMovementComp::ReceiveMsg(const cMessage& message)
{

}
