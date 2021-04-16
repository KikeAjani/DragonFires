#ifndef _NEW_POS_MSG_H_
#define _NEW_POS_MSG_H_

#include "../../../../../common/vector2d.h"
#include "message.h"

// New position message.
class cNewPosMsg : public cMessage
{
private:
	vec2	m_vPos;

public:
	cNewPosMsg(const vec2 &vPos) : m_vPos(vPos)
	{}

	inline const vec2 &GetPos() const { return m_vPos; }
};

#endif // !_NEW_POS_MSG_H_
