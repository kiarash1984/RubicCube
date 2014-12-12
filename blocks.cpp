#include "blocks.h"

Blocks::Blocks(QVector3D position)
{
    Position = position;
    lastRotation = QVector3D(0,0,0);
    mMatrix.setToIdentity();
    orientation.setToIdentity();
    rotX = 0;
    rotY = 0;
    rotZ = 0;
}

Blocks::~Blocks()
{

}

QVector3D Blocks::getLastRotation()
{
    return lastRotation;
}

bool Blocks::ifAlreadyRotated()
{
    return lastRotation==QVector3D(0,0,0) ? false : true;
}

void Blocks::updateLastRotation(QVector3D rot)
{
    lastRotation = rot;
    QMatrix4x4 tmp;
    tmp.setToIdentity();
    tmp.rotate(QQuaternion::fromAxisAndAngle(rot,90));
    qDebug() << "^^^^^^^^^^^^^^^^^^^^^^BEFORE^^^^^^^^^^^^^^^^^^^^^^^^^^";
    qDebug() << Position;
    Position = Position * tmp;

    orientation.setToIdentity();
    Position.setX(int(Position.x()));
    Position.setY(int(Position.y()));
    Position.setZ(int(Position.z()));
    qDebug() << "^^^^^^^^^^^^^^^^^^^^^^AFTER^^^^^^^^^^^^^^^^^^^^^^^^^^";
    qDebug() << Position;
    mMatrix.setToIdentity();

}

QMatrix4x4 Blocks::getModelMatrix()
{
    return mMatrix;
}

QVector3D Blocks::getPosition()
{
    return Position;
}
QMatrix4x4 Blocks::getOrientation()
{
    return orientation;
}


bool Blocks::getMembersForRotation(int coord, int index)
{
    bool answer = false;

    if(coord == 0)
    {
        rotX += 1;
        if(rotX == 4)
            rotX = 0;

        if(index == 0)
        {
            if(Position.x() == -2)
                answer = true;
        }
        if(index == 1)
        {
            if(Position.x() == 0)
                answer = true;
        }
        if(index == 2)
        {
            if(Position.x() == 2)
                answer = true;
        }
    }
    if(coord == 1)
    {
        rotY += 1;
        if(rotY == 4)
            rotY = 0;
        if(index == 0)
        {
            if(Position.y() == -2)
                answer = true;
        }
        if(index == 1)
        {
            if(Position.y() == 0)
                answer = true;
        }
        if(index == 2)
        {
            if(Position.y() == 2)
                answer = true;
        }
    }
    if(coord == 2)
    {
        rotZ += 1;
        if(rotZ == 4)
            rotZ = 0;
        if(index == 0)
        {
            if(Position.z() == 2)
                answer = true;
        }
        if(index == 1)
        {
            if(Position.z() == 0)
                answer = true;
        }
        if(index == 2)
        {
            if(Position.z() == -2)
                answer = true;
        }
    }

//    if(QVector3D::dotProduct(Position,tmpVec) == QVector3D::dotProduct(tmpVec,tmpVec))
//        return this;

    return answer;
}

