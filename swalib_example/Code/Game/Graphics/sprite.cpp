#include "../../../../common/stdafx.h"
#include "sprite.h"
#include "../Managers/graphics_engine.h"
#include <string.h>
#include <assert.h>

cSprite::cSprite(const char *sFileName, const vec2 &vSize) : m_vPos({ 0,0 })
	, m_vSize(vSize)
{
	errno_t err = strcpy_s(m_sFileName, _countof(m_sFileName), sFileName);
	assert(err == 0);
	m_uImgId = cGraphicsEngine::GetInstance().InsertImg(sFileName);	// Get id from repository to render.
}

cSprite::~cSprite()
{
	cGraphicsEngine::GetInstance().DeleteImg(m_sFileName);	// Delete image.
}

void cSprite::Render()
{
	// Render Sprite.
	CORE_RenderCenteredSprite(m_vPos, m_vSize, m_uImgId);
}
