#include "GLPolygonRenderer.h"

#include "GLShader.h"

namespace sprite {

PolygonRendererPtr PolygonRenderer::Create(
	const std::vector<PolygonRenderer::Vertex>& vertices,
	const std::vector<uint32_t>& indices,
	const PolygonRenderer::POLYGON_MODE mode)
{
	return std::make_shared<GLPolygonRenderer>(vertices, indices, mode);
}

GLPolygonRenderer::GLPolygonRenderer(
	const std::vector<PolygonRenderer::Vertex>& vertices,
	const std::vector<uint32_t>& indices,
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * m_indices.size(), &m_indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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

GLPolygonRenderer::~GLPolygonRenderer()
{
    glDeleteVertexArrays(1, &m_vertexArrayObject);
    glDeleteBuffers(1, &m_arrayBufferObject);
    glDeleteBuffers(1, &m_arrayElementObject);
}

void GLPolygonRenderer::BeginRendering(const ShaderPtr& shader)
{
	shader->SetShader();

	glBindVertexArray(m_vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, m_arrayBufferObject);
	GLShader* glShader = static_cast<GLShader*>(shader.get());

	const GLint vPosition = glShader->GetVPositionLocation();
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(PolygonRenderer::Vertex), (void*)0);

	const GLint vTexCoord = glShader->GetVTexCoordLocation();
	glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(PolygonRenderer::Vertex), (void*)(sizeof(math::Vector3)));

	glEnableVertexAttribArray(vPosition);
	glEnableVertexAttribArray(vTexCoord);

	const GLint vNormal = glShader->GetVNormalLocation();
	if (vNormal != -1)
	{
		glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, sizeof(PolygonRenderer::Vertex), (void*)(sizeof(math::Vector3) + sizeof(math::Vector2)));
		glEnableVertexAttribArray(vNormal);
	}
}

void GLPolygonRenderer::Render()
{
	glDrawElements(m_glMode, (GLsizei)m_indices.size(), GL_UNSIGNED_INT, 0);
}

void GLPolygonRenderer::EndRendering()
{
}

} // namespace sprite
