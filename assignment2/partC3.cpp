#include "../init.h"
#include <iostream>

const char *TITLE = "Graphics Lecture - Assignment 2 Part C";
GLint winWidth = 500;
GLint winHeight = 500;

void drawScene() {
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(0.0f, 0.0f, 0.0f);
  glLineWidth(2.0f);
  glBegin(GL_LINES);
  glVertex2i(-250, 0);
  glVertex2i(250, 0);
  glVertex2i(0, -250);
  glVertex2i(0, 250);
  glEnd();

  glColor3f(0.25f, 0.25f, 0.25f);
  glRecti(50, 100, 200, 150);

  glColor3f(0.15f, 0.15f, 0.70f);
  glScalef(-0.5, 1.0f, 1.0f);
  glRecti(50, 100, 200, 150);

  glFlush();
}

void setup() { glClearColor(1.0f, 1.0f, 1.0f, 0.0f); }

void resize(int width, int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-250.0, 250.0, -250.0, 250.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClear(GL_COLOR_BUFFER_BIT);
}

void keyInput(unsigned char key, int x, int y) {}

int main(int argc, char *argv[]) {
  init(&argc, argv, TITLE, winWidth, winHeight, drawScene, resize, keyInput);
  setup();
  glutMainLoop();
  return 0;
}
