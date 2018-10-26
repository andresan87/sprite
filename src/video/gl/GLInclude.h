#ifndef SPRITE_VIDEO_GL_GLINCLUDE_H_
#define SPRITE_VIDEO_GL_GLINCLUDE_H_

#if defined(__APPLE__) && defined(__MACH__)
	#define GL_SILENCE_DEPRECATION
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#endif
