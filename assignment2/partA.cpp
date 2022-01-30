#include "../init.h"
#include <cmath>
#include <iostream>

const char *TITLE = "Graphics Lecture - Assignment 2 Part A";
GLint winWidth = 400;
GLint winHeight = 300;
GLint hexagon;

void drawScene() {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.25f, 0.25f, 0.25f);
  glCallList(hexagon);
  glFlush();
}

void setup() {
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  hexagon = glGenLists(1);

  glNewList(hexagon, GL_COMPILE);
  GLfloat cx = winWidth / 2.0f;
  GLfloat cy = winHeight / 2.0f;
  GLfloat r = 150.0f;
  glBegin(GL_POLYGON);
  for (int i = 0; i < 6; ++i) {
    GLfloat angle = 2.0 * M_PI * i / 6.0;
    glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
  }
  glEnd();
  glEndList();
}

void resize(int width, int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, winWidth, 0.0, winHeight, -1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
}

void keyInput(unsigned char key, int x, int y) {}

int main(int argc, char *argv[]) {
  init(&argc, argv, TITLE, winWidth, winHeight, drawScene, resize, keyInput);
  setup();
  glutMainLoop();
  return 0;
}