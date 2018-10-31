#include "../../video/Video.h"
#include "../../video/PolygonRenderer.h"

#include "../../platform/FileIOHub.h"
#include "../../platform/StdFileManager.h"

int main(int argc, const char * argv[])
{
	using namespace sprite;
	
	FileIOHubPtr fileIOHub = FileIOHub::Create();
	FileManagerPtr fileManager(new StdFileManager);
	
	VideoPtr video = Video::Create("Sprite", math::Vector2(800.0f, 600.0f), false);

	video->SetClearColor(Color(0xFF336699));

	std::vector<PolygonRenderer::Vertex> vertices =
	{
		PolygonRenderer::Vertex(math::Vector3( 0.5f, 0.5f, 0.0f), math::Vector3(1.0f), math::Vector2(1.0f, 1.0f)),
		PolygonRenderer::Vertex(math::Vector3( 0.5f,-0.5f, 0.0f), math::Vector3(1.0f), math::Vector2(1.0f, 0.0f)),
		PolygonRenderer::Vertex(math::Vector3(-0.5f,-0.5f, 0.0f), math::Vector3(1.0f), math::Vector2(0.0f, 0.0f)),
		PolygonRenderer::Vertex(math::Vector3(-0.5f, 0.5f, 0.0f), math::Vector3(1.0f), math::Vector2(0.0f, 1.0f))
	};
	std::vector<unsigned int> indices =
	{
		0, 1, 3,
		1, 2, 3
	};
	PolygonRendererPtr polygonRendererA = PolygonRenderer::Create(vertices, indices, PolygonRenderer::TRIANGLE_LIST);

	vertices =
	{
		PolygonRenderer::Vertex(math::Vector3(-1.0f, 1.0f, 0.0f), math::Vector3(1.0f), math::Vector2(1.0f)),
		PolygonRenderer::Vertex(math::Vector3(-0.9f, 0.0f, 0.0f), math::Vector3(1.0f), math::Vector2(1.0f)),
		PolygonRenderer::Vertex(math::Vector3( 0.3f, 0.9f, 0.0f), math::Vector3(1.0f), math::Vector2(1.0f)),
		PolygonRenderer::Vertex(math::Vector3( 0.0f, 0.0f, 0.0f), math::Vector3(1.0f), math::Vector2(1.0f))
	};
	indices =
	{
		0, 1, 2, 3
	};
	PolygonRendererPtr polygonRendererB = PolygonRenderer::Create(vertices, indices, PolygonRenderer::TRIANGLE_STRIP);

	std::string vertexShader, fragmentShader;
	fileManager->GetUTF8FileString(fileIOHub->GetResourceDirectory() + "sprite.vs", vertexShader);
	fileManager->GetUTF8FileString(fileIOHub->GetResourceDirectory() + "sprite.fs", fragmentShader);
	ShaderPtr shader = Shader::Create(video, vertexShader, fragmentShader);

	TexturePtr texture = Texture::Create(video, fileManager, fileIOHub->GetResourceDirectory() + "asantee-logo.png");

	Video::APP_STATUS status;
	while ((status = video->HandleEvents()) != Video::AS_QUIT)
	{
		if (status == Video::AS_SKIP)
			continue;
		
		video->BeginRendering();
		{
			polygonRendererA->BeginRendering(shader);
			shader->SetParameter("spriteColor", math::Vector3(1.0f, 0.0f, 0.0f));
			polygonRendererA->Render();
			polygonRendererA->EndRendering();

			polygonRendererB->BeginRendering(shader);
			shader->SetParameter("spriteColor", math::Vector3(0.0f, 0.0f, 1.0f));
			polygonRendererB->Render();
			polygonRendererB->EndRendering();
		}
		video->EndRendering();
	}
	return 0;
}
