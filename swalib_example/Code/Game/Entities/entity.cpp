#include "entity.h"
#include "Components/component.h"

cEntity::~cEntity()
{
	m_Components.clear();
}

void cEntity::Activate()
{
	for (auto compIt = m_Components.begin(); compIt != m_Components.end(); ++compIt) {
		(*compIt)->Activate();
	}
}

void cEntity::Deactivate()
{
	for (auto compIt = m_Components.begin(); compIt != m_Components.end(); ++compIt) {
		(*compIt)->Deactivate();
	}
}

void cEntity::Slot(double fTimeDiff)
{
	for (auto compIt = m_Components.begin(); compIt != m_Components.end(); ++compIt) {
		(*compIt)->Slot(fTimeDiff);
	}
}

void cEntity::SendMsg(const cMessage &message) const
{
	for (auto compIt = m_Components.begin(); compIt != m_Components.end(); ++compIt) {
		(*compIt)->ReceiveMsg(message);
	}
}

void cEntity::AddComponent(cComponent& component)
{
	m_Components.push_back(&component);
	component.SetOwner(*this);
}

void cEntity::SetActivated(bool IsActivated)
{
	m_Activated = IsActivated;
}

bool cEntity::GetActivated()
{
	return m_Activated;
}

EntityType cEntity::GetEntityType()
{
	return m_EntityType;
}
