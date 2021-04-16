#pragma once
#include "component.h"
class cFireComp :  public cComponent
{
private:
	float fTimeSinceLastShot;
	float fMinTimeBetweenShots;
public:
	cFireComp(float MinTime) {
		fMinTimeBetweenShots = MinTime;
		fTimeSinceLastShot = MinTime + 1.0f; //To let player shot at the beggining
	}

	virtual void Slot(double fTimeDiff) override;
	virtual void ReceiveMsg(const cMessage& message) override;

	bool KeyPressed(int key);

};

