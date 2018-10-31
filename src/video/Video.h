#ifndef SPRITE_PLATFORM_VIDEO_H_
#define SPRITE_PLATFORM_VIDEO_H_

#include <memory>
#include <string>

#include "../math/Vector2.h"
#include "../math/Color.h"

namespace sprite {

class Video;

typedef std::shared_ptr<Video> VideoPtr;

class Video
{
public:
	enum LOG_MESSAGE_TYPE
	{
		LMT_INFO,
		LMT_WARNING,
		LMT_ERROR
	};

	enum APP_STATUS
	{
		AS_OK,
		AS_QUIT,
		AS_SKIP
	};

	enum ALPHA_MODE
	{
		AM_PIXEL,
		AM_ADD,
		AM_MODULATE,
		AM_NONE,
		AM_UNKNOWN
	};

	static VideoPtr Create(
		const std::string& title,
		const math::Vector2& resolution,
		const bool fullscreen);

	virtual void SetAlphaMode(const ALPHA_MODE mode) = 0;
	virtual ALPHA_MODE GetAlphaMode() const = 0;

	virtual void SetResolution(const math::Vector2& resolution) = 0;
	virtual math::Vector2 GetResolution() const = 0;

	virtual void SetClearColor(const Color& color) = 0;
	virtual Color GetClearColor() const = 0;

	virtual void BeginRendering() = 0;
	virtual void EndRendering() = 0;

	virtual void Log(const std::string& message, const LOG_MESSAGE_TYPE type) = 0;
	virtual APP_STATUS HandleEvents() = 0;
};

} // namespace sprite

#endif
