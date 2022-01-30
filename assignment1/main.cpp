#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

void drawCurve(float cx, float cy, float radius, int nSegments) {
  glBegin(GL_LINE_STRIP);
  float angle = 0.0f;
  for (int i = 0; i <= nSegments; ++i) {
    float x = radius * cos(angle);
    float y = radius * sin(angle);
    glVertex3f(cx + x, cy + y, 0.0f);
    angle += 1.5 * M_PI / nSegments;
  }
  glEnd();
}

void drawScene() {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0f, 0.0f, 0.0f);
  glLineWidth(2.0f);
  drawCurve(20.0f, 80.0f, 18.0f, 3);
  drawCurve(80.0f, 80.0f, 18.0f, 6);
  drawCurve(50.0f, 30.0f, 28.0f, 12);
  glFlush();
}

void resize(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void keyInput(unsigned char key, int x, int y) {}

void setup() { glClearColor(1.0f, 1.0f, 1.0f, 0.0f); }

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitContextVersion(3, 0);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Graphics Lecture - Assignment 1");
  glutDisplayFunc(drawScene);
  glutReshapeFunc(resize);
  glutKeyboardFunc(keyInput);
  setup();
  glutMainLoop();
  return 0;
}
