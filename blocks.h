#pragma once

#include <QObject>
#include <QVector3D>
#include <QMatrix4x4>


class Blocks : public QObject
{
    Q_OBJECT
public:
    explicit Blocks(QVector3D position);
    ~Blocks();
    QVector3D getLastRotation();
    bool ifAlreadyRotated();
    void updateLastRotation(QVector3D rot);
    QMatrix4x4 getModelMatrix();
    QVector3D getPosition();
    bool getMembersForRotation(int coord, int index);

    QMatrix4x4 getOrientation();

    QMatrix4x4 mMatrix;

    QVector3D Position;
    int rotX,rotY,rotZ;
signals:

public slots:

private:
    QMatrix4x4 orientation;
    QVector3D lastRotation;   //last Rotation of the block




};


