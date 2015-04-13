#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#include <SOIL/SOIL.h>

GLuint texture[6];//6 textures for 6 faces of the cube

GLfloat xRot,yRot,zRot;//control cube's rotation

//load the bitmap and convert it into a texture
int LoadGLTextures()
{
int Status = 0;
char *bmpFile[6] =          {"BmpFile/Ferrary.bmp","BmpFile/Honda.bmp","BmpFile/Hust.bmp",
    "BmpFile/Lamborghini.bmp","BmpFile/NeHe.bmp","BmpFile/Porsche.bmp"};
for (int i = 0;i < 6;++i)
{
    texture[i] = SOIL_load_OGL_texture(
        "toyoura.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y);
    printf("texture[%d]: %d\n",i,texture[i]);
    if(texture[i] == 0)
        Status = 0;
    glBindTexture(GL_TEXTURE_2D,texture[i]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
}

return Status;
}

int init()
{
glEnable(GL_TEXTURE_2D);
if(!LoadGLTextures())
    return 0;
glShadeModel(GL_SMOOTH);
glClearColor(0.0f,0.0f,0.0f,0.5f);
glClearDepth(1.0f);
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LEQUAL);
glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
return 1;
}

void display()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glLoadIdentity();
glTranslatef(0.0f,0.0f,-5.0f);
glRotatef(xRot,1.0f,0.0f,0.0f);
glRotatef(yRot,0.0f,1.0f,0.0f);
glRotatef(zRot,0.0f,0.0f,1.0f);

//glRotatef(45,1.0f,0.0f,0.0f);
//glRotatef(45,0.0f,1.0f,0.0f);

glBindTexture(GL_TEXTURE_2D,texture[0]);

glBegin(GL_QUADS); 
// Front Face 
// Bottom Left Of The Texture and Quad 
glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f); 
// Bottom Right Of The Texture and Quad 
glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f); 
// Top Right Of The Texture and Quad 
glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f); 
// Top Left Of The Texture and Quad 
glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f); 
glEnd(); 

glBindTexture(GL_TEXTURE_2D,texture[1]);
glBegin(GL_QUADS); 
// Back Face 
// Bottom Right Of The Texture and Quad 
glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); 
// Top Right Of The Texture and Quad 
glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f); 
// Top Left Of The Texture and Quad 
glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f); 
// Bottom Left Of The Texture and Quad 
glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f); 
glEnd(); 

glBindTexture(GL_TEXTURE_2D,texture[2]);
glBegin(GL_QUADS); 
// Top Face 
// Top Left Of The Texture and Quad 
glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f); 
// Bottom Left Of The Texture and Quad 
glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f); 
// Bottom Right Of The Texture and Quad 
glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f); 
// Top Right Of The Texture and Quad 
glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f); 
glEnd(); 

glBindTexture(GL_TEXTURE_2D,texture[3]);
glBegin(GL_QUADS); 
// Bottom Face 
// Top Right Of The Texture and Quad 
glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f); 
// Top Left Of The Texture and Quad 
glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f); 
// Bottom Left Of The Texture and Quad 
glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f); 
// Bottom Right Of The Texture and Quad 
glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f); 
glEnd(); 

glBindTexture(GL_TEXTURE_2D,texture[4]);
glBegin(GL_QUADS); 
// Right face 
// Bottom Right Of The Texture and Quad 
glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f); 
// Top Right Of The Texture and Quad 
glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f); 
// Top Left Of The Texture and Quad 
glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f); 
// Bottom Left Of The Texture and Quad 
glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f); 
glEnd(); 

glBindTexture(GL_TEXTURE_2D,texture[5]);
glBegin(GL_QUADS); 
// Left Face 
// Bottom Left Of The Texture and Quad 
glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); 
// Bottom Right Of The Texture and Quad 
glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f); 
// Top Right Of The Texture and Quad 
glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f); 
// Top Left Of The Texture and Quad 
glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f); 
glEnd(); 

/*xRot += 0.3f;
yRot += 0.4f;
zRot += 0.5f;*/

glutSwapBuffers();
}

void reshape(int w,int h)
{
if (0 == h)
    h = 1;

glViewport(0,0,(GLsizei)w,(GLsizei)h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(60.0f,(GLfloat)w / (GLfloat)h,1,100);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}

void keyboard(unsigned char key,int x,int y)
{
switch(key){
    case 'x':
        xRot += 1.0f;
        glutPostRedisplay();
        break;
    case 'y':
        yRot += 1.0f;
        glutPostRedisplay();
        break;
    case 'z':
        zRot += 1.0f;
        glutPostRedisplay();
        break;
    default:
        break;
}
}

int main(int argc,char** argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
glutInitWindowSize(400,400);
glutInitWindowPosition(100,100);
glutCreateWindow("Texture Map");
init();
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutKeyboardFunc(keyboard);
glutMainLoop();
return 0;
}
