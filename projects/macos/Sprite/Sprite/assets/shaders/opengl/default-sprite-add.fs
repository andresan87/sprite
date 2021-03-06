#version 330 core
out vec4 outFragColor;

in vec4 outColor;
in vec2 outTexCoord;

uniform sampler2D diffuse;
uniform sampler2D secondary;

void main()
{
	outFragColor = (texture(diffuse, outTexCoord) * outColor) + vec4(texture(secondary, outTexCoord).xyz, 0.0);
}
