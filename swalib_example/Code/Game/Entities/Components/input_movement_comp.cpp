#define KEY_LEFT 75
#define KEY_RIGHT 77
#include "input_movement_comp.h"
#include <windows.h>
#include "../Messages/new_pos_msg.h"
#include <assert.h>
#include "../entity.h"

cInputMovComp::cInputMovComp()
{
	m_vPos = vec2(SCR_WIDTH / 2, 50);
}

void cInputMovComp::Slot(double fTimeDiff)
{
	float movSpeed = 300.0f;
	float ExtraMov = movSpeed*static_cast<float>(fTimeDiff);

	if (KeyPressed(VK_LEFT) && (m_vPos.x - ExtraMov > 0 + m_vSize.x/6)) {
		m_vPos.x -= ExtraMov;
	}
	else if (KeyPressed(VK_RIGHT) && (m_vPos.x - ExtraMov < SCR_WIDTH - m_vSize.x / 6)) {
		m_vPos.x += ExtraMov;
	}
	cNewPosMsg msg(m_vPos);
	cEntity* pEnt = GetOwner();
	assert(pEnt != nullptr);
	pEnt->SendMsg(msg);
}

void cInputMovComp::ReceiveMsg(const cMessage& message)
{
}

bool cInputMovComp::KeyPressed(int key)
{
	return (GetKeyState(key) & 0x8000);
}

void cInputMovComp::SetSize(vec2 Size)
{
	m_vSize = Size;
}
