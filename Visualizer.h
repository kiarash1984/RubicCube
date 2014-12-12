#pragma once

#include <QObject>
#include <QGLWidget>
#include <QGLShaderProgram>
#include <QDebug>
#include <QVector>
#include <QVector3D>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QTimer>
#include <QGLBuffer>
#include <QString>
#include <QTextStream>
#include <QChar>
#include <blocks.h>
#include <math.h>



struct m_pBufferShaderList{
    int id;
    QGLBuffer* buffer;
    int numVertices;
    int numVaiables;
    QString variable1;
    QString variable2;
    QString variable3;
    QGLShaderProgram* shaderProgram;
    m_pBufferShaderList(int a, int n, QGLBuffer* b) : id(a), numVertices(n),buffer(b), shaderProgram(NULL){}
    m_pBufferShaderList(int a, int n, QGLBuffer* b,QGLShaderProgram* s) : id(a), numVertices(n), buffer(b), shaderProgram(s){}
};

class Visualizer : public QGLWidget
{
    Q_OBJECT
public:
    Visualizer(QWidget *parent = 0);
    ~Visualizer();
    QSize sizeHint() const;
    int ObjectLoader(QFile *filename);
    QGLBuffer* WriteBufferData(QVector<QVector3D> vertices, QVector<QVector3D> normals, QVector<QVector3D> colors);
    QGLBuffer* WriteBufferData(QVector<QVector3D> vertices, QVector<QVector3D> normals, QVector<QVector2D> textures);
    QGLBuffer* WriteBufferData(QVector<QVector3D> vertices, QVector<QVector3D> colors);
    void WriteBufferToGPU(m_pBufferShaderList *list,int id);
    void releaseShaderProgram(m_pBufferShaderList *list, int id);
    float degToRad(float);

protected:
    void initializeGL();
    void resizeGL(int width,int height);
    void paintGL();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);

signals:


public slots:


private:

    QString *m_pSourceCode;
    QMatrix4x4 pMatrix;
    QGLShaderProgram coloringShaderProgram;
    QGLShaderProgram lightingShaderProgram;
    QGLShaderProgram leftlightShaderProgram;
    QVector<QVector3D> cubeVertices;
    QVector<QVector3D> cubeNormals;
    QVector<QVector3D> spotlightVertices;
    QVector<QVector2D> cubeTextureCoordinates;
    QVector<QVector3D> spotlightColors;

    double lightAngle;
    GLuint cubeTexture;

    QList<m_pBufferShaderList*> m_pBufferList;
    QMap<QGLBuffer*,QGLShaderProgram*> m_pShaderProgramAssigner;
    QGLBuffer cubeBuffer;
    QGLBuffer spotlightBuffer;
    QGLBuffer blenderObjectFileBuffer;

    int numSpotlightVertices;
    int numCubeVertices;

    double alpha;
    double beta;
    double distance;
    QPoint lastMousePosition;

    bool startTimer;
    int rotateAngle;
    int stopRotation;

    float rotationStep;
    int selectedGroup;

    QList<Blocks*> myBlocks;

    bool isRotating;




    int m_coord;
    int m_coordInx;

private Q_SLOTS:
    void timeout();
};


