#include <GL/freeglut.h>
#include <GL/glu.h>

void drawScene() {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINES);
  glVertex3f(20.0, 80.0, 0.0);
  glVertex3f(80.0, 20.0, 0.0);
  glEnd();
  glFlush();
}

void resize(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 100.0, 0.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void keyInput(unsigned char key, int x, int y) {}

void setup() { glClearColor(1.0, 1.0, 1.0, 0.0); }

int main(int argc, char *argv[]) {

  glutInit(&argc, argv);
  glutInitContextVersion(3, 0);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Graphics Lecture");
  glutDisplayFunc(drawScene);
  glutReshapeFunc(resize);
  glutKeyboardFunc(keyInput);
  setup();
  glutMainLoop();
  return 0;
}
