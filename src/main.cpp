// compile on Linux with
//  g++ -L/usr/X11R6/lib 3dpoints.cpp -lglut -lGLU -lGL  -lXmu -lX11 -lXi -lm

#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <list>

using namespace std;

class Point3d {
public:
     float x, y, z;

     Point3d() : x(0), y(0), z(0) {}
     Point3d(float a, float b, float c) : x(a), y(b), z(c) {}

     void dump() { printf("xyz (%f %f %f)\n", x, y, z); }
     double squared() { return x*x + y*y + z*z; }
     double length() { return sqrt(squared()); }
     void normalize() { double l = length(); x /= l; y /= l; z /= l; }
     void scalar(double f) { x *= f; y *= f; z *= f; }
};

Point3d
operator-(const Point3d& a, const Point3d& b)
{
     return Point3d(a.x-b.x, a.y-b.y, a.z-b.z);
}

Point3d
operator+(const Point3d& a, const Point3d& b)
{
     return Point3d(a.x+b.x, a.y+b.y, a.z+b.z);
}

//-------------------- globals -----------------------------------------

double nearDist, farDist; // frustum distances
double projMat[16]; // saved projection matrix
int viewport[4]; // saved viewport data
int sphereDL; // display list id of wireframe sphere
int pointDL; // display list id of point geometry
int floorDL; // display list id of floor geometry
Point3d cursor(0.0, 0.0, -20.0);
double cursorDepth = 10.0, cursorDepth0;
list<Point3d> points; // points in scene
int xorig, yorig;
bool rotateMode = false;
bool depthMode = false;
double shadowMatrix[4][4]; // shadow projection matrix

//----------------------- shadows -----------------------------------------
// ground plane given by gp[0]X + gp[1]Y + gp[2]Z + gp[4] = 0
static float groundPlane[4] = { 0.0, 1.0, 0.0, 49.0 };
static float lightPoint[4] = { 0.0, 8.0, 1.5, 0.0 };
 
/*! Compute shadow matrix from ground equation (normal) and light position. */
static void
myShadowMatrix(float ground[4], float light[4], double shadowMat[4][4])
{
  double dot;
 
  dot = ground[0] * light[0] +
    ground[1] * light[1] +
    ground[2] * light[2] +
    ground[3] * light[3];
 
  shadowMat[0][0] = dot - light[0] * ground[0];
  shadowMat[1][0] = 0.0 - light[0] * ground[1];
  shadowMat[2][0] = 0.0 - light[0] * ground[2];
  shadowMat[3][0] = 0.0 - light[0] * ground[3];
 
  shadowMat[0][1] = 0.0 - light[1] * ground[0];
  shadowMat[1][1] = dot - light[1] * ground[1];
  shadowMat[2][1] = 0.0 - light[1] * ground[2];
  shadowMat[3][1] = 0.0 - light[1] * ground[3];
 
  shadowMat[0][2] = 0.0 - light[2] * ground[0];
  shadowMat[1][2] = 0.0 - light[2] * ground[1];
  shadowMat[2][2] = dot - light[2] * ground[2]+0.0001;
  shadowMat[3][2] = 0.0 - light[2] * ground[3];
 
  shadowMat[0][3] = 0.0 - light[3] * ground[0];
  shadowMat[1][3] = 0.0 - light[3] * ground[1];
  shadowMat[2][3] = 0.0 - light[3] * ground[2];
  shadowMat[3][3] = dot - light[3] * ground[3];
}     

/*! Generate display list for checkered floor geometry */
void
makeFloor()
{
     const double sideLen = 50.0;
     const double y = -50.0;
     const int n = 10;
     int i, j;

     glPushMatrix();
     glTranslated(-sideLen * float(n)/2.0f, y, -100.0f);
     for (j = 0; j < n; ++j) {
	  for (i = 0; i < n; ++i) {
	       if ((i^j) & 1) {
		    glColor4d(0.1, 0.9, 0.1, 1.0);
	       } else {
		    glColor4d(0.1, 0.5, 0.5, 1.0);
	       }
	       glBegin(GL_QUADS);
	         glVertex3d(i*sideLen, 0.0, -j*sideLen);
		 glVertex3d(i*sideLen+sideLen, 0.0, -j*sideLen);
		 glVertex3d(i*sideLen+sideLen, 0.0, -j*sideLen+sideLen);
		 glVertex3d(i*sideLen, 0.0, -j*sideLen+sideLen);
	       glEnd();
	  }
     }
     glPopMatrix();
}

/*! Set up OpenGL stuff, init display lists etc. */
void
setupGL()
{
     glClearColor(0.0, 0.0, 1.0, 1.0);
     glEnable(GL_DEPTH_TEST);
     glPointSize(3.0);
     glShadeModel(GL_FLAT);

     sphereDL = glGenLists(1);
     glNewList(sphereDL, GL_COMPILE);
       glutWireSphere(10.0, 10, 10);
     glEndList();

     pointDL = glGenLists(1);
     glNewList(pointDL, GL_COMPILE);
       glutSolidSphere(2.0, 4, 4);
     glEndList();

     floorDL = glGenLists(1);
     glNewList(floorDL, GL_COMPILE);
       makeFloor();
     glEndList();

     myShadowMatrix(groundPlane, lightPoint, shadowMatrix);
}

/*! Draw points in list without setting the color */
void
drawPoints()
{
     list<Point3d>::iterator i;

     for (i = points.begin(); i != points.end(); ++i) {
	  glPushMatrix();
	  glTranslatef(i->x, i->y, i->z);
	  glCallList(pointDL);
	  glPopMatrix();
     }
}

/*! Draw the 3d cursor without setting color */
void
drawCursor()
{
     glPushMatrix();
     glTranslatef(cursor.x, cursor.y, cursor.z);
     glCallList(sphereDL);
     glPopMatrix();
}

/*! Convert mouse xy coord to 3d point coord */
Point3d
mouse2Coord(int x, int y)
{
     GLdouble mvmatrix[16] = {1.0, 0.0, 0.0, 0.0,
			      0.0, 1.0, 0.0, 0.0,
			      0.0, 0.0, 1.0, 0.0,
			      0.0, 0.0, 0.0, 1.0};
     GLdouble wx, wy, wz;

     glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
     y = viewport[3] - y;
     gluUnProject((GLdouble)x, (GLdouble)y, 0.0,
		  mvmatrix, projMat, viewport, &wx, &wy, &wz);
     Point3d n(wx, wy, wz);
     gluUnProject((GLdouble)x, (GLdouble)y, 1.0,
		  mvmatrix, projMat, viewport, &wx, &wy, &wz);
     Point3d f(wx, wy, wz);
     Point3d d = f - n;
     d.normalize();
     d.scalar(cursorDepth);
     return n + d;
}

//----------------- GLUT callbacks ------------------------------------

/*! GLUT display callback, draw scene */
void
display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // clear screen

    glCallList(floorDL); // draw floor

    glColor4f(1.0f, 1.0f, 0.2f, 1.0f); 
    drawPoints(); // draw the points

    glColor4f(1.0f, 0.2f, 0.2f, 1.0f); 
    drawCursor(); // draw the cursor

    // draw shadows of points and cursor
    glColor4f(0.1f, 0.1f, 0.1f, 1.0f);
    glPushMatrix();
      glMultMatrixd((GLdouble *)shadowMatrix);
      drawPoints();
      drawCursor();
    glPopMatrix();

    glutSwapBuffers(); // swap front and back buffers, we're double buffered
}

/*! GLUT keyboard callback, process keystrokes */
void
keyboard(unsigned char c, int x, int y)
{
     const double cursorSpeed = 8.0;

     switch (c) {
     case 'a': case 'A':
	  cursorDepth += cursorSpeed;
	  break;
     case 'z': case 'Z':
	  cursorDepth -= cursorSpeed;
	  break;
     case ' ':
	  points.push_back(cursor);
	  break;
     case 'h': case 'H':
	  glLoadIdentity();
	  break;
     default:
	  break;
     }
     cursor = mouse2Coord(x, y);
     glutPostRedisplay();
}

/*! GLUT resize callback, recompute viewport and frustum */
void
reshape(int w, int h)
{
     const double defFOVY = 45.0; // field-of-view in degrees in up direction
     double aspect = double(w)/double(h);
     // field-of-view
     double fov = (w < h) ? defFOVY : defFOVY/aspect;

     glViewport(0, 0, w, h);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     nearDist = 10.0;
     farDist = 1000.0;

     gluPerspective(fov, aspect, nearDist, farDist);

     glGetIntegerv(GL_VIEWPORT, &viewport[0]);
     glGetDoublev(GL_PROJECTION_MATRIX, projMat);
     glMatrixMode(GL_MODELVIEW);
}

/*! GLUT mouse motion callback */
void
motion(int x, int y)
{
     if (rotateMode) {
	  const double turnSpeed = 0.10;
	  // translate to cursor center
	  glTranslatef(cursor.x, cursor.y, cursor.z);
	  glRotated((x-xorig)*turnSpeed, 0.0, 1.0, 0.0);
	  glRotated((y-yorig)*turnSpeed, 1.0, 0.0, 0.0);
	  // translate back out to viewpoint
	  glTranslatef(-cursor.x, -cursor.y, -cursor.z);
	  xorig = x; yorig = y;
     } else if (depthMode) {
	  const double depthSpeed = 0.5;
	  cursorDepth = cursorDepth0 - depthSpeed * (y-yorig);
	  cursor = mouse2Coord(x, yorig);
     } else {
	  cursor = mouse2Coord(x, y);
     }
     glutPostRedisplay();
}

/*! GLUT mouse button callback */
void
mouse(int button, int state, int x, int y)
{
     xorig = x; yorig = y;
     rotateMode = false;
     depthMode = false;
     if (button == GLUT_LEFT_BUTTON 
	 && (glutGetModifiers() & GLUT_ACTIVE_SHIFT)) {
	  if (state == GLUT_DOWN) {
	       rotateMode = true;
	  }
     } else if (button == GLUT_MIDDLE_BUTTON) {
	  cursorDepth0 = cursorDepth;
	  depthMode = (state == GLUT_DOWN);
     }
     glutPostRedisplay();
}

//---------------- main program ---------------------------------------

int
main(int argc, char *argv[])
{
     glutInitWindowSize(400,400);
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
     glutCreateWindow("3D Points");
     glutDisplayFunc(display);
     glutKeyboardFunc(keyboard);
     glutReshapeFunc(reshape);
     glutMouseFunc(mouse);
     glutMotionFunc(motion);

     setupGL();
     
     glutMainLoop();
     return 0;
} 
