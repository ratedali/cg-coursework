#ifndef __GRAPHICS_LECTURE_INIT
#define __GRAPHICS_LECTURE_INIT

#include <GL/freeglut.h>

void init(int *argc, char *argv[], const char *title, GLint width, GLint height,
          void (*drawScene)(), void (*resize)(int, int),
          void (*keyInput)(unsigned char, int, int));

#endif
