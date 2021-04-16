#ifndef _COMPONENT_H_
#define _COMPONENT_H_

class cEntity;
class cMessage;

// Component of a entity.
class cComponent
{
private:
	cEntity* m_pOwner;	// Entity.

public:
	cComponent() : m_pOwner(nullptr)
	{}
	inline void SetOwner(cEntity &ent) { m_pOwner = &ent; }
	inline cEntity *GetOwner() const { return m_pOwner; }

	// Component activation when it's running first time.
	virtual void Activate()
	{}
	// Component deactivation before is deleted.
	virtual void Deactivate()
	{}
	// Process slot.
	virtual void Slot(double fTimeDiff) = 0;

	// Receive from another component.
	virtual void ReceiveMsg(const cMessage& message)
	{};
};

#endif // !_COMPONENT_H_
