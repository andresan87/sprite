#include "Sprite.h"

#include "../platform/FileIOHub.h"

#include "../math/Util.h"

namespace sprite {

PolygonRendererPtr Sprite::m_polygonRenderer;
ShaderPtr Sprite::m_defaultShader;
ShaderPtr Sprite::m_solidColorShader;
ShaderPtr Sprite::m_addShader;
ShaderPtr Sprite::m_modulateShader;
ShaderPtr Sprite::m_solidColorAddShader;
ShaderPtr Sprite::m_solidColorModulateShader;
math::Vector2 Sprite::m_virtualScreenResolution(1280.0f, 720.0f);
float Sprite::m_parallaxIntensity = 0.0f;

void Sprite::Initialize(VideoPtr video, FileManagerPtr fileManager)
{
	if (!m_polygonRenderer)
	{
		std::vector<PolygonRenderer::Vertex> vertices =
		{
			PolygonRenderer::Vertex(math::Vector3( 0.0f, 0.0f, 0.0f), math::Vector3(1.0f), math::Vector2(0.0f, 0.0f)),
			PolygonRenderer::Vertex(math::Vector3( 0.0f, 1.0f, 0.0f), math::Vector3(1.0f), math::Vector2(0.0f, 1.0f)),
			PolygonRenderer::Vertex(math::Vector3( 1.0f, 0.0f, 0.0f), math::Vector3(1.0f), math::Vector2(1.0f, 0.0f)),
			PolygonRenderer::Vertex(math::Vector3( 1.0f, 1.0f, 0.0f), math::Vector3(1.0f), math::Vector2(1.0f, 1.0f))
		};

		std::vector<unsigned int> indices = { 0, 1, 2, 3 };

		m_polygonRenderer = PolygonRenderer::Create(vertices, indices, PolygonRenderer::TRIANGLE_STRIP);
	}

	if (!m_defaultShader)
	{
		FileIOHubPtr fileIOHub = FileIOHub::Create();
		std::string vertexShader, fragmentShader;
		fileManager->GetUTF8FileString(fileIOHub->GetResourceDirectory() + "shaders/opengl/default-sprite.vs", vertexShader);
		fileManager->GetUTF8FileString(fileIOHub->GetResourceDirectory() + "shaders/opengl/default-sprite.fs", fragmentShader);
		m_defaultShader = Shader::Create(video, vertexShader, fragmentShader);
	}

	if (!m_solidColorShader)
	{
		FileIOHubPtr fileIOHub = FileIOHub::Create();
		std::string vertexShader, fragmentShader;
		fileManager->GetUTF8FileString(fileIOHub->GetResourceDirectory() + "shaders/opengl/default-sprite.vs", vertexShader);
		fileManager->GetUTF8FileString(fileIOHub->GetResourceDirectory() + "shaders/opengl/default-sprite-solid-color.fs", fragmentShader);
		m_solidColorShader = Shader::Create(video, vertexShader, fragmentShader);
	}

	if (!m_addShader)
	{
		FileIOHubPtr fileIOHub = FileIOHub::Create();
		std::string vertexShader, fragmentShader;
		fileManager->GetUTF8FileString(fileIOHub->GetResourceDirectory() + "shaders/opengl/default-sprite.vs", vertexShader);
		fileManager->GetUTF8FileString(fileIOHub->GetResourceDirectory() + "shaders/opengl/default-sprite-add.fs", fragmentShader);
		m_addShader = Shader::Create(video, vertexShader, fragmentShader);
	}

	if (!m_modulateShader)
	{
		FileIOHubPtr fileIOHub = FileIOHub::Create();
		std::string vertexShader, fragmentShader;
		fileManager->GetUTF8FileString(fileIOHub->GetResourceDirectory() + "shaders/opengl/default-sprite.vs", vertexShader);
		fileManager->GetUTF8FileString(fileIOHub->GetResourceDirectory() + "shaders/opengl/default-sprite-modulate.fs", fragmentShader);
		m_modulateShader = Shader::Create(video, vertexShader, fragmentShader);
	}

	if (!m_solidColorAddShader)
	{
		FileIOHubPtr fileIOHub = FileIOHub::Create();
		std::string vertexShader, fragmentShader;
		fileManager->GetUTF8FileString(fileIOHub->GetResourceDirectory() + "shaders/opengl/default-sprite.vs", vertexShader);
		fileManager->GetUTF8FileString(fileIOHub->GetResourceDirectory() + "shaders/opengl/default-sprite-solid-color-add.fs", fragmentShader);
		m_solidColorAddShader = Shader::Create(video, vertexShader, fragmentShader);
	}

	if (!m_solidColorModulateShader)
	{
		FileIOHubPtr fileIOHub = FileIOHub::Create();
		std::string vertexShader, fragmentShader;
		fileManager->GetUTF8FileString(fileIOHub->GetResourceDirectory() + "shaders/opengl/default-sprite.vs", vertexShader);
		fileManager->GetUTF8FileString(fileIOHub->GetResourceDirectory() + "shaders/opengl/default-sprite-solid-color-modulate.fs", fragmentShader);
		m_solidColorModulateShader = Shader::Create(video, vertexShader, fragmentShader);
	}
}

void Sprite::SetParallaxIntensity(const float intensity)
{
	m_parallaxIntensity = intensity;
}

float Sprite::GetParallaxIntensity()
{
	return m_parallaxIntensity;
}

void Sprite::SetVirtualScreenResolution(const math::Vector2& resolution)
{
	m_virtualScreenResolution = resolution;
}

math::Vector2 Sprite::GetVirtualScreenResolution()
{
	return m_virtualScreenResolution;
}

void Sprite::SetVirtualScreenHeight(const math::Vector2& currentScreenResolution, const float height)
{
	m_virtualScreenResolution.x = currentScreenResolution.x * (height / currentScreenResolution.y);
	m_virtualScreenResolution.y = height;
}

Sprite::Sprite(
	VideoPtr video,
	FileManagerPtr fileManager,
	const std::string& fileName,
	const float pixelDensity) :
	m_pixelDensity(pixelDensity),
	m_alphaMode(Video::AM_PIXEL)
{
	Initialize(video, fileManager);
	m_texture = Texture::Create(video, fileManager, fileName);
}

bool Sprite::IsLoaded() const
{
	return (m_texture != TexturePtr());
}

math::Vector2 Sprite::GetSize() const
{
	return (IsLoaded())
		? ((m_texture->GetResolution() / m_pixelDensity) * m_rect.size)
		: (math::Vector2(0.0f));
}

TexturePtr Sprite::GetTexture()
{
	return m_texture;
}

void Sprite::Draw(
	const math::Vector3& pos,
	const math::Vector2& origin,
	const float scale,
	const float angle) const
{
	Draw(pos, GetSize() * scale, origin, Color(1.0f, 1.0f, 1.0f, 1.0f), angle, false, false);
}

void Sprite::Draw(
	const math::Vector3& pos,
	const math::Vector2& size,
	const math::Vector2& origin,
	const Color& color,
	const float angle,
	const bool flipX,
	const bool flipY,
	ShaderPtr shader,
	ShaderParametersPtr shaderParameters) const
{
	using namespace math;

	Vector2 flipMul = Vector2(1.0f);
	Vector2 flipAdd = Vector2(0.0f);
	if (flipX)
	{
		flipMul.x =-1.0f;
		flipAdd.x = 1.0f;
	}
	if (flipY)
	{
		flipMul.y =-1.0f;
		flipAdd.y = 1.0f;
	}

	if (!shader)
	{
		shader = m_defaultShader;
	}

	m_polygonRenderer->BeginRendering(shader);
	{
		if (shaderParameters)
		{
			for (ShaderParameters::iterator it = shaderParameters->begin(); it != shaderParameters->end(); ++it)
			{
				it.value()->SetParameter(it.key(), shader);
			}
		}
		shader->SetParameter("color", color);
		shader->SetParameter("size_origin", Vector4(size, origin));
		shader->SetParameter("spritePos_virtualTargetResolution", Vector4(Vector2(pos.x, pos.y), m_virtualScreenResolution));
		shader->SetParameter("diffuse", m_texture);
		shader->SetParameter("flipAdd_flipMul", Vector4(flipAdd, flipMul));
		shader->SetParameter("rectPos_rectSize", Vector4(m_rect.pos, m_rect.size));
		shader->SetParameter("angle_parallaxIntensity_zPos", Vector4(Util::DegreeToRadian(angle), m_parallaxIntensity, pos.z, 0.0f));
		m_polygonRenderer->Render();
	}
	m_polygonRenderer->EndRendering();
}

void Sprite::Draw(
	const math::Vector3& pos,
	const math::Vector2& size,
	const math::Vector2& origin,
	const Color& color,
	const float angle,
	const bool flipX,
	const bool flipY,
	const Color* solidColor,
	const TexturePtr& secondaryTexture,
	const TEXTURE_BLEND_MODE textureBlendMode) const
{
	ShaderPtr shader = m_defaultShader;
	ShaderParametersPtr parameters(new ShaderParameters);

	if (solidColor != 0 && solidColor->w > 0.0f)
	{
		if (textureBlendMode == TBM_NONE)
		{
			shader = m_solidColorShader;
		}
		else if (textureBlendMode == TBM_ADD)
		{
			shader = m_solidColorAddShader;
		}
		else if (textureBlendMode == TBM_MODULATE)
		{
			shader = m_solidColorModulateShader;
		}
		(*parameters)["solidColor"] = std::make_shared<Shader::Vector4ShaderParameter>(*solidColor);
	}
	else if (textureBlendMode != TBM_NONE)
	{
		if (textureBlendMode == TBM_ADD)
		{
			shader = m_addShader;
		}
		else if (textureBlendMode == TBM_MODULATE)
		{
			shader = m_modulateShader;
		}
	}

	if (secondaryTexture)
	{
		(*parameters)["secondary"] = std::make_shared<Shader::TextureShaderParameter>(secondaryTexture);
	}
	
	Draw(pos, size, origin, color, angle, flipX, flipY, shader, parameters);
}

void Sprite::SetRect(const math::Rect& rect)
{
	m_rect = rect;
}

math::Rect Sprite::GetRect() const
{
	return m_rect;
}

} // namespace sprite
