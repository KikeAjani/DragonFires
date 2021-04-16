#include "../../../../common/stdafx.h"
#include "background.h"
#include "../../../../common/sys.h"
#include "../../../../common/font.h"

cBackground::cBackground(const char *sFileName, const vec2 &fSize) : m_Sprite(sFileName, fSize)
{
}

void cBackground::Render()
{
	// Render backgground
	for (int i = 0; i <= SCR_WIDTH / 128; i++) {
		for (int j = 0; j <= SCR_HEIGHT / 128; j++) {
			m_Sprite.SetPos(vec2(i * 128.f + 64.f, j * 128.f + 64.f));
			m_Sprite.Render();
		}
	}
}