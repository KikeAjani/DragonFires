#include "fire_comp.h"
#include <windows.h>
#include "../entity.h"
#include <assert.h>

#include "../../Managers/world.h"
void cFireComp::Slot(double fTimeDiff)
{
	fTimeSinceLastShot += fTimeDiff;
	if (KeyPressed(VK_UP) && fTimeSinceLastShot>=fMinTimeBetweenShots) {
		cWorld::GetInstance().AddBullet();
		fTimeSinceLastShot = 0;
	}
}

void cFireComp::ReceiveMsg(const cMessage& message)
{
}

bool cFireComp::KeyPressed(int key)
{
	return (GetKeyState(key) & 0x8000);
}