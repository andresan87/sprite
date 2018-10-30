#include "../../video/Video.h"
#include "../../video/PolygonRenderer.h"

const char* vertexShaderSource =
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"out vec4 vertexColor;\n"
	"uniform vec3 spriteColor;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"	vertexColor = vec4(aPos.x, aPos.y, 1.0 - aPos.x, 1.0) * vec4(spriteColor, 1.0);"
	"}\0";

const char* fragmentShaderSource =
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"in vec4 vertexColor;\n"
	"void main()\n"
	"{\n"
	"   FragColor = vertexColor;\n"
	"}\n\0";

int main(int argc, const char * argv[])
{
	using namespace sprite;
	
	VideoPtr video = Video::Create("Sprite", math::Vector2(800.0f, 600.0f), false);

	video->SetClearColor(Color(0xFF336699));

	std::vector<PolygonRenderer::Vertex> vertices =
	{
		PolygonRenderer::Vertex(math::Vector3( 0.5f, 0.5f, 0.0f)),
		PolygonRenderer::Vertex(math::Vector3( 0.5f,-0.5f, 0.0f)),
		PolygonRenderer::Vertex(math::Vector3(-0.5f,-0.5f, 0.0f)),
		PolygonRenderer::Vertex(math::Vector3(-0.5f, 0.5f, 0.0f))
	};
	std::vector<unsigned int> indices =
	{
		0, 1, 3,
		1, 2, 3
	};
	PolygonRendererPtr polygonRendererA = PolygonRenderer::Create(vertices, indices, PolygonRenderer::TRIANGLE_LIST);

	vertices =
	{
		PolygonRenderer::Vertex(math::Vector3(-1.0f, 1.0f, 0.0f)),
		PolygonRenderer::Vertex(math::Vector3(-0.9f, 0.0f, 0.0f)),
		PolygonRenderer::Vertex(math::Vector3( 0.3f, 0.9f, 0.0f)),
		PolygonRenderer::Vertex(math::Vector3( 0.0f, 0.0f, 0.0f))
	};
	indices =
	{
		0, 1, 2, 3
	};
	PolygonRendererPtr polygonRendererB = PolygonRenderer::Create(vertices, indices, PolygonRenderer::TRIANGLE_STRIP);

	ShaderPtr shader = Shader::Create(video, vertexShaderSource, fragmentShaderSource);

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
