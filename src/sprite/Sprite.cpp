#include "Sprite.h"

#include "../platform/FileIOHub.h"

namespace sprite {

PolygonRendererPtr Sprite::m_polygonRenderer;
ShaderPtr Sprite::m_defaultShader;
math::Vector2 Sprite::m_virtualScreenResolution = math::Vector2(1280.0f, 720.0f);

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
}

void Sprite::SetVirtualScreenResolution(const math::Vector2& resolution)
{
	m_virtualScreenResolution = resolution;
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
	return (IsLoaded()) ? (m_texture->GetResolution() / m_pixelDensity) : (math::Vector2(0.0f));
}

void Sprite::Draw(const math::Vector2& pos, const math::Vector2& origin) const
{
	Draw(pos, GetSize(), origin);
}

void Sprite::Draw(const math::Vector2& pos, const math::Vector2& size, const math::Vector2& origin) const
{
	const ShaderPtr& shader = m_defaultShader;
	m_polygonRenderer->BeginRendering(shader);
		shader->SetParameter("size_origin", math::Vector4(size.x, size.y, origin.x, origin.y));
		shader->SetParameter("spritePos_virtualTargetResolution",
			math::Vector4(pos.x, pos.y, m_virtualScreenResolution.x, m_virtualScreenResolution.y));
		shader->SetParameter("diffuse", m_texture);
		m_polygonRenderer->Render();
	m_polygonRenderer->EndRendering();
}

} // namespace sprite
