#pragma once
#include "component.h"
#include "../../../../../common/vector2d.h"

class cBulletMovementComp : public cComponent
{
private:
	vec2 m_vPos;
	float m_fVel;

public:
	cBulletMovementComp(vec2 InitialPosition, float Velocity);
	virtual void Slot(double fTimeDiff) override;
	inline const vec2& GetPos() const { return m_vPos; }
	inline void SetPos(const vec2& vPos) { m_vPos = vPos; }
	virtual void ReceiveMsg(const cMessage& message) override;

};

