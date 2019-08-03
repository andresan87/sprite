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
	static math::Vector2 m_virtualScreenResolution;
	static float m_parallaxIntensity;

	TexturePtr m_texture;

	float m_pixelDensity;

public:
	static ShaderPtr m_defaultShader;
	static ShaderPtr m_fastShader;
	static ShaderPtr m_solidColorShader;
	static ShaderPtr m_addShader;
	static ShaderPtr m_modulateShader;
	static ShaderPtr m_solidColorAddShader;
	static ShaderPtr m_solidColorModulateShader;

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
	math::Vector2 GetSize(const math::Rect& rect) const;
	void Draw(
		const math::Vector3& pos,
		const math::Vector2& origin,
		const float scale,
		const float angle,
		const math::Rect& rect) const;

	void Draw(
		const math::Vector3& pos,
		const math::Vector2& size,
		const math::Vector2& origin,
		const Color& color,
		const float angle,
		const math::Rect& rect,
		const bool flipX,
		const bool flipY,
		ShaderPtr shader,
		ShaderParametersPtr shaderParameters = nullptr) const;

	void Draw(
		const math::Vector2& cameraPos,
		const math::Vector3& pos,
		const math::Vector2& size,
		const math::Vector2& origin,
		const Color& color,
		const float angle,
		const math::Rect& rect,
		const bool flipX,
		const bool flipY,
		ShaderPtr shader,
		ShaderParametersPtr shaderParameters = nullptr) const;

	void BeginFastDraw() const;
	void FastDraw(
		const math::Vector3& pos,
		const math::Vector2& size,
		const math::Vector2& origin,
		const Color& color,
		const math::Rect& rect) const;
	void EndFastDraw() const;

	TexturePtr GetTexture();
};

} // namespace sprite

#endif
