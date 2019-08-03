#include "Sprite.h"

#include "../platform/FileIOHub.h"

#include "../math/Util.h"

namespace sprite {

PolygonRendererPtr Sprite::m_polygonRenderer;
ShaderPtr Sprite::m_defaultShader;
ShaderPtr Sprite::m_fastShader;
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

		std::vector<uint32_t> indices = { 0, 1, 2, 3 };

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

	if (!m_fastShader)
	{
		FileIOHubPtr fileIOHub = FileIOHub::Create();
		std::string vertexShader, fragmentShader;
		fileManager->GetUTF8FileString(fileIOHub->GetResourceDirectory() + "shaders/opengl/default-sprite-fast.vs", vertexShader);
		fileManager->GetUTF8FileString(fileIOHub->GetResourceDirectory() + "shaders/opengl/default-sprite.fs", fragmentShader);
		m_fastShader = Shader::Create(video, vertexShader, fragmentShader);
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
	m_pixelDensity(pixelDensity)
{
	Initialize(video, fileManager);
	m_texture = Texture::Create(video, fileManager, fileName);
}

bool Sprite::IsLoaded() const
{
	return (m_texture != TexturePtr());
}

math::Vector2 Sprite::GetSize(const math::Rect& rect) const
{
	return (IsLoaded())
		? ((m_texture->GetResolution() / m_pixelDensity) * rect.size)
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
	const float angle,
	const math::Rect& rect) const
{
	Draw(
		pos,
		GetSize(rect) * scale,
		origin,
		Color(1.0f, 1.0f, 1.0f, 1.0f),
		angle,
		rect,
		false,
		false,
		m_defaultShader,
		nullptr);
}

void Sprite::Draw(
	const math::Vector3& pos,
	const math::Vector2& size,
	const math::Vector2& origin,
	const Color& color,
	const float angle,
	const math::Rect& rect,
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

		#define SIZE_ORIGIN 0
		#define SPRITEPOS_VIRTUALTARGETRESOLUTION 1
		#define COLOR 2
		#define FLIPADD_FLIPMUL 3
		#define RECTPOS_RECTSIZE 4
		#define ANGLE_PARALLAXINTENSITY_ZPOS 5

		const unsigned int uSize = 6;
		Vector4* u = new Vector4[uSize];
		u[COLOR] = color;
		u[SIZE_ORIGIN] = Vector4(size, origin);
		u[SPRITEPOS_VIRTUALTARGETRESOLUTION] = Vector4(Vector2(pos.x, pos.y), m_virtualScreenResolution);
		u[FLIPADD_FLIPMUL] = Vector4(flipAdd, flipMul);
		u[RECTPOS_RECTSIZE] = Vector4(rect.pos, rect.size);
		u[ANGLE_PARALLAXINTENSITY_ZPOS] = Vector4(Util::DegreeToRadian(angle), m_parallaxIntensity, pos.z, 0.0f);
		shader->SetConstantArray("u", uSize, u);
		delete [] u;

		shader->SetParameter("diffuse", m_texture, 0);

		m_polygonRenderer->Render();
	}
	m_polygonRenderer->EndRendering();
}

void Sprite::BeginFastDraw() const
{
	m_polygonRenderer->BeginRendering(m_fastShader);
	m_fastShader->SetParameter("diffuse", m_texture, 0);
}

void Sprite::FastDraw(
	const math::Vector3& pos,
	const math::Vector2& size,
	const math::Vector2& origin,
	const Color& color,
	const math::Rect& rect) const
{
	using namespace math;

	#define FAST_SIZE_ORIGIN 0
	#define FAST_SPRITEPOS_VIRTUALTARGETRESOLUTION 1
	#define FAST_COLOR 2
	#define FAST_RECTPOS_RECTSIZE 3

	const unsigned int uSize = 4;
	Vector4* u = new Vector4[uSize];
	u[FAST_SIZE_ORIGIN] = Vector4(size, origin);
	u[FAST_SPRITEPOS_VIRTUALTARGETRESOLUTION] = Vector4(Vector2(pos.x, pos.y), m_virtualScreenResolution);
	u[FAST_COLOR] = color;
	u[FAST_RECTPOS_RECTSIZE] = Vector4(rect.pos, rect.size);
	m_fastShader->SetConstantArray("u", uSize, u);
	delete [] u;

	m_polygonRenderer->Render();
}

void Sprite::EndFastDraw() const
{
	m_polygonRenderer->EndRendering();
}

} // namespace sprite
