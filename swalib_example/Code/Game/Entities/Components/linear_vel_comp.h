#ifndef _LINEAR_VEL_COMP_H_
#define _LINEAR_VEL_COMP_H_

#include "../../../../../common/core.h"
#include "../../../../../common/vector2d.h"
#include "component.h"

// Velocity component.
// Update new position using linear velocity.
class cLinearVelComp : public cComponent
{
private:
	vec2	m_vPos;	// Position. Coord. window.
	vec2	m_vVel;	// Velocity.

public:
	cLinearVelComp();

	virtual void Slot(double fTimeDiff) override;
	inline const vec2 &GetPos() const { return m_vPos; }
	inline void SetPos(const vec2& vPos) { m_vPos = vPos; }
	inline const vec2 &GetVel() const { return m_vVel; }
	inline void SetVel(const vec2& vVel) { m_vVel = vVel; }

	virtual void ReceiveMsg(const cMessage &message) override;
};

#endif // !_LINEAR_VEL_COMP_H_
