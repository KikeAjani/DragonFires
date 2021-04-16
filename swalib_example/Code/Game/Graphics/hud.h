#ifndef _HUD_H_
#define _HUD_H_

#include "../../../../common/core.h"
#include "../Graphics/sprite.h"
#include "render_object.h"

// Background class. It's an object rendered by Graphics Render.
class cHud : public cRenderObject
{
private:
	int m_TotalLifes;
public:
	// Constructor.
	cHud();

	// To render background. Called by Graphics Render.
	void Render() override;

	void SetTotalLifes(int Lifes);
};


#endif // !_HUD_H_

