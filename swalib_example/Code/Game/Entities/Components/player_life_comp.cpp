#include "player_life_comp.h"
#include "../entity.h"
#include "../Messages/life_lost_msg.h"
int cLifeComponent::GetLifes()
{
	return m_Lifes;
}
void cLifeComponent::Slot(double fTimeDiff)
{
	if (m_Lifes==0 && GetOwner()->GetActivated())
	{
		cEntity* tEnt = GetOwner();
		tEnt->Deactivate();
		tEnt->SetActivated(false);
	}
}

void cLifeComponent::ReceiveMsg(const cMessage& message)
{
	const cLifeLostMsg* pLifeLostMsg = dynamic_cast<const cLifeLostMsg*>(&message);
	if (pLifeLostMsg !=nullptr) {
		if (m_Lifes > 0) {
			m_Lifes -= 1;
		}
	}
}
