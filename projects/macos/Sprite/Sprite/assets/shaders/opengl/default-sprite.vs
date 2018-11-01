#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 2) in vec2 inTexCoord;

out vec4 outColor;
out vec2 outTexCoord;

uniform vec4 size_origin;
uniform vec4 spritePos_virtualTargetResolution;

void main()
{
	vec4 vertexPos = vec4(inPos, 1.0);

	vec2 size   = vec2(size_origin.x, size_origin.y);
	vec2 origin = vec2(size_origin.z, size_origin.w);

	vec2 spritePos = vec2(spritePos_virtualTargetResolution.x, spritePos_virtualTargetResolution.y);
	vec2 virtualTargetResolution = vec2(spritePos_virtualTargetResolution.z, spritePos_virtualTargetResolution.w);

	// scale to size and flip y-axis
	size.y *= -1.0;
	vertexPos = vertexPos * vec4(size.x, size.y, 1.0, 1.0);

	// adjust origin
	vertexPos = vertexPos - vec4(origin * size, 0.0, 0.0);

	// scale to match fixed virtual
	vertexPos.x /= (virtualTargetResolution.x * 0.5);
	vertexPos.y /= (virtualTargetResolution.y * 0.5);

	gl_Position = vertexPos;
	outColor = vec4(1.0, 1.0, 1.0, 1.0);
	outTexCoord = inTexCoord;
}
