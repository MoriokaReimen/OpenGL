class Object
{
public:
    virtual ~Object() = default;
    virtual pGLObject getGLObject() = 0;
    virtual pBulletObject getBullet() = 0;
};

class Sphere : public Object
{
public:
    pGLSphere gl;
    pBulletSphere bullet;
    Sphere(const double radius) : gl(new GLSphere)
    {
        this->gl->setSize(quat);
        this->bullet = BulletObjectFactory(100);
        return;
    }
        return;
    }
    ~Sphere() = default;

    void setPosition(const double x, const y, const z)
    {
        this->gl->setPosition(x,y,z);
        this->bullet->setPosition(x,y,z);
        return;
    }

    void setPosition(Point point);
    {
        this->gl->setPosition(point);
        this->bullet->setPosition(point);
        return;
    }
    virtual void setAttitude(const Quaternion& quat);
    {
        this->gl->setAttitude(quat);
        this->bullet->setAttitude(quat);
        return;
    }

    pGLObject getGLObject() override
    {
         return this->gl;
    }

    pBulletObject getBullet() override
    {
        return this->bullet;
    }
};
