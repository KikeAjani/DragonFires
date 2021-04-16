#ifndef _GRAPHICS_ENGINE_H_
#define _GRAPHICS_ENGINE_H_

#include <map>

class cRenderObject;

// Manager of renderable objects.
class cGraphicsEngine
{
private:
	struct tImgInfo {
		GLuint	ImgId;	// Id. image
		unsigned int	iRefCount;	// Reference counter to unload image if not used.
		tImgInfo() : ImgId(0), iRefCount(0)
		{}
	};

	// Collection of pairs of name image and renderable info. For memmory purposes.
	std::map<std::string, tImgInfo> m_Images;
	// Array of renderable objects.
	std::vector<cRenderObject *>	m_RenderObjs;

public:
	static cGraphicsEngine& GetInstance();	// Singleton.
	cGraphicsEngine(cGraphicsEngine const&) = delete;
	void operator = (cGraphicsEngine const&) = delete;

	// Initialization.
	void Init();
	// Slot.
	void Slot();
	// Shutdown.
	void Terminate();

	// Insert image inside the repository of images.
	GLuint InsertImg(const char *sFileName);
	// Delete image.
	void DeleteImg(const char *sFileName);
	// Insert renderable object.
	void InsertRenderObj(cRenderObject &renderObj);
	// Delete renderable object.
	void DeleteRenderObj(cRenderObject &renderObj);

private:
	cGraphicsEngine() {};

	// Render objects.
	void RenderObjs() const;
	// Get info image. Returns 0 if error.
	cGraphicsEngine::tImgInfo *GetImgInfo(const char *sFileName);
};

#endif // !_GRAPHICS_ENGINE_H_

