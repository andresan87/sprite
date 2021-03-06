/* This file has been generated by the ShaderToCHeader tool. Do not edit! */

#ifndef GL_SHADER_CODE_H_
#define GL_SHADER_CODE_H_

#include <string>

/* Shaders included in this file:
GL/default-sprite-add.fs                  ->     default_sprite_add_fs
GL/default-sprite-fast.vs                 ->     default_sprite_fast_vs
GL/default-sprite-modulate.fs             ->     default_sprite_modulate_fs
GL/default-sprite-solid-color-add.fs      ->     default_sprite_solid_color_add_fs
GL/default-sprite-solid-color-modulate.fs ->     default_sprite_solid_color_modulate_fs
GL/default-sprite-solid-color.fs          ->     default_sprite_solid_color_fs
GL/default-sprite.fs                      ->     default_sprite_fs
GL/default-sprite.vs                      ->     default_sprite_vs
*/

namespace gs2d_shaders {

const std::string default_sprite_add_fs = 
"#version 330 core\n" \
"out vec4 outFragColor;\n" \
"\n" \
"in vec4 outColor;\n" \
"in vec2 outTexCoord;\n" \
"\n" \
"uniform sampler2D diffuse;\n" \
"uniform sampler2D secondary;\n" \
"\n" \
"void main()\n" \
"{\n" \
"	outFragColor = (texture(diffuse, outTexCoord) * outColor) + vec4(texture(secondary, outTexCoord).xyz, 0.0);\n" \
"}\n" \
"\n" \
"\n";

const std::string default_sprite_fast_vs = 
"#version 330 core\n" \
"\n" \
"layout (location = 0) in vec3 inPosition;\n" \
"layout (location = 1) in vec2 inTexCoord;\n" \
"\n" \
"out vec4 outColor;\n" \
"out vec2 outTexCoord;\n" \
"\n" \
"uniform vec4 u[4];\n" \
"\n" \
"#define SIZE_ORIGIN 0\n" \
"#define SPRITEPOS_VIRTUALTARGETRESOLUTION 1\n" \
"#define COLOR 2\n" \
"#define RECTPOS_RECTSIZE 3\n" \
"\n" \
"void main()\n" \
"{\n" \
"	vec4 vertexPos = vec4(inPosition, 1.0);\n" \
"\n" \
"	vec2 size   = vec2(u[SIZE_ORIGIN].x, u[SIZE_ORIGIN].y);\n" \
"	vec2 origin = vec2(u[SIZE_ORIGIN].z, u[SIZE_ORIGIN].w);\n" \
"\n" \
"	vec2 spritePos = vec2(u[SPRITEPOS_VIRTUALTARGETRESOLUTION].x, u[SPRITEPOS_VIRTUALTARGETRESOLUTION].y);\n" \
"	vec2 virtualTargetResolution = vec2(u[SPRITEPOS_VIRTUALTARGETRESOLUTION].z, u[SPRITEPOS_VIRTUALTARGETRESOLUTION].w);\n" \
"\n" \
"	vec2 rectPos  = vec2(u[RECTPOS_RECTSIZE].x, u[RECTPOS_RECTSIZE].y);\n" \
"	vec2 rectSize = vec2(u[RECTPOS_RECTSIZE].z, u[RECTPOS_RECTSIZE].w);\n" \
"\n" \
"	// scale to size and flip y-axis\n" \
"	size.y *= -1.0;\n" \
"	vertexPos = vertexPos * vec4(size.x, size.y, 1.0, 1.0);\n" \
"\n" \
"	// adjust origin\n" \
"	vertexPos = vertexPos - vec4(origin * size, 0.0, 0.0);\n" \
"\n" \
"	// translate\n" \
"	vertexPos = vertexPos + vec4(spritePos.x,-spritePos.y, 0.0, 0.0);\n" \
"\n" \
"	// adjust axis to traditional 2D\n" \
"	vec2 halfScreenSize = virtualTargetResolution / 2.0;\n" \
"	vertexPos = vertexPos + vec4(-halfScreenSize.x, halfScreenSize.y, 0.0, 0.0);\n" \
"\n" \
"	// scale to match fixed virtual\n" \
"	vertexPos.x /= halfScreenSize.x;\n" \
"	vertexPos.y /= halfScreenSize.y;\n" \
"\n" \
"	// map sprite rect\n" \
"	vec2 texCoord = inTexCoord * rectSize;\n" \
"	texCoord = texCoord + rectPos;\n" \
"	outTexCoord = texCoord;\n" \
"\n" \
"	gl_Position = vertexPos;\n" \
"	outColor = u[COLOR];\n" \
"}\n" \
"\n" \
"\n";

const std::string default_sprite_modulate_fs = 
"#version 330 core\n" \
"out vec4 outFragColor;\n" \
"\n" \
"in vec4 outColor;\n" \
"in vec2 outTexCoord;\n" \
"\n" \
"uniform sampler2D diffuse;\n" \
"uniform sampler2D secondary;\n" \
"\n" \
"void main()\n" \
"{\n" \
"	outFragColor = texture(diffuse, outTexCoord) * texture(secondary, outTexCoord) * outColor;\n" \
"}\n" \
"\n" \
"\n";

const std::string default_sprite_solid_color_add_fs = 
"#version 330 core\n" \
"out vec4 outFragColor;\n" \
"\n" \
"in vec4 outColor;\n" \
"in vec2 outTexCoord;\n" \
"\n" \
"uniform sampler2D diffuse;\n" \
"uniform sampler2D secondary;\n" \
"uniform vec4 solidColor;\n" \
"\n" \
"void main()\n" \
"{\n" \
"	vec4 blendedColor = (texture(diffuse, outTexCoord) * outColor) + vec4(texture(secondary, outTexCoord).xyz, 0.0);\n" \
"	outFragColor = mix(blendedColor, vec4(solidColor.xyz, blendedColor.w), solidColor.w);\n" \
"}\n" \
"\n" \
"\n";

const std::string default_sprite_solid_color_modulate_fs = 
"#version 330 core\n" \
"out vec4 outFragColor;\n" \
"\n" \
"in vec4 outColor;\n" \
"in vec2 outTexCoord;\n" \
"\n" \
"uniform sampler2D diffuse;\n" \
"uniform sampler2D secondary;\n" \
"uniform vec4 solidColor;\n" \
"\n" \
"void main()\n" \
"{\n" \
"	vec4 blendedColor = texture(diffuse, outTexCoord) * texture(secondary, outTexCoord) * outColor;\n" \
"	outFragColor = mix(blendedColor, vec4(solidColor.xyz, blendedColor.w), solidColor.w);\n" \
"}\n" \
"\n" \
"\n";

const std::string default_sprite_solid_color_fs = 
"#version 330 core\n" \
"out vec4 outFragColor;\n" \
"\n" \
"in vec4 outColor;\n" \
"in vec2 outTexCoord;\n" \
"\n" \
"uniform sampler2D diffuse;\n" \
"uniform vec4 solidColor;\n" \
"\n" \
"void main()\n" \
"{\n" \
"	vec4 blendedColor = texture(diffuse, outTexCoord) * outColor;\n" \
"	outFragColor = mix(blendedColor, vec4(solidColor.xyz, blendedColor.w), solidColor.w);\n" \
"}\n" \
"\n" \
"\n";

const std::string default_sprite_fs = 
"#version 330 core\n" \
"out vec4 outFragColor;\n" \
"\n" \
"in vec4 outColor;\n" \
"in vec2 outTexCoord;\n" \
"\n" \
"uniform sampler2D diffuse;\n" \
"\n" \
"void main()\n" \
"{\n" \
"	outFragColor = texture(diffuse, outTexCoord) * outColor;\n" \
"}\n" \
"\n" \
"\n";

const std::string default_sprite_vs = 
"#version 330 core\n" \
"\n" \
"layout (location = 0) in vec3 inPosition;\n" \
"layout (location = 1) in vec2 inTexCoord;\n" \
"\n" \
"out vec4 outColor;\n" \
"out vec2 outTexCoord;\n" \
"\n" \
"uniform vec4 u[6];\n" \
"\n" \
"#define SIZE_ORIGIN 0\n" \
"#define SPRITEPOS_VIRTUALTARGETRESOLUTION 1\n" \
"#define COLOR 2\n" \
"#define FLIPADD_FLIPMUL 3\n" \
"#define RECTPOS_RECTSIZE 4\n" \
"#define ANGLE_PARALLAXINTENSITY_ZPOS 5\n" \
"\n" \
"void main()\n" \
"{\n" \
"	vec4 vertexPos = vec4(inPosition, 1.0);\n" \
"\n" \
"	vec2 size   = vec2(u[SIZE_ORIGIN].x, u[SIZE_ORIGIN].y);\n" \
"	vec2 origin = vec2(u[SIZE_ORIGIN].z, u[SIZE_ORIGIN].w);\n" \
"\n" \
"	vec2 spritePos = vec2(u[SPRITEPOS_VIRTUALTARGETRESOLUTION].x, u[SPRITEPOS_VIRTUALTARGETRESOLUTION].y);\n" \
"	vec2 virtualTargetResolution = vec2(u[SPRITEPOS_VIRTUALTARGETRESOLUTION].z, u[SPRITEPOS_VIRTUALTARGETRESOLUTION].w);\n" \
"\n" \
"	vec2 flipAdd = vec2(u[FLIPADD_FLIPMUL].x, u[FLIPADD_FLIPMUL].y);\n" \
"	vec2 flipMul = vec2(u[FLIPADD_FLIPMUL].z, u[FLIPADD_FLIPMUL].w);\n" \
"\n" \
"	vec2 rectPos  = vec2(u[RECTPOS_RECTSIZE].x, u[RECTPOS_RECTSIZE].y);\n" \
"	vec2 rectSize = vec2(u[RECTPOS_RECTSIZE].z, u[RECTPOS_RECTSIZE].w);\n" \
"\n" \
"	float angle = u[ANGLE_PARALLAXINTENSITY_ZPOS].x;\n" \
"	float parallaxIntensity = u[ANGLE_PARALLAXINTENSITY_ZPOS].y;\n" \
"	float zPos = u[ANGLE_PARALLAXINTENSITY_ZPOS].z;\n" \
"\n" \
"	// apply flip\n" \
"	vertexPos = vertexPos * vec4(flipMul.x, flipMul.y, 1.0, 1.0) + vec4(flipAdd.x, flipAdd.y, 0.0, 0.0);\n" \
"\n" \
"	// scale to size and flip y-axis\n" \
"	size.y *= -1.0;\n" \
"	vertexPos = vertexPos * vec4(size.x, size.y, 1.0, 1.0);\n" \
"\n" \
"	// adjust origin\n" \
"	vertexPos = vertexPos - vec4(origin * size, 0.0, 0.0);\n" \
"\n" \
"	// rotate\n" \
"	vertexPos = vec4(\n" \
"		vertexPos.x * cos(angle) - vertexPos.y * sin(angle),\n" \
"		vertexPos.x * sin(angle) + vertexPos.y * cos(angle),\n" \
"		vertexPos.z,\n" \
"		vertexPos.w);\n" \
"\n" \
"	// translate\n" \
"	vertexPos = vertexPos + vec4(spritePos.x,-spritePos.y, 0.0, 0.0);\n" \
"\n" \
"	// compute parallax offset\n" \
"	vec2 halfScreenSize = virtualTargetResolution / 2.0;\n" \
"	vec2 parallaxOffset = ((vertexPos.xy + vec2(-halfScreenSize.x, halfScreenSize.y)) / virtualTargetResolution.y) * parallaxIntensity * zPos;\n" \
"	vertexPos = vertexPos + vec4(parallaxOffset, 0.0, 0.0);\n" \
"\n" \
"	// adjust axis to traditional 2D\n" \
"	vertexPos = vertexPos + vec4(-halfScreenSize.x, halfScreenSize.y, 0.0, 0.0);\n" \
"\n" \
"	// scale to match fixed virtual\n" \
"	vertexPos.x /= halfScreenSize.x;\n" \
"	vertexPos.y /= halfScreenSize.y;\n" \
"\n" \
"	// map sprite rect\n" \
"	vec2 texCoord = inTexCoord * rectSize;\n" \
"	texCoord = texCoord + rectPos;\n" \
"	outTexCoord = texCoord;\n" \
"\n" \
"	gl_Position = vertexPos;\n" \
"	outColor = u[COLOR];\n" \
"}\n" \
"\n" \
"\n";


}

#endif
