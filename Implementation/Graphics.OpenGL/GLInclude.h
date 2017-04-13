#pragma once

#ifdef _WIN32
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Windows/gl3.h"
#elif __ANDROID__
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#endif

#include "GLUtils.h"

#ifdef _DEBUG
#define CHECK_GL_ERROR() checkGLError(__FILE__, __LINE__)
#else
#define CHECK_GL_ERROR()
#endif

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(off) (void*)(off)
#endif


