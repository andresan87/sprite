#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 2) in vec2 inTexCoord;

out vec4 outColor;
out vec2 outTexCoord;

uniform vec4 size_origin;
uniform vec4 spritePos_virtualTargetResolution;
uniform vec4 color;
uniform vec4 flipAdd_flipMul;
uniform float angle;

void main()
{
	vec4 vertexPos = vec4(inPos, 1.0);

	vec2 size   = vec2(size_origin.x, size_origin.y);
	vec2 origin = vec2(size_origin.z, size_origin.w);

	vec2 spritePos = vec2(spritePos_virtualTargetResolution.x, spritePos_virtualTargetResolution.y);
	vec2 virtualTargetResolution = vec2(spritePos_virtualTargetResolution.z, spritePos_virtualTargetResolution.w);

	vec2 flipAdd = vec2(flipAdd_flipMul.x, flipAdd_flipMul.y);
	vec2 flipMul = vec2(flipAdd_flipMul.z, flipAdd_flipMul.w);

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
	vec2 halfScreenSize = virtualTargetResolution / 2.0;
	vertexPos = vertexPos + vec4(spritePos.x - halfScreenSize.x,-spritePos.y + halfScreenSize.y, 0.0, 0.0);

	// scale to match fixed virtual
	vertexPos.x /= halfScreenSize.x;
	vertexPos.y /= halfScreenSize.y;

	gl_Position = vertexPos;
	outColor = color;
	outTexCoord = inTexCoord;
}
