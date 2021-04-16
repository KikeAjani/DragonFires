#pragma once
#include "component.h"
#include "../../../../../common/vector2d.h"
#include ".././../../../../common/sys.h"

class cInputMovComp :  public cComponent
{

private:
	vec2 m_vPos;
	vec2 m_vSize;
public:
	cInputMovComp();
	virtual void Slot(double fTimeDiff) override;
	inline const vec2& GetPos() const { return m_vPos; }
	inline void SetPos(const vec2& vPos) { m_vPos = vPos; }

	virtual void ReceiveMsg(const cMessage& message) override;

	bool KeyPressed(int key);

	void SetSize(vec2 Size);
	inline const vec2& GetSize() const { return m_vSize; }

};

