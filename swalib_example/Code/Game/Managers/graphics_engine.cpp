#include "../../../../common/stdafx.h"
#include "graphics_engine.h"
#include "../../../../common/sys.h"
#include "../../../../common/core.h"
#include "../../../../common/font.h"
#include "world.h"
#include "../Graphics/render_object.h"
#include <assert.h>

cGraphicsEngine& cGraphicsEngine::GetInstance()
{
	static cGraphicsEngine engine;
	return engine;
}

void cGraphicsEngine::Init()
{
	FONT_Init();	// Characters and symbols inicialization to draw on screen.

	// Set up rendering
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Sets up clipping
	glClearColor(0.0f, 0.1f, 0.3f, 0.0f);	// Specifies clear values for the color buffers.
	glMatrixMode(GL_PROJECTION);	// Specifies projection matrix is the current matrix.
	glLoadIdentity();	// Replaces the current matrix with the identity matrix.
	glOrtho(0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);	// Multiplies the current matrix by an orthographic matrix.
	glEnable(GL_TEXTURE_2D);	// Enabling two-dimensional texturing.
	glEnable(GL_BLEND);	// Blend the incoming RGBA color values with the values in the color buffers.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Blend func. for alpha color.

	m_Images.clear();
	m_RenderObjs.clear();
}

void cGraphicsEngine::Slot()
{
	// Render
	glClear(GL_COLOR_BUFFER_BIT);	// Clear color buffer to preset values.

	RenderObjs();

	SYS_Show();	// Exchanges the front and back buffers.
}

void cGraphicsEngine::Terminate()
{
	for (auto itImg = m_Images.begin(); itImg != m_Images.end(); ++itImg) {
		CORE_UnloadPNG(itImg->second.ImgId);
	}
	m_Images.clear();
	m_RenderObjs.clear();
	FONT_End();	// Fonts shutdown.
}

GLuint cGraphicsEngine::InsertImg(const char *sFileName)
{
	// Control if prev. inserted.
	tImgInfo *pImgInfo = GetImgInfo(sFileName);
	if (pImgInfo != nullptr) {
		pImgInfo->iRefCount++;
		return pImgInfo->ImgId;
	}

	GLuint imgId = CORE_LoadPNG(sFileName, false);
	assert(imgId != 0);
	tImgInfo newImgInfo;
	newImgInfo.ImgId = imgId;
	newImgInfo.iRefCount = 1;
	m_Images[sFileName] = newImgInfo;
	return newImgInfo.ImgId;
}

void cGraphicsEngine::DeleteImg(const char *sFileName)
{
	tImgInfo *pImgInfo = GetImgInfo(sFileName);
	if (pImgInfo == nullptr) {
		return;
	}
	pImgInfo->iRefCount--;
	// Image is deleted if it's not used.
	if (pImgInfo->iRefCount == 0) {
		CORE_UnloadPNG(pImgInfo->ImgId);
		m_Images.erase(sFileName);
	}
}

cGraphicsEngine::tImgInfo *cGraphicsEngine::GetImgInfo(const char *sFileName)
{
	// Control if prev. inserted.
	auto result = m_Images.find(sFileName);
	if (result != m_Images.end()) {
		return &result->second;
	}
	return nullptr;
}

void cGraphicsEngine::InsertRenderObj(cRenderObject &renderObj)
{
	// Control if prev. inserted.
	for (const cRenderObject *pRenderObj : m_RenderObjs) {
		if (pRenderObj == &renderObj) {
			return;
		}
	}
	m_RenderObjs.push_back(&renderObj);
}

void cGraphicsEngine::DeleteRenderObj(cRenderObject &renderObj)
{
	for (auto it = m_RenderObjs.begin(); it != m_RenderObjs.end(); ++it) {
		if (*it == &renderObj) {
			m_RenderObjs.erase(it);
			break;
		}
	}
}

void cGraphicsEngine::RenderObjs() const
{
	for (cRenderObject *pRenderObj : m_RenderObjs) {
		assert(pRenderObj != nullptr);
		pRenderObj->Render();
	}
}