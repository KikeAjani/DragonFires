#include "../../../../common/stdafx.h"
#include "hud.h"
#include "../../../../common/sys.h"
#include "../../../../common/font.h"

cHud::cHud(){
	m_TotalLifes = 0; //Resetted at begging
}

void cHud::Render()
{
	char myString[128];;
	snprintf(myString, sizeof(myString), "LIFES:  %d", m_TotalLifes);

	// Text
	FONT_DrawString(vec2(15, SCR_HEIGHT-40), myString);

}

void cHud::SetTotalLifes(int Lifes)
{
	m_TotalLifes = Lifes;
}
