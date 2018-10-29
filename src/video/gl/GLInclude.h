#ifndef SPRITE_VIDEO_GL_GLINCLUDE_H_
#define SPRITE_VIDEO_GL_GLINCLUDE_H_

#if defined(__APPLE__) && defined(__MACH__)
	#define GL_SILENCE_DEPRECATION
	#include <OpenGL/gl3.h>
	#include <OpenGL/gl3ext.h>
#else
	#include <GL/gl.h>
#endif

#endif
