#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "../../../../common/core.h"
#include "../../../../common/vector2d.h"
#include "render_object.h"

// Class sprite.
class cSprite : public cRenderObject
{
private:
	vec2	m_vPos;	// Position.
	vec2	m_vSize;	// Size.
	GLuint	m_uImgId;	// OpenGL Id.
	char m_sFileName[128];	// File name.

public:
	// Constructor/Destructor.
	cSprite(const char *sFileName, const vec2 &vSize);
	~cSprite();

	// Get/Set member variables.
	inline void SetPos(const vec2 &vPos) { m_vPos = vPos; };
	inline void SetSize(const vec2 &vSize) { m_vSize = vSize; }

	// Render method.
	void Render() override;
};

#endif // !_SPRITE_H_
