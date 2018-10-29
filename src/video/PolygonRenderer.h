#ifndef SPRITE_VIDEO_POLYGON_RENDERER_H_
#define SPRITE_VIDEO_POLYGON_RENDERER_H_

#include "Shader.h"

#include "../math/Vector3.h"

#include <vector>

namespace sprite {

class PolygonRenderer;

typedef std::shared_ptr<PolygonRenderer> PolygonRendererPtr;

class PolygonRenderer
{
public:
	enum POLYGON_MODE
	{
		TRIANGLE_LIST,
		TRIANGLE_STRIP,
		TRIANGLE_FAN
	};

	struct Vertex
	{
		Vertex(const math::Vector3& p);
		math::Vector3 pos;
	};

	static PolygonRendererPtr Create(
		const std::vector<Vertex>& vertices,
		const std::vector<unsigned int>& indices,
		const POLYGON_MODE mode);

	virtual void BeginRendering(const ShaderPtr& shader) = 0;
	virtual void Render() = 0;
	virtual void EndRendering() = 0;
};

} // namespace sprite

#endif
