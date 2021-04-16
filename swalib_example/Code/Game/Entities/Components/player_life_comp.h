#pragma once
#include "component.h"

class cLifeComponent : public cComponent
{

private:
	int m_Lifes;

public:
	cLifeComponent(int InitLifes) {
		m_Lifes = InitLifes;
	}

	int GetLifes();
private:
	virtual void Slot(double fTimeDiff) override;
	virtual void ReceiveMsg(const cMessage& message) override;


};

