#ifndef SPRITE_SPRITE_H_
#define SPRITE_SPRITE_H_

#include "../video/PolygonRenderer.h"

#include "../platform/FileManager.h"

#include "SpriteRects.h"

namespace sprite {

class Sprite;

typedef std::shared_ptr<Sprite> SpritePtr;

class Sprite
{
	static void Initialize(VideoPtr video, FileManagerPtr fileManager);
	static PolygonRendererPtr m_polygonRenderer;
	static ShaderPtr m_defaultShader;
	static ShaderPtr m_solidColorShader;
	static math::Vector2 m_virtualScreenResolution;
	static float m_parallaxIntensity;

	TexturePtr m_texture;

	float m_pixelDensity;

	Video::ALPHA_MODE m_alphaMode;

	math::Rect m_rect;

public:
	enum TEXTURE_BLEND_MODE
	{
		TBM_NONE,
		TBM_MODULATE,
		TBM_ADD
	};

	static void SetVirtualScreenResolution(const math::Vector2& resolution);
	static math::Vector2 GetVirtualScreenResolution();
	static void SetVirtualScreenHeight(const math::Vector2& currentScreenResolution, const float height);
	static void SetParallaxIntensity(const float intensity);
	static float GetParallaxIntensity();

	Sprite(
		VideoPtr video,
		FileManagerPtr fileManager,
		const std::string& fileName,
		const float pixelDensity = 1.0f);

	bool IsLoaded() const;
	math::Vector2 GetSize() const;
	void Draw(
		const math::Vector3& pos,
		const math::Vector2& origin,
		const float scale = 1.0f,
		const float angle = 0.0f) const;

	void Draw(
		const math::Vector3& pos,
		const math::Vector2& size,
		const math::Vector2& origin,
		const Color& color,
		const float angle,
		const bool flipX,
		const bool flipY,
		const Color* solidColor = 0,
		Texture* secondaryTexture = 0,
		const TEXTURE_BLEND_MODE textureBlendMode = TBM_NONE) const;

	void SetRect(const math::Rect& rect);
	math::Rect GetRect() const;
};

} // namespace sprite

#endif
