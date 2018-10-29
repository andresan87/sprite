#include "GLPolygonRenderer.h"

#include "GLShader.h"

namespace sprite {

PolygonRendererPtr PolygonRenderer::Create(
	const std::vector<PolygonRenderer::Vertex>& vertices,
	const std::vector<unsigned int>& indices,
	const PolygonRenderer::POLYGON_MODE mode)
{
	std::shared_ptr<GLPolygonRenderer> r = std::make_shared<GLPolygonRenderer>(vertices, indices, mode);
	return (r);
}

GLPolygonRenderer::GLPolygonRenderer(
	const std::vector<PolygonRenderer::Vertex>& vertices,
	const std::vector<unsigned int>& indices,
	const PolygonRenderer::POLYGON_MODE mode) :
	m_mode(mode),
	m_indices(indices),
	m_vertices(vertices)
{
	glGenVertexArrays(1, &m_vertexArrayObject);
	glGenBuffers(1, &m_arrayBufferObject);
	glGenBuffers(1, &m_arrayElementObject);

	glBindVertexArray(m_vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, m_arrayBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(PolygonRenderer::Vertex) * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_arrayElementObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_indices.size(), &m_indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PolygonRenderer::Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	switch (mode)
	{
		case PolygonRenderer::TRIANGLE_STRIP:
			m_glMode = GL_TRIANGLE_STRIP;
		break;

		case PolygonRenderer::TRIANGLE_FAN:
			m_glMode = GL_TRIANGLE_FAN;
		break;

		case PolygonRenderer::TRIANGLE_LIST:
		default:
			m_glMode = GL_TRIANGLES;
		break;
	}
}

void GLPolygonRenderer::BeginRendering(const ShaderPtr& shader)
{
	glBindVertexArray(m_vertexArrayObject);
	
	GLShader* glShader = (GLShader*)shader.get();
	glUseProgram(glShader->GetShaderProgram());
}

void GLPolygonRenderer::Render()
{
	glDrawElements(m_glMode, (GLsizei)m_indices.size(), GL_UNSIGNED_INT, 0);
}

void GLPolygonRenderer::EndRendering()
{
}

} // namespace sprite
