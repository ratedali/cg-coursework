#include "../init.h"
#include <GL/gl.h>
#include <cmath>
#include <iostream>

const char *TITLE = "Graphics Lecture - Assignment 3 Part B";
GLsizei winWidth = 500;
GLsizei winHeight = 500;
GLuint regWheel;
GLfloat rotAngle = 0.0f;

void rotateWheel() {
  rotAngle += 0.01f;
  if (rotAngle > 360.0) {
    rotAngle -= 360.0;
  }
  glutPostRedisplay();
}

void drawScene() {
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();
  glRotatef(rotAngle, 0.0f, 0.0f, -1.0f);
  glCallList(regWheel);
  glPopMatrix();

  glutSwapBuffers();
  glFlush();
}

void setup() {
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

  GLint x;
  GLint y;
  GLdouble angle;
  GLint k;

  regWheel = glGenLists(1);
  GLfloat innerRadius = 25.0f;
  GLfloat outerRadius = 215.0f;
  GLfloat thickness = 30.f;
  GLint nShafts = 8;
  GLfloat width = 20.0f;
  GLfloat innerAngle = (width / 2) / innerRadius;
  GLfloat outerAngle = (width / 2) / outerRadius;

  glNewList(regWheel, GL_COMPILE);

  // Shafts
  for (int i = 0; i < nShafts; ++i) {
    if (i == 0) {
      glColor3f(0.15f, 0.15f, 0.15f);
    } else {
      glColor3f(0.40f, 0.40f, 0.40f);
    }
    GLfloat angle = M_PI_2 + 2.0f * M_PI * ((float)i / nShafts);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(innerRadius * cos(angle - innerAngle),
               innerRadius * sin(angle - innerAngle));
    glVertex2f(outerRadius * cos(angle - outerAngle),
               outerRadius * sin(angle - outerAngle));
    glVertex2f(innerRadius * cos(angle + innerAngle),
               innerRadius * sin(angle + innerAngle));
    glVertex2f(outerRadius * cos(angle + outerAngle),
               outerRadius * sin(angle + outerAngle));
    glEnd();
  }
  // Inner circle
  GLint nPoints = 40;
  glColor3f(0.0f, 0.0f, 0.0f);
  glLineWidth(4.0f);
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < nPoints; ++i) {
    GLfloat angle = M_PI_2 + 2.0f * M_PI * ((float)i / nPoints);
    glVertex2f(innerRadius * cos(angle), innerRadius * sin(angle));
  }
  glEnd();

  // Outer circle
  GLfloat innerRim = outerRadius - thickness / 2;
  GLfloat outerRim = outerRadius + thickness / 2;
  glColor3f(0.40f, 0.40f, 0.40f);
  glBegin(GL_TRIANGLE_STRIP);
  for (int i = 0; i <= nPoints; ++i) {
    GLfloat angle = 2.0f * M_PI * ((float)i / nPoints);
    glVertex2f(innerRim * cos(angle), innerRim * sin(angle));
    glVertex2f(outerRim * cos(angle), outerRim * sin(angle));
  }
  glEnd();

  glEndList();

  glutIdleFunc(rotateWheel);
}

void resize(int width, int height) {
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);

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