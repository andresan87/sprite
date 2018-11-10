#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 2) in vec2 inTexCoord;

out vec4 outColor;
out vec2 outTexCoord;

uniform vec4 size_origin;
uniform vec4 spritePos_virtualTargetResolution;
uniform vec4 color;
uniform vec4 flipAdd_flipMul;
uniform vec4 rectPos_rectSize;
uniform vec4 angle_parallaxIntensity_zPos;

void main()
{
	vec4 vertexPos = vec4(inPos, 1.0);

	vec2 size   = vec2(size_origin.x, size_origin.y);
	vec2 origin = vec2(size_origin.z, size_origin.w);

	vec2 spritePos = vec2(spritePos_virtualTargetResolution.x, spritePos_virtualTargetResolution.y);
	vec2 virtualTargetResolution = vec2(spritePos_virtualTargetResolution.z, spritePos_virtualTargetResolution.w);

	vec2 flipAdd = vec2(flipAdd_flipMul.x, flipAdd_flipMul.y);
	vec2 flipMul = vec2(flipAdd_flipMul.z, flipAdd_flipMul.w);

	vec2 rectPos  = vec2(rectPos_rectSize.x, rectPos_rectSize.y);
	vec2 rectSize = vec2(rectPos_rectSize.z, rectPos_rectSize.w);

	float angle = angle_parallaxIntensity_zPos.x;
	float parallaxIntensity = angle_parallaxIntensity_zPos.y;
	float zPos = angle_parallaxIntensity_zPos.z;

	// apply flip
	vertexPos = vertexPos * vec4(flipMul.x, flipMul.y, 1.0, 1.0) + vec4(flipAdd.x, flipAdd.y, 0.0, 0.0);

	// scale to size and flip y-axis
	size.y *= -1.0;
	vertexPos = vertexPos * vec4(size.x, size.y, 1.0, 1.0);

	// adjust origin
	vertexPos = vertexPos - vec4(origin * size, 0.0, 0.0);

	// rotate
	vertexPos = vec4(
		vertexPos.x * cos(angle) - vertexPos.y * sin(angle),
		vertexPos.x * sin(angle) + vertexPos.y * cos(angle),
		vertexPos.z,
		vertexPos.w);

	// translate
	vertexPos = vertexPos + vec4(spritePos.x,-spritePos.y, 0.0, 0.0);

	// compute parallax offset
	vec2 halfScreenSize = virtualTargetResolution / 2.0;
	vec2 parallaxOffset = ((vertexPos.xy + vec2(-halfScreenSize.x, halfScreenSize.y)) / virtualTargetResolution.y) * parallaxIntensity * zPos;
	vertexPos = vertexPos + vec4(parallaxOffset, 0.0, 0.0);

	// adjust axis to traditional 2D
	vertexPos = vertexPos + vec4(-halfScreenSize.x, halfScreenSize.y, 0.0, 0.0);

	// scale to match fixed virtual
	vertexPos.x /= halfScreenSize.x;
	vertexPos.y /= halfScreenSize.y;

	// map sprite rect
	vec2 texCoord = inTexCoord * rectSize;
	texCoord = texCoord + rectPos;
	outTexCoord = texCoord;

	gl_Position = vertexPos;
	outColor = color;
}
