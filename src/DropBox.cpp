#include <GL/freeglut.h>
#include <ode/ode.h>
#include <vector>

using namespace std;

#define WIDTH 320
#define HEIGHT 240

#define ODE_MAX_CONTACTS 1024

//ライトの位置
GLfloat lightpos[] = { 2.0, 4.0, 1.0, 0.0 };
const GLfloat FOV = 45.0f;

//ODE関連変数
bool WorldCreated = false;    //ODEワールド作成フラグ
double g_fDt = 0.005;            //タイムステップ幅

dWorldID World;                //ODEワールド
dSpaceID Space;                //ODE空間
dJointGroupID JointGroupID;//ジョイントグループ

dGeomID Ground;                //床
vector<dBodyID> ODE_obj;        //オブジェクト(立方体)

dBodyID CubeID = 0;            //立方体のID

double CubeSize = 0.1;        //立方体の大きさ
bool CrtContact = false;

//3つのベクトル
struct Vector3f {
    float x;
    float y;
    float z;
    Vector3f() {};
    Vector3f(float _x,float _y,float _z)
    {
        x=_x;
        y=_y;
        z=_z;
    };
} vec3d;
Vector3f & operator-(Vector3f &a,Vector3f &b)
{
    a.x-=b.x;
    a.y-=b.y;
    a.z-=b.z;
    return a;
}

inline Vector3f ODE_GetPos(dBodyID body)
{
    Vector3f pos;
    pos.x = (float)dBodyGetPosition(body)[0];
    pos.y = (float)dBodyGetPosition(body)[1];
    pos.z = (float)dBodyGetPosition(body)[2];
    return pos;
}
inline Vector3f ODE_GetPosG(dGeomID geom)
{
    Vector3f pos;
    pos.x = (float)dGeomGetPosition(geom)[0];
    pos.y = (float)dGeomGetPosition(geom)[1];
    pos.z = (float)dGeomGetPosition(geom)[2];
    return pos;
}


inline void ODE_GetRotMat(dBodyID body, GLfloat m[16])
{
    m[0]  = (GLfloat)dBodyGetRotation(body)[0];
    m[1]  = (GLfloat)dBodyGetRotation(body)[4];
    m[2]  = (GLfloat)dBodyGetRotation(body)[8];
    m[3]  = 0.0f;

    m[4]  = (GLfloat)dBodyGetRotation(body)[1];
    m[5]  = (GLfloat)dBodyGetRotation(body)[5];
    m[6]  = (GLfloat)dBodyGetRotation(body)[9];
    m[7]  = 0.0f;

    m[8]  = (GLfloat)dBodyGetRotation(body)[2];
    m[9]  = (GLfloat)dBodyGetRotation(body)[6];
    m[10] = (GLfloat)dBodyGetRotation(body)[10];
    m[11] = 0.0f;

    m[12] = (GLfloat)dBodyGetRotation(body)[3];
    m[13] = (GLfloat)dBodyGetRotation(body)[7];
    m[14] = (GLfloat)dBodyGetRotation(body)[11];
    m[15] = 1.0f;
}

inline double dot(const Vector3f& a, const Vector3f& b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

inline double norm(const Vector3f& a)
{
    return sqrt(dot(a,a));
}

//衝突コールバック関数用のデータ
struct NearCallData {
    dWorldID* world;
    dJointGroupID* contact;
};


//ODEの衝突処理 2つの物体の距離が近いときにODEから呼ばれるコールバック関数
static void ODENearCallback(void *data, dGeomID o1, dGeomID o2)
{
    // 衝突判定する物体のボディIDを取得
    dBodyID b1 = dGeomGetBody(o1);
    dBodyID b2 = dGeomGetBody(o2);
    if(b1 && b2 && dAreConnected(b1, b2)) {
        return;
    }

    // 接触判定
    dContact contact[ODE_MAX_CONTACTS];
    int n = dCollide(o1, o2, ODE_MAX_CONTACTS, &contact[0].geom, sizeof(dContact));

    if(n > 0) {   // 1点以上での接触があった場合
        for(int i = 0; i < n; ++i) {
            // 接触ごとにパラメータを設定
            contact[i].surface.mode = dContactBounce;
            contact[i].surface.bounce = 0.5;    // 弾力性
            contact[i].surface.bounce_vel = 0.001;

            dJointID c = dJointCreateContact(*(((NearCallData*)data)->world), *(((NearCallData*)data)->contact), contact+i);
            dJointAttach(c, dGeomGetBody(o1), dGeomGetBody(o2));
        }

    }
}

//ODEの計算ステップを進める
void StepODE(void)
{
    NearCallData data;
    data.world = &World;
    data.contact = &JointGroupID;
    dSpaceCollide(Space, &data, &ODENearCallback);
    dWorldQuickStep(World, g_fDt);
    dJointGroupEmpty(JointGroupID);

    // 立方体を回転(角速度を設定)
    if(CubeID) {
        dBodySetAngularVel(CubeID, 0.0, 10.0, 10.0);
    }
}

//ODE空間に立方体を配置
void SetODECube(Vector3f pos, double len)
{
    double d = 10*len;
    if(!ODE_obj.empty()) {
        // 最後に追加したオブジェクトとの距離
        d = norm(pos-ODE_GetPos(ODE_obj.back()));
    }

    // 追加位置に別のオブジェクトがなければ追加
    if(d > len) {
        // 立方体の重さを算出
        dMass mass;
        dMassSetBox(&mass, 1.0, (dReal)len, (dReal)len, (dReal)len);
        dMassAdjust(&mass, 1.0);

        // 形状の作成
        dGeomID geom = dCreateBox(Space, (dReal)len, (dReal)len, (dReal)len);

        // ボディの作成
        dBodyID body = dBodyCreate(World);
        dBodySetMass(body, &mass);
        dGeomSetBody(geom, body);

        // 位置を設定
        dBodySetPosition(body, pos.x, pos.y, pos.z);

        ODE_obj.push_back(body);
    }
}


void InitODE(void)
{
    dInitODE2(0);

    //ODE空間の破棄(既に存在していれば)
    if(WorldCreated) {
        dJointGroupDestroy(JointGroupID);
        dSpaceDestroy(Space);
        dWorldDestroy(World);
    }

    //ODE空間の生成
    World = dWorldCreate();
    Space = dHashSpaceCreate(0);
    JointGroupID = dJointGroupCreate(0);

    //ODE空間パラメータの設定
    dWorldSetGravity(World, 0, -9.8, 0);            //重力
    dWorldSetCFM(World, 1e-5);                    //グローバルCFM(constraint force mixing) : Typical Value [10^-9, 1.0]
    dWorldSetContactMaxCorrectingVel(World, 0.1);
    dWorldSetERP(World, 0.8);                    //グローバルERP

    dWorldSetLinearDamping(World, 0.00001);        //空気抵抗(平行移動速度)
    dWorldSetAngularDamping(World, 0.005);        //空気抵抗(角速度)
    dWorldSetMaxAngularSpeed(World, 200);        //最大角速度
    dWorldSetContactSurfaceLayer(World, 0.05);    //接触層の厚さ(この層内にいる物体は接触しているとする)
    dWorldSetAutoDisableFlag(World, 1);            //しばらく動いていないbodyを自動でdisableする

    WorldCreated = true;

    // 床
    Ground = dCreatePlane(Space, 0, 1, 0, 0);

    // 立方体
    CrtContact = false;
    SetODECube(Vector3f(0.0f, 0.8f, 0.0f), CubeSize);
}

void CleanODE(void)
{
    if(WorldCreated) {
        for(int i = 0; i < (int)ODE_obj.size(); ++i) {
            dBodyDestroy(ODE_obj[i]);
        }
        dGeomDestroy(Ground);

        dJointGroupDestroy(JointGroupID);
        dSpaceDestroy(Space);
        dWorldDestroy(World);

        dCloseODE();
    }
}

//シーンの描画
void DrawScene(void)
{
    GLfloat blue[] = { 0.4f, 0.4f, 1.0f, 1.0f };//青
    static const GLfloat spec[] = { 0.3f, 0.3f, 0.3f, 1.0f };    //鏡面反射色
    static const GLfloat ambi[] = { 0.1f, 0.1f, 0.1f, 1.0f };    //環境光

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glDisable(GL_COLOR_MATERIAL);

    // 材質を設定
    glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
    glMaterialfv(GL_FRONT, GL_AMBIENT,  ambi);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0);

    glPolygonMode(GL_FRONT, GL_FILL);
    glColor3f(0.0, 0.0, 1.0);

    // 立方体を描画
    for(int i = 0; i < (int)ODE_obj.size(); ++i) {
        dBodyID body = ODE_obj[i];
        glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);

        glPushMatrix();

        Vector3f pos;
        GLfloat m[16];

        pos = ODE_GetPos(body);
        ODE_GetRotMat(body, m);

        glTranslatef(pos.x, pos.y, pos.z);
        glMultMatrixf(m);

        // 形状の取得
        dGeomID geom = dBodyGetFirstGeom(body);

        // 形状タイプの取得
        int type = dGeomGetClass(geom);

        // 形状ごとの描画
        if(type == dBoxClass) {
            dReal sl[4];
            dGeomBoxGetLengths(geom, sl);

            glScalef((float)sl[0], (float)sl[1], (float)sl[2]);
            glutSolidCube(1.0);
        } else if(type == dSphereClass) {
            dReal rad = dGeomSphereGetRadius(geom);

            glutSolidSphere(rad, 32, 16);
        }
        glPopMatrix();
    }

    // 床を描画
    GLfloat color[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE,  color);
    glPushMatrix();
    glNormal3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 0.0, -10.0);
    glVertex3f(-10.0, 0.0,  10.0);
    glVertex3f( 10.0, 0.0,  10.0);
    glVertex3f( 10.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, WIDTH, HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOV, (float)WIDTH/(float)HEIGHT, 0.01f, 20.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();

    //視点の設定
    gluLookAt(1.0,0.5,1.0, //カメラの座標
              0.0,0.0,0.0, // 注視点の座標
              0.0,1.0,0.0); // 画面の上方向を指すベクトル

    // 光源位置
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    DrawScene();

    glPopMatrix();

    glutSwapBuffers();
}


void idle(void)
{
    StepODE();
    glutPostRedisplay();
    Sleep(1);
}

void Init(void)
{
    // 背景色
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    InitODE();
}

int main(int argc, char *argv[])
{
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("Hello ODE World!!");
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    Init();
    glutMainLoop();
    CleanODE();
    return 0;
}
