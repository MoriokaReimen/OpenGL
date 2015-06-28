
#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>

/* assimp include files. These three are usually needed. */
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

/* the global Assimp scene object */

#include <string>
#include <cmath>

/* current rotation angle */
static float angle = 0.f;

class GLModel
{
const aiScene* scene = nullptr;
GLuint scene_list = 0;
aiVector3D scene_min, scene_max, scene_center;

/* ---------------------------------------------------------------------------- */
void get_bounding_box_for_node (const aiNode* nd,
                                aiVector3D* min,
                                aiVector3D* max,
                                aiMatrix4x4* trafo
                               )
{
    aiMatrix4x4 prev;
    unsigned int n = 0, t;

    prev = *trafo;
    aiMultiplyMatrix4(trafo,&nd->mTransformation);

    for (; n < nd->mNumMeshes; ++n) {
        const aiMesh* mesh = this->scene->mMeshes[nd->mMeshes[n]];
        for (t = 0; t < mesh->mNumVertices; ++t) {

            aiVector3D tmp = mesh->mVertices[t];
            aiTransformVecByMatrix4(&tmp,trafo);

            min->x = std::min(min->x,tmp.x);
            min->y = std::min(min->y,tmp.y);
            min->z = std::min(min->z,tmp.z);

            max->x = std::max(max->x,tmp.x);
            max->y = std::max(max->y,tmp.y);
            max->z = std::max(max->z,tmp.z);
        }
    }

    for (n = 0; n < nd->mNumChildren; ++n) {
        get_bounding_box_for_node(nd->mChildren[n],min,max,trafo);
    }
    *trafo = prev;
}

/* ---------------------------------------------------------------------------- */
void get_bounding_box (aiVector3D* min, aiVector3D* max)
{
    aiMatrix4x4 trafo;
    aiIdentityMatrix4(&trafo);

    min->x = min->y = min->z =  1e10f;
    max->x = max->y = max->z = -1e10f;
    get_bounding_box_for_node(this->scene->mRootNode,min,max,&trafo);
}

/* ---------------------------------------------------------------------------- */
void color4_to_float4(const aiColor4D& c, float f[4])
{
    f[0] = c.r;
    f[1] = c.g;
    f[2] = c.b;
    f[3] = c.a;
}

/* ---------------------------------------------------------------------------- */
void set_float4(float f[4], const float& a, const float& b, const float& c, const float& d)
{
    f[0] = a;
    f[1] = b;
    f[2] = c;
    f[3] = d;
}

/* ---------------------------------------------------------------------------- */
void apply_material(const aiMaterial *mtl)
{
    float c[4];

    GLenum fill_mode;
    int ret1, ret2;
    aiColor4D diffuse;
    aiColor4D specular;
    aiColor4D ambient;
    aiColor4D emission;
    float shininess, strength;
    int two_sided;
    int wireframe;
    unsigned int max;

    set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
    if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
        color4_to_float4(diffuse, c);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c);

    set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
    if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
        color4_to_float4(specular, c);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

    set_float4(c, 0.2f, 0.2f, 0.2f, 1.0f);
    if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
        color4_to_float4(ambient, c);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);

    set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
    if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
        color4_to_float4(emission, c);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, c);

    max = 1;
    ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
    if(ret1 == AI_SUCCESS) {
        max = 1;
        ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);
        if(ret2 == AI_SUCCESS)
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
        else
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    } else {
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
        set_float4(c, 0.0f, 0.0f, 0.0f, 0.0f);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);
    }

    max = 1;
    if(AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max))
        fill_mode = wireframe ? GL_LINE : GL_FILL;
    else
        fill_mode = GL_FILL;
    glPolygonMode(GL_FRONT_AND_BACK, fill_mode);

    max = 1;
    if((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
        glDisable(GL_CULL_FACE);
    else
        glEnable(GL_CULL_FACE);
}

/* ---------------------------------------------------------------------------- */
void recursive_render (const aiScene *sc, const aiNode* nd)
{
    unsigned int i;
    unsigned int n = 0, t;
    aiMatrix4x4 m = nd->mTransformation;

    /* update transform */
    aiTransposeMatrix4(&m);
    glPushMatrix();
    glMultMatrixf((float*)&m);

    /* draw all meshes assigned to this node */
    for (; n < nd->mNumMeshes; ++n) {
        const aiMesh* mesh = this->scene->mMeshes[nd->mMeshes[n]];

        apply_material(sc->mMaterials[mesh->mMaterialIndex]);

        if(mesh->mNormals == NULL) {
            glDisable(GL_LIGHTING);
        } else {
            glEnable(GL_LIGHTING);
        }

        for (t = 0; t < mesh->mNumFaces; ++t) {
            const aiFace* face = &mesh->mFaces[t];
            GLenum face_mode;

            switch(face->mNumIndices) {
            case 1:
                face_mode = GL_POINTS;
                break;
            case 2:
                face_mode = GL_LINES;
                break;
            case 3:
                face_mode = GL_TRIANGLES;
                break;
            default:
                face_mode = GL_POLYGON;
                break;
            }

            glBegin(face_mode);

            for(i = 0; i < face->mNumIndices; i++) {
                int index = face->mIndices[i];
                if(mesh->mColors[0] != NULL)
                    glColor4fv((GLfloat*)&mesh->mColors[0][index]);
                if(mesh->mNormals != NULL)
                    glNormal3fv(&mesh->mNormals[index].x);
                glVertex3fv(&mesh->mVertices[index].x);
            }

            glEnd();
        }

    }

    /* draw all children */
    for (n = 0; n < nd->mNumChildren; ++n) {
        recursive_render(sc, nd->mChildren[n]);
    }

    glPopMatrix();
}
public:
/* ---------------------------------------------------------------------------- */
GLModel(std::string path)
{
    /* we are taking one of the postprocessing presets to avoid
       spelling out 20+ single postprocessing flags here. */
    this->scene = aiImportFile(path.c_str(),aiProcessPreset_TargetRealtime_MaxQuality);

    if (this->scene) {
        get_bounding_box(&scene_min,&scene_max);
        scene_center.x = (scene_min.x + scene_max.x) / 2.0f;
        scene_center.y = (scene_min.y + scene_max.y) / 2.0f;
        scene_center.z = (scene_min.z + scene_max.z) / 2.0f;
        return;
    }
    return;
}
~GLModel()
{
    aiReleaseImport(this->scene);
    return;
}

void draw()
{
    if(scene_list == 0) {
        scene_list = glGenLists(1);
        glNewList(scene_list, GL_COMPILE);
        /* now begin at the root node of the imported data and traverse
           the scenegraph by multiplying subsequent local transforms
           together on GL's matrix stack. */
        recursive_render(this->scene, this->scene->mRootNode);
        glEndList();
    }

    glCallList(scene_list);
    return;
}
} miku("miku.obj");



/* ---------------------------------------------------------------------------- */
void reshape(int width, int height)
{
    const double aspectRatio = (float) width / height, fieldOfView = 45.0;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fieldOfView, aspectRatio,
                   1.0, 1000.0);  /* Znear and Zfar */
    glViewport(0, 0, width, height);
}


/* ---------------------------------------------------------------------------- */
void do_motion (void)
{
    static GLint prev_time = 0;
    static GLint prev_fps_time = 0;
    static int frames = 0;

    int time = glutGet(GLUT_ELAPSED_TIME);
    angle += (time-prev_time)*0.01;
    prev_time = time;

    frames += 1;
    if ((time - prev_fps_time) > 1000) { /* update every seconds */
        int current_fps = frames * 1000 / (time - prev_fps_time);
        printf("%d fps\n", current_fps);
        frames = 0;
        prev_fps_time = time;
    }


    glutPostRedisplay ();
}

/* ---------------------------------------------------------------------------- */
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.f,0.f,3.f,0.f,0.f,-5.f,0.f,1.f,0.f);

    /* rotate it around the y axis */
    glRotatef(angle,0.f,1.f,0.f);

    /* if the display list has not been made yet, create a new one and
       fill it with scene contents */

    miku.draw();

    glutSwapBuffers();

    do_motion();
}


/* ---------------------------------------------------------------------------- */
int main(int argc, char **argv)
{
    aiLogStream stream;

    glutInitWindowSize(900,600);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInit(&argc, argv);

    glutCreateWindow("Assimp - Very simple OpenGL sample");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glClearColor(0.1f,0.1f,0.1f,1.f);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);    /* Uses default lighting parameters */

    glEnable(GL_DEPTH_TEST);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);


    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

    glutGet(GLUT_ELAPSED_TIME);
    glutMainLoop();

    /* cleanup - calling 'aiReleaseImport' is important, as the library
       keeps internal resources until the scene is freed again. Not
       doing so can cause severe resource leaking. */

    return 0;
}

