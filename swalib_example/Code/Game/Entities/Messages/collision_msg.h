#ifndef _COLLISION_MSG_H_
#define _COLLISION_MSG_H_

#include "message.h"

class cEntity;

// Collision msg.
class cCollisionMsg : public cMessage
{
};

// Entity collision msg.
class cEntCollisionMsg : public cCollisionMsg
{
private:
	cEntity	*m_pEntToColl;	// Entity to collide.
	vec2	m_vColl;	// Collision vector to entity;

public:
	cEntCollisionMsg(cEntity &ent, vec2 &vColl) : m_pEntToColl(&ent)
		, m_vColl(vColl)
	{}

	inline const cEntity *GetEntToColl() const { return m_pEntToColl; }
	inline const vec2 &GetVectColl() const { return m_vColl; }
};

// Limit collision msg.
class cLimitWorldCollMsg : public cCollisionMsg
{
public: 
	// Collision limit.
	// To use bit operators i.e. value = LIMIT_X_NEG & LIMIT_Y_NEG indicates negative limits X and Y in same value.
	enum eType : __int8
	{		
		LIMIT_X_NEG = 1,
		LIMIT_X_POS = 2,
		LIMIT_Y_NEG = 4,
		LIMIT_Y_POS = 8
	};
private:
	__int8	m_uLimit;	// Limit world.

public:
	cLimitWorldCollMsg(__int8 uLimit) : m_uLimit(uLimit)
	{}

	inline __int8 GetTypeLimitWorldColl() const { return m_uLimit; }
};

#endif // !_COLLISION_MSG_H_

