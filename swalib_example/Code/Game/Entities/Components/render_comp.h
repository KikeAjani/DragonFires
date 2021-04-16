#ifndef _RENDER_COMP_H_
#define _RENDER_COMP_H_

#include "../../Graphics/sprite.h"
#include "component.h"

// Renderable component.
class cRenderComp : public cComponent
{
private:
	cSprite	m_Sprite;	// Sprite associated.

public:
	cRenderComp(const char *sFileName, const vec2 &vSize);
	~cRenderComp();

	// Component activation when it's running first time.
	virtual void Activate() override;
	// Component deactivation before is deleted.
	virtual void Deactivate() override;

	virtual void Slot(double fTimeDiff) override
	{};

	virtual void ReceiveMsg(const cMessage &message) override;
};

#endif // !_RENDER_COMP_H_
