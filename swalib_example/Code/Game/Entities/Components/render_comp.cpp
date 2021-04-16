#include "../../../../../common/stdafx.h"
#include "render_comp.h"
#include "../../Managers/graphics_engine.h"
#include "../Messages/new_pos_msg.h"

cRenderComp::cRenderComp(const char *sFileName, const vec2 &vSize) : m_Sprite(sFileName, vSize)
{
}

cRenderComp::~cRenderComp()
{
	Deactivate();
}

void cRenderComp::Activate()
{
	// Registering renderable object in Graphics Engine.
	cGraphicsEngine::GetInstance().InsertRenderObj(m_Sprite);
}

void cRenderComp::Deactivate()
{
	// Derregistering renderable object in Graphics Engine.
	cGraphicsEngine::GetInstance().DeleteRenderObj(m_Sprite);
}

void cRenderComp::ReceiveMsg(const cMessage &message)
{
	// Update sprite's position.
	const cNewPosMsg *pMsg = dynamic_cast<const cNewPosMsg *>(&message);
	if (pMsg != nullptr) {
		m_Sprite.SetPos(pMsg->GetPos());
		return;
	}
}
