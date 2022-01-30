#include "init.h"

void init(int *argc, char *argv[], const char *title, GLint width, GLint height,
          void (*drawScene)(), void (*resize)(int, int),
          void (*keyInput)(unsigned char, int, int)) {
  glutInit(argc, argv);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(width, height);
  glutCreateWindow(title);

  glutDisplayFunc(drawScene);
  glutKeyboardFunc(keyInput);
  glutReshapeFunc(resize);
}
