#ifndef SPRITE_SPRITE_H_
#define SPRITE_SPRITE_H_

#include "../video/PolygonRenderer.h"

#include "../platform/FileManager.h"

namespace sprite {

class Sprite;

typedef std::shared_ptr<Sprite> SpritePtr;

class Sprite
{
	static void Initialize(VideoPtr video, FileManagerPtr fileManager);
	static PolygonRendererPtr m_polygonRenderer;
	static ShaderPtr m_defaultShader;
	static math::Vector2 m_virtualScreenResolution;

	TexturePtr m_texture;

	float m_pixelDensity;

	Video::ALPHA_MODE m_alphaMode;

public:
	static void SetVirtualScreenResolution(const math::Vector2& resolution);
	static void SetVirtualScreenHeight(const math::Vector2& currentScreenResolution, const float height);

	Sprite(
		VideoPtr video,
		FileManagerPtr fileManager,
		const std::string& fileName,
		const float pixelDensity = 1.0f);

	bool IsLoaded() const;
	math::Vector2 GetSize() const;
	void Draw(const math::Vector2& pos, const math::Vector2& origin) const;
	void Draw(const math::Vector2& pos, const math::Vector2& size, const math::Vector2& origin) const;
};

} // namespace sprite

#endif
