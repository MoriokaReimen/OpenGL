
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
aiVector3D min_xyz{1e10f, 1e10f, 1e10f}, max_xyz{1e10f, 1e10f, 1e10f},
           center_xyz{1e10f, 1e10f, 1e10f};

/* ---------------------------------------------------------------------------- */
void get_bounding_box_for_node (const aiNode* nd,
                                aiMatrix4x4* trafo
                               )
{
    aiMatrix4x4 prev;

    prev = *trafo;
    aiMultiplyMatrix4(trafo,&nd->mTransformation);

    for (int i{0}; i < nd->mNumMeshes; ++i) {
        const aiMesh* mesh = this->scene->mMeshes[nd->mMeshes[i]];
        for (int j{0}; j < mesh->mNumVertices; ++j) {

            aiVector3D tmp = mesh->mVertices[j];
            aiTransformVecByMatrix4(&tmp,trafo);

            this->min_xyz.x = std::min(this->min_xyz.x,tmp.x);
            this->min_xyz.y = std::min(this->min_xyz.y,tmp.y);
            this->min_xyz.z = std::min(this->min_xyz.z,tmp.z);

            this->max_xyz.x = std::max(this->max_xyz.x,tmp.x);
            this->max_xyz.y = std::max(this->max_xyz.y,tmp.y);
            this->max_xyz.z = std::max(this->max_xyz.z,tmp.z);
        }
    }

    for (int i{0}; i < nd->mNumChildren; ++i) {
        get_bounding_box_for_node(nd->mChildren[i], trafo);
    }
    *trafo = prev;
}

/* ---------------------------------------------------------------------------- */
void get_bounding_box ()
{
    aiMatrix4x4 trafo;
    aiIdentityMatrix4(&trafo);

    get_bounding_box_for_node(this->scene->mRootNode, &trafo);
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
    aiMatrix4x4 m = nd->mTransformation;

    /* update transform */
    aiTransposeMatrix4(&m);
    glPushMatrix();
    glMultMatrixf((float*)&m);

    /* draw all meshes assigned to this node */
    for (int i{0}; i < nd->mNumMeshes; ++i) {
        const aiMesh* mesh = this->scene->mMeshes[nd->mMeshes[i]];

        apply_material(sc->mMaterials[mesh->mMaterialIndex]);

        if(mesh->mNormals == NULL) {
            glDisable(GL_LIGHTING);
        } else {
            glEnable(GL_LIGHTING);
        }

        for (int j{0}; j < mesh->mNumFaces; ++j) {
            const aiFace* face = &mesh->mFaces[j];
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

            for(int k{0}; k < face->mNumIndices; k++) {
                int index = face->mIndices[k];
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
    for (int i{0}; i < nd->mNumChildren; ++i) {
        recursive_render(sc, nd->mChildren[i]);
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
        get_bounding_box();
        this->center_xyz.x = (this->min_xyz.x + this->max_xyz.x) / 2.0f;
        this->center_xyz.y = (this->min_xyz.y + this->max_xyz.y) / 2.0f;
        this->center_xyz.z = (this->min_xyz.z + this->max_xyz.z) / 2.0f;
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

