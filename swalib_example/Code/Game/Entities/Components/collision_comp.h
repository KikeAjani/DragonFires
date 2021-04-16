#ifndef _COLLISION_COMP_H_
#define _COLLISION_COMP_H_

#include "component.h"
#include "../../../../../common/core.h"
#include "../../../../../common/vector2d.h"

class cLinearVelComp;

// Collision component.
// Control collisions between other entities and margins.
class cCollisionComp : public cComponent
{
private:
	float	m_fRadius;	// Entity radius.
	vec2	m_vPos;	// Collision position could differ from pos logic.

	cEntity* pLastBallColl;
	float fTimeSinceLastBallColl = 9999.0f;

public:
	cCollisionComp(float fRadius);
	virtual void Slot(double fTimeDiff) override;
	inline float GetRadius() const { return m_fRadius; }
	inline const vec2 &GetPos() const { return m_vPos; }
	virtual void ReceiveMsg(const cMessage &message) override;

};

#endif // _COLLISION_COMP_H_
