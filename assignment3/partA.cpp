#include "../init.h"
#include <GL/gl.h>
#include <cmath>
#include <iostream>

const char *TITLE = "Graphics Lecture - Assignment 3 Part A";
GLsizei winWidth = 500;
GLsizei winHeight = 500;
GLuint regRect;
GLfloat transAngle = -180.0f;

void translateRect() {
  transAngle += 0.05f;
  if (transAngle > 360.0) {
    transAngle -= 360.0;
  }
  glutPostRedisplay();
}

void drawScene() {
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();
  GLfloat x = 200 + 200 * std::cos(transAngle * M_PI / 180.0f);
  glTranslatef(x, 0, 0);
  glCallList(regRect);
  glPopMatrix();

  glutSwapBuffers();
  glFlush();
}

void setup() {
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  GLint x;
  GLint y;
  GLdouble angle;
  GLint k;

  regRect = glGenLists(1);
  glNewList(regRect, GL_COMPILE);
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_POLYGON);
  glVertex2i(0, 300);
  glVertex2i(0, 200);
  glVertex2i(100, 200);
  glVertex2i(100, 300);
  glEnd();
  glEndList();

  glutIdleFunc(translateRect);
}

void resize(int width, int height) {
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 500.0, 0.0, 500.0, -1.0, 1.0);

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
