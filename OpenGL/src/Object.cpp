class Object
{
public:
    GLSphere* gl_;
    BulletSphere* bullet_;
    virtual ~Object() = default;
    void setPosition(Math3D::Vector3 xyz)
    {
        this->gl_->setPosition(xyz);
        this->bullet_->setPosition(xyz);
        return;
    }

    void setAttitude(Math3D::Quaternion quat);
    {
        this->gl_->setAttitude(quat);
        this->bullet_->setAttitude(quat);
        return;
    }
};

class Sphere : public Object
{
public:
    Sphere(const double radius) : gl(new GLSphere)
    {
        this->gl->setSize(quat);
        this->bullet = BulletObjectFactory(100);
        return;
    }
        return;
    }

    ~Sphere()
    {
        delete this->bullet_;
        delete this->gl_;
    }
};
