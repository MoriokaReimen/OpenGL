#include "GL.hpp"

std::list<pObject> GL::object_list;

GL::GL(int argc, char** argv, int bwidth, int bheight) : width(bwidth), height(bheight)
{
    /* Make Window */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(this->width, this->height);
    glutCreateWindow("Hello ODE World!!");
    glutDisplayFunc(GL::display);
    glutIdleFunc(GL::idle);

    /* Set Background Color and Depth Buffer */
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);

    return;
}

void GL::setLight(GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat lightpos[4];
    lightpos[0] = x;
    lightpos[1] = y;
    lightpos[2] = z;
    lightpos[3] = 1.f;

    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    return;
}

void GL::setLight(const Point& xyz)
{
    GLfloat lightpos[4];
    lightpos[0] = xyz.x;
    lightpos[1] = xyz.y;
    lightpos[2] = xyz.z;
    lightpos[3] = 1.f;

    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    return;
}

void GL::setCamera()
{
    //視点の設定
    glViewport(0, 0, this->width, this->height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.f, (float)this->width/(float)this->height, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0,20,-50, //カメラの座標
              0.0,0.0,0.0, // 注視点の座標
              0.0,1.0,0.0); // 画面の上方向を指すベクトル
    return;
}

void GL::setCamera(const Point& camera_pos, const Point& look_at)
{
    //視点の設定
    glViewport(0, 0, this->width, this->height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.f, (float)this->width/(float)this->height, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera_pos.x, camera_pos.y, camera_pos.z, //カメラの座標
              look_at.x, look_at.y, look_at.z, // 注視点の座標
              0.0,1.0,0.0); // 画面の上方向を指すベクトル
    return;
}

void GL::display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GL::DrawScene();
    glutSwapBuffers();
}

void GL::idle()
{
    glutPostRedisplay();
}

void GL::run()
{
    glutMainLoop();
}

void GL::DrawScene(void)
{
    for(auto it = GL::object_list.begin(); it != GL::object_list.end(); ++it) {
        (*it) -> draw();
    }
    return;
}

void GL::pushObject(pObject object)
{
    GL::object_list.push_back(object);
    return;
}
