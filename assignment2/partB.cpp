#include "../init.h"
#include <cmath>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>

using std::cos;
using std::sin;

const char *TITLE = "Graphics Lecture - Assignment 2 Part B";
GLint winWidth = 600;
GLint winHeight = 500;

GLint segmentedList;
GLint curves;

void circle(GLfloat cx, GLfloat cy, GLfloat radius, GLint nPoints) {
  glBegin(GL_LINE_STRIP);
  for (GLint i = 0; i <= nPoints; ++i) {
    GLfloat angle = 2.0 * M_PI * i / nPoints;
    glVertex2f(cx + radius * cos(angle), cy + radius * sin(angle));
  }
  glEnd();
}

void segmentedCircle(GLfloat cx, GLfloat cy, GLfloat radius,
                     std::vector<GLint> weights) {
  GLfloat sum = 0.0f;
  for (auto w : weights) {
    sum += w;
  }

  circle(cx, cy, radius, 100);

  GLfloat angle = 0.0f;
  for (auto w : weights) {
    angle += 2.0f * M_PI * w / sum;
    glBegin(GL_LINES);
    glVertex2f(cx, cy);
    glVertex2f(cx + radius * cos(angle), cy + radius * sin(angle));
    glEnd();
  }
}

typedef enum { limacon = 1, cardioid, threeLeaf, fourLeaf, spiral } CurveType;

void curve(CurveType type, GLfloat cx, GLfloat cy, GLfloat a, GLfloat b) {

  GLfloat px = cx, py = cy;
  switch (type) {
  case limacon:
    px += a + b;
    break;
  case cardioid:
    px += a + a;
    break;
  case threeLeaf:
  case fourLeaf:
    px += a;
    break;
  case spiral:
    break;
  }

  GLfloat r;
  GLfloat delta = 1.0 / a;
  GLfloat angle = 0.0;
  while (angle < 2.0 * M_PI) {
    switch (type) {
    case limacon:
      r = a * cos(angle) + b;
      break;
    case cardioid:
      r = a * (1 + cos(angle));
      break;
    case threeLeaf:
      r = a * cos(3 * angle);
      break;
    case fourLeaf:
      r = a * cos(2 * angle);
      break;
    case spiral:
      r = (a / 4.0) * angle;
      break;
    default:
      break;
    }
    GLfloat x = cx + r * cos(angle);
    GLfloat y = cy + r * sin(angle);
    glBegin(GL_LINES);
    glVertex2f(px, py);
    glVertex2f(x, y);
    glEnd();
    px = x;
    py = y;
    angle += delta;
  }
}

void drawScene() {
  glClear(GL_COLOR_BUFFER_BIT);
  glLineWidth(2.0f);
  glColor3f(0.25f, 0.25f, 0.25f);
  glCallList(segmentedList);
  glCallList(curves);
  glFlush();
}

void setup() {
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  glMatrixMode(GL_PROJECTION);
  glOrtho(0.0, 200.0, 0.0, 150.0, -1.0, 1.0);

  GLfloat r = winHeight * 0.15f;
  GLfloat a = r, b = r * 0.34f;
  GLfloat cx = winWidth * 0.05f;
  GLfloat cy = winHeight * 0.95 - a;
  curves = glGenLists(1);
  glNewList(curves, GL_COMPILE);
  for (int i = 1; i <= 5; ++i) {
    auto type = CurveType(i);
    curve(type, cx, cy, a, b);
    if (i % 2 == 0) {
      switch (type) {
      case limacon:
        cx += a + b;
        break;
      case cardioid:
        cx += 3 * a;
        break;
      default:
        cx += 2.0f * a;
      }
      cx += winWidth * 0.05f;
      cy = winHeight * 0.95 - a;
    } else {
      cy = winHeight * 0.05 + a;
    }
  }
  glEndList();

  std::vector<GLint> weights{10, 7, 13, 5, 13, 14, 3, 16, 5, 3, 17, 8};
  segmentedList = glGenLists(1);
  glNewList(segmentedList, GL_COMPILE);
  segmentedCircle(cx, cy, r, weights);
  glEndList();
}

void resize(int width, int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, winWidth, 0.0, winHeight, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void keyInput(unsigned char key, int x, int y) {}

int main(int argc, char *argv[]) {
  init(&argc, argv, TITLE, winWidth, winHeight, drawScene, resize, keyInput);
  setup();
  glutMainLoop();
  return 0;
}