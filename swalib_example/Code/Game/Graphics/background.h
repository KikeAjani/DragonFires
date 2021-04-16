#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "../../../../common/core.h"
#include "../Graphics/sprite.h"
#include "render_object.h"

// Background class. It's an object rendered by Graphics Render.
class cBackground : public cRenderObject
{
private:
	cSprite	m_Sprite;	// Sprite associated.

public:
	// Constructor.
	cBackground(const char *sFileName, const vec2 &fSize);

	// To render background. Called by Graphics Render.
	void Render() override;
};


#endif // !_BACKGROUND_H_

