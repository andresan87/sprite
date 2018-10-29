#include "../../video/Video.h"
#include "../../video/PolygonRenderer.h"

const char* vertexShaderSource =
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

const char* fragmentShaderSource =
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
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

	ShaderPtr shader = Shader::Create(video, vertexShaderSource, fragmentShaderSource);

	PolygonRendererPtr polygonRenderer = PolygonRenderer::Create(vertices, indices, PolygonRenderer::TRIANGLE_LIST);

	Video::APP_STATUS status;
	while ((status = video->HandleEvents()) != Video::AS_QUIT)
	{
		if (status == Video::AS_SKIP)
			continue;
		
		video->BeginRendering();
		{
			polygonRenderer->BeginRendering(shader);
			{
				polygonRenderer->Render();
			}
			polygonRenderer->EndRendering();
		}
		video->EndRendering();
	}
	return 0;
}
