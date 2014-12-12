#include "Visualizer.h"

Visualizer::Visualizer(QWidget *parent) :
    QGLWidget(parent)
{
    alpha = 25;
    beta = -25;
    distance = 2.5;

    rotationStep = 5;
    selectedGroup = 0;
    stopRotation = 18;

    isRotating = false;

    m_coord = 0;
    m_coordInx = 0;

    lightAngle = 0;
    startTimer = false;
    rotateAngle = 0;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(timeout()));
    timer->start(1);



    Blocks *tmpBlock0 = new Blocks(QVector3D(-2,-2,2));
    myBlocks << tmpBlock0;
    Blocks *tmpBlock1 = new Blocks(QVector3D(0,-2,2));
    myBlocks << tmpBlock1;
    Blocks *tmpBlock2 = new Blocks(QVector3D(2,-2,2));
    myBlocks << tmpBlock2;
    Blocks *tmpBlock3 = new Blocks(QVector3D(-2,0,2));
    myBlocks << tmpBlock3;
    Blocks *tmpBlock4 = new Blocks(QVector3D(0,0,2));
    myBlocks << tmpBlock4;
    Blocks *tmpBlock5 = new Blocks(QVector3D(2,0,2));
    myBlocks << tmpBlock5;
    Blocks *tmpBlock6 = new Blocks(QVector3D(-2,2,2));
    myBlocks << tmpBlock6;
    Blocks *tmpBlock7 = new Blocks(QVector3D(0,2,2));
    myBlocks << tmpBlock7;
    Blocks *tmpBlock8 = new Blocks(QVector3D(2,2,2));
    myBlocks << tmpBlock8;
    Blocks *tmpBlock9 = new Blocks(QVector3D(-2,-2,0));
    myBlocks << tmpBlock9;
    Blocks *tmpBlock10 = new Blocks(QVector3D(0,-2,0));
    myBlocks << tmpBlock10;
    Blocks *tmpBlock11 = new Blocks(QVector3D(2,-2,0));
    myBlocks << tmpBlock11;
    Blocks *tmpBlock12 = new Blocks(QVector3D(-2,0,0));
    myBlocks << tmpBlock12;
    Blocks *tmpBlock13 = new Blocks(QVector3D(0,0,0));
    myBlocks << tmpBlock13;
    Blocks *tmpBlock14 = new Blocks(QVector3D(2,0,0));
    myBlocks << tmpBlock14;
    Blocks *tmpBlock15 = new Blocks(QVector3D(-2,2,0));
    myBlocks << tmpBlock15;
    Blocks *tmpBlock16 = new Blocks(QVector3D(0,2,0));
    myBlocks << tmpBlock16;
    Blocks *tmpBlock17 = new Blocks(QVector3D(2,2,0));
    myBlocks << tmpBlock17;
    Blocks *tmpBlock18 = new Blocks(QVector3D(-2,-2,-2));
    myBlocks << tmpBlock18;
    Blocks *tmpBlock19 = new Blocks(QVector3D(0,-2,-2));
    myBlocks << tmpBlock19;
    Blocks *tmpBlock20 = new Blocks(QVector3D(2,-2,-2));
    myBlocks << tmpBlock20;
    Blocks *tmpBlock21 = new Blocks(QVector3D(-2,0,-2));
    myBlocks << tmpBlock21;
    Blocks *tmpBlock22 = new Blocks(QVector3D(0,0,-2));
    myBlocks << tmpBlock22;
    Blocks *tmpBlock23 = new Blocks(QVector3D(2,0,-2));
    myBlocks << tmpBlock23;
    Blocks *tmpBlock24 = new Blocks(QVector3D(-2,2,-2));
    myBlocks << tmpBlock24;
    Blocks *tmpBlock25 = new Blocks(QVector3D(0,2,-2));
    myBlocks << tmpBlock25;
    Blocks *tmpBlock26 = new Blocks(QVector3D(2,2,-2));
    myBlocks << tmpBlock26;



}
Visualizer::~Visualizer()
{
    for(int i=0;i<myBlocks.size();i++)
        delete myBlocks.value(i);

}

QSize Visualizer::sizeHint() const
{
    return QSize(800,600);
}


void Visualizer::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    qglClearColor(QColor(Qt::black));

    QFile file("../../../../RubicCubeSolver/objects/box3.obj");
    int x;
    for(int i=0;i<27;i++)
        x = ObjectLoader(&file);

    //Bind Fragment and Vertex Shader for the Cube
    QGLShaderProgram* tmpShaderProg = new QGLShaderProgram;
    tmpShaderProg->addShaderFromSourceFile(QGLShader::Vertex, "../../../../RubicCubeSolver/lightingVertexShader2.vs");
    tmpShaderProg->addShaderFromSourceFile(QGLShader::Fragment, "../../../../RubicCubeSolver/lightingFragmentShader2.fs");
    tmpShaderProg->link();

    lightingShaderProgram.addShaderFromSourceFile(QGLShader::Vertex, "../../../../RubicCubeSolver/lightingVertexShader.vs");
    lightingShaderProgram.addShaderFromSourceFile(QGLShader::Fragment, "../../../../RubicCubeSolver/lightingFragmentShader.fs");
    lightingShaderProgram.link();

    cubeVertices << QVector3D(-0.5, -0.5,  0.5) << QVector3D( 0.5, -0.5,  0.5) << QVector3D( 0.5,  0.5,  0.5) << QVector3D(-0.5,  0.5,  0.5) // Front
                 << QVector3D( 0.5, -0.5, -0.5) << QVector3D(-0.5, -0.5, -0.5) << QVector3D(-0.5,  0.5, -0.5) << QVector3D( 0.5,  0.5, -0.5) // Back
                 << QVector3D(-0.5, -0.5, -0.5) << QVector3D(-0.5, -0.5,  0.5) << QVector3D(-0.5,  0.5,  0.5) << QVector3D(-0.5,  0.5, -0.5) // Left
                 << QVector3D( 0.5, -0.5,  0.5) << QVector3D( 0.5, -0.5, -0.5) << QVector3D( 0.5,  0.5, -0.5) << QVector3D( 0.5,  0.5,  0.5) // Right
                 << QVector3D(-0.5,  0.5,  0.5) << QVector3D( 0.5,  0.5,  0.5) << QVector3D( 0.5,  0.5, -0.5) << QVector3D(-0.5,  0.5, -0.5) // Top
                 << QVector3D(-0.5, -0.5, -0.5) << QVector3D( 0.5, -0.5, -0.5) << QVector3D( 0.5, -0.5,  0.5) << QVector3D(-0.5, -0.5,  0.5);// Bottom

    cubeTextureCoordinates << QVector2D(0, 0) << QVector2D(1, 0) << QVector2D(1, 1) << QVector2D(0, 1) // Front
                           << QVector2D(0, 0) << QVector2D(1, 0) << QVector2D(1, 1) << QVector2D(0, 1) // Front
                           << QVector2D(0, 0) << QVector2D(1, 0) << QVector2D(1, 1) << QVector2D(0, 1) // Front
                           << QVector2D(0, 0) << QVector2D(1, 0) << QVector2D(1, 1) << QVector2D(0, 1) // Front
                           << QVector2D(0, 0) << QVector2D(1, 0) << QVector2D(1, 1) << QVector2D(0, 1) // Front
                           << QVector2D(0, 0) << QVector2D(1, 0) << QVector2D(1, 1) << QVector2D(0, 1);// Front

    cubeNormals << QVector3D( 0,  0,  1) << QVector3D( 0,  0,  1) << QVector3D( 0,  0,  1) << QVector3D( 0,  0,  1) // Front
                << QVector3D( 0,  0, -1) << QVector3D( 0,  0, -1) << QVector3D( 0,  0, -1) << QVector3D( 0,  0, -1) // Back
                << QVector3D(-1,  0,  0) << QVector3D(-1,  0,  0) << QVector3D(-1,  0,  0) << QVector3D(-1,  0,  0) // Left
                << QVector3D( 1,  0,  0) << QVector3D( 1,  0,  0) << QVector3D( 1,  0,  0) << QVector3D( 1,  0,  0) // Right
                << QVector3D( 0,  1,  0) << QVector3D( 0,  1,  0) << QVector3D( 0,  1,  0) << QVector3D( 0,  1,  0) // Top
                << QVector3D( 0, -1,  0) << QVector3D( 0, -1,  0) << QVector3D( 0, -1,  0) << QVector3D( 0, -1,  0); // Bottom

    cubeTexture = bindTexture(QPixmap("../../../../RubicCubeSolver/texture.png"));

//    QGLBuffer* tmpBuffer = WriteBufferData(cubeVertices,cubeNormals,cubeTextureCoordinates);
//    m_pBufferList.append(new m_pBufferShaderList(2, cubeVertices.size(), tmpBuffer, tmpShaderProg));
    for(int i=0;i<27;i++)
    {
    m_pBufferList[i]->shaderProgram = tmpShaderProg;
    m_pBufferList[i]->variable1 = "vertex";
    m_pBufferList[i]->variable2 = "normal";
    m_pBufferList[i]->variable3 = "color";
    m_pBufferList[i]->numVaiables = 3;
    }

    //Bind Fragment and Vertex shadet for the Rotating Spotlight

    coloringShaderProgram.addShaderFromSourceFile(QGLShader::Vertex, "../../../../RubicCubeSolver/coloringVertexShader.vs");
    coloringShaderProgram.addShaderFromSourceFile(QGLShader::Fragment, "../../../../RubicCubeSolver/coloringFragmentShader.fs");
    coloringShaderProgram.link();

    spotlightVertices << QVector3D(   0,    1,    0) << QVector3D(-0.5,    0,  0.5) << QVector3D( 0.5,    0,  0.5) // Front
                      << QVector3D(   0,    1,    0) << QVector3D( 0.5,    0, -0.5) << QVector3D(-0.5,    0, -0.5) // Back
                      << QVector3D(   0,    1,    0) << QVector3D(-0.5,    0, -0.5) << QVector3D(-0.5,    0,  0.5) // Left
                      << QVector3D(   0,    1,    0) << QVector3D( 0.5,    0,  0.5) << QVector3D( 0.5,    0, -0.5) // Right
                      << QVector3D(-0.5,    0, -0.5) << QVector3D( 0.5,    0, -0.5) << QVector3D( 0.5,    0,  0.5) // Bottom
                      << QVector3D( 0.5,    0,  0.5) << QVector3D(-0.5,    0,  0.5) << QVector3D(-0.5,    0, -0.5);
    spotlightColors << QVector3D(0.2, 0.2, 0.2) << QVector3D(0.2, 0.2, 0.2) << QVector3D(0.2, 0.2, 0.2) // Front
                    << QVector3D(0.2, 0.2, 0.2) << QVector3D(0.2, 0.2, 0.2) << QVector3D(0.2, 0.2, 0.2) // Back
                    << QVector3D(0.2, 0.2, 0.2) << QVector3D(0.2, 0.2, 0.2) << QVector3D(0.2, 0.2, 0.2) // Left
                    << QVector3D(0.2, 0.2, 0.2) << QVector3D(0.2, 0.2, 0.2) << QVector3D(0.2, 0.2, 0.2) // Right
                    << QVector3D(  1,   1,   1) << QVector3D(  1,   1,   1) << QVector3D(  1,   1,   1) // Bottom
                    << QVector3D(  1,   1,   1) << QVector3D(  1,   1,   1) << QVector3D(  1,   1,   1);

    //Bind Fragment and Vertex shadet for the non-Rotating left-Spotlight

    leftlightShaderProgram.addShaderFromSourceFile(QGLShader::Vertex, "../../../../RubicCubeSolver/leftlightVertexShader.vs");
    leftlightShaderProgram.addShaderFromSourceFile(QGLShader::Fragment, "../../../../RubicCubeSolver/leftlightFragmentShader.fs");
    leftlightShaderProgram.link();


    //Writing Buffer Vertices, Normals and textures for the Cube

    numCubeVertices = 24;
    cubeBuffer.create();
    cubeBuffer.bind();
    cubeBuffer.allocate(numCubeVertices * (3+3+2) * sizeof (GLfloat));
    int offset = 0;
    cubeBuffer.write(offset, cubeVertices.constData(), numCubeVertices * 3 * sizeof (GLfloat));
    offset += numCubeVertices * 3 * sizeof (GLfloat);
    cubeBuffer.write(offset, cubeNormals.constData(), numCubeVertices * 3 * sizeof (GLfloat));
    offset += numCubeVertices * 3 * sizeof (GLfloat);
    cubeBuffer.write(offset, cubeTextureCoordinates.constData(), numCubeVertices * 2 *sizeof (GLfloat));
    cubeBuffer.release();

    //Writting Buffer Vertices and Colors for the Rotating spotlight

    numSpotlightVertices = 18;
    spotlightBuffer.create();
    spotlightBuffer.bind();
    spotlightBuffer.allocate(numSpotlightVertices * (3+3) * sizeof (GLfloat));
    offset = 0;
    spotlightBuffer.write(offset, spotlightVertices.constData(), numSpotlightVertices * 3 * sizeof (GLfloat));
    offset += numSpotlightVertices * 3 * sizeof (GLfloat);
    spotlightBuffer.write(offset, spotlightColors.constData(), numSpotlightVertices * 3 * sizeof (GLfloat));
    offset += numSpotlightVertices * 3 * sizeof (GLfloat);
    spotlightBuffer.release();
}
void Visualizer::resizeGL(int width,int height)
{
    if (height == 0)
        height = 1;
    pMatrix.setToIdentity();
    pMatrix.perspective(60.0, (float) width / (float) height, 0.001, 1000);

    glViewport(0, 0, width, height);
}
void Visualizer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 mMatrix;
    QMatrix4x4 vMatrix;

    QMatrix4x4 cameraTransformation;
    cameraTransformation.rotate(alpha,0,1,0);
    cameraTransformation.rotate(beta,1,0,0);

    QVector3D cameraPosition = cameraTransformation * QVector3D(0,0,distance);
    QVector3D cameraUpDirection = cameraTransformation * QVector3D(0,1,0);

    vMatrix.lookAt(cameraPosition,QVector3D(0,0,0),cameraUpDirection);

    mMatrix.setToIdentity();

    QMatrix4x4 mvMatrix;
    mvMatrix = vMatrix * mMatrix;

    QMatrix3x3 normalMatrix;
    normalMatrix = mvMatrix.normalMatrix();

    QMatrix4x4 lightTransformation;
    lightTransformation.rotate(lightAngle,0 ,1, 0);

    //QVector3D lightPosition = lightTransformation * QVector3D(0,1,1);
    QVector3D lightPosition = QVector3D(0,1,1);
    QVector3D leftlightPosition = QVector3D(-1,0,0);

    int offset;
//    for(int k=0;k<myBlocks.size();k++)
    for(int k=0;k<27;k++)
    {

        mMatrix.setToIdentity();

//        mMatrix *= stones[k].mMatrix;
//        mMatrix.translate(stones[k].position);
        if(isRotating)
        {
            mMatrix = myBlocks.value(k)->getModelMatrix() * mMatrix;
            mMatrix.translate(myBlocks.value(k)->getPosition());
        }
        if(!isRotating)
        {

            mMatrix.translate(myBlocks.value(k)->getPosition());
            mMatrix = myBlocks.value(k)->getOrientation() * mMatrix ;
        }
        //mMatrix = myBlocks.value(k)->getOrientation() * mMatrix;

        mMatrix.scale(1);
        mvMatrix = vMatrix * mMatrix;
        normalMatrix = mvMatrix.normalMatrix();

        m_pBufferList[k]->shaderProgram->bind();
        m_pBufferList[k]->shaderProgram->setUniformValue("mvpMatrix", pMatrix * mvMatrix);
        m_pBufferList[k]->shaderProgram->setUniformValue("mvMatrix", mvMatrix);
        m_pBufferList[k]->shaderProgram->setUniformValue("normalMatrix", normalMatrix);
        m_pBufferList[k]->shaderProgram->setUniformValue("lightPosition", vMatrix * lightPosition);
        m_pBufferList[k]->shaderProgram->setUniformValue("leftlightPosition", vMatrix * leftlightPosition);

        m_pBufferList[k]->shaderProgram->setUniformValue("ambientColor", QColor(162,162,162));
        m_pBufferList[k]->shaderProgram->setUniformValue("diffuseColor", QColor(128,128,128));
        m_pBufferList[k]->shaderProgram->setUniformValue("specularColor", QColor(255,255,255));
        m_pBufferList[k]->shaderProgram->setUniformValue("ambientReflection", (GLfloat) 1.0);
        m_pBufferList[k]->shaderProgram->setUniformValue("diffuseReflection", (GLfloat) 1.0);
        m_pBufferList[k]->shaderProgram->setUniformValue("specularReflection", (GLfloat) 1.0);
        m_pBufferList[k]->shaderProgram->setUniformValue("shininess", (GLfloat) 100.0);
        //m_pBufferList[0]->shaderProgram->setUniformValue("texture",0);

        //glBindTexture(GL_TEXTURE_2D,cubeTexture);



        WriteBufferToGPU(m_pBufferList[k],0);
        glDrawArrays(GL_TRIANGLES, 0, m_pBufferList[k]->numVertices);
        releaseShaderProgram(m_pBufferList[k],0);

    }


    mMatrix.setToIdentity();
    mMatrix.translate(lightPosition);
    mMatrix.rotate(lightAngle,0,1,0);
    mMatrix.rotate(45,1,0,0);
    mMatrix.scale(0.1);

    coloringShaderProgram.bind();

    coloringShaderProgram.setUniformValue("mvpMatrix", pMatrix*vMatrix*mMatrix);

    offset = 0;
    spotlightBuffer.bind();
    coloringShaderProgram.setAttributeBuffer("vertex", GL_FLOAT, offset, 3, 0);
    coloringShaderProgram.enableAttributeArray("vertex");
    offset += numSpotlightVertices * 3 * sizeof (GLfloat);
    coloringShaderProgram.setAttributeBuffer("color", GL_FLOAT, offset, 3, 0);
    coloringShaderProgram.enableAttributeArray("color");

    glDrawArrays(GL_TRIANGLES, 0, spotlightVertices.size());

    coloringShaderProgram.disableAttributeArray("vertex");
    coloringShaderProgram.disableAttributeArray("color");

    coloringShaderProgram.release();

    mMatrix.setToIdentity();
    mMatrix.translate(-2,0,0);
    mMatrix.scale(0.1);

    leftlightShaderProgram.bind();
    leftlightShaderProgram.setUniformValue("mvpMatrix", pMatrix*vMatrix*mMatrix);

    blenderObjectFileBuffer.bind();
    offset = 0;
    leftlightShaderProgram.setAttributeBuffer("vertex", GL_FLOAT, offset, 3, 0);
    leftlightShaderProgram.enableAttributeArray("vertex");
    offset += numSpotlightVertices * 3 * sizeof (GLfloat);
    leftlightShaderProgram.setAttributeBuffer("color", GL_FLOAT, offset, 3, 0);
    leftlightShaderProgram.enableAttributeArray("color");

    glDrawArrays(GL_TRIANGLES, 0, 12);

    leftlightShaderProgram.disableAttributeArray("vertex");
    leftlightShaderProgram.disableAttributeArray("color");

    leftlightShaderProgram.release();

}

void Visualizer::mousePressEvent(QMouseEvent *event)
{
    lastMousePosition = event->pos();

    event->accept();
}

void Visualizer::mouseMoveEvent(QMouseEvent *event)
{
    int deltaX = event->x() - lastMousePosition.x();
    int deltaY = event->y() - lastMousePosition.y();
    if(event->buttons() & Qt::LeftButton)
    {
        alpha -= deltaX;
        if (alpha<0)
            alpha+=360;
        if (alpha>=360)
            alpha-=360;

        beta -= deltaY;
        if (beta<-90)
            beta=-90;
        if (beta>90)
            beta=90;

        updateGL();
    }
    lastMousePosition = event->pos();
    event->accept();
}

void Visualizer::wheelEvent(QWheelEvent *event)
{
    int delta = event->delta();

    if(event->orientation() == Qt::Vertical)
    {
        if(delta<0)
            distance *= 1.1;
        else if(delta>0)
            distance *=0.9;
        updateGL();
    }
    event->accept();

}

void Visualizer::keyPressEvent(QKeyEvent *event)
{
    if(!startTimer){
        if(event->key() == Qt::Key_D)
        {
            selectedGroup = 2;
            m_coord = 0;
            m_coordInx = 2;
            startTimer = true;
        }
        if(event->key() == Qt::Key_S)
        {
            selectedGroup = 1;
            m_coord = 0;
            m_coordInx = 1;
            startTimer = true;
        }
        if(event->key() == Qt::Key_A)
        {
            m_coord = 0;
            m_coordInx = 0;
            selectedGroup = 0;
            startTimer = true;
        }
        if(event->key() == Qt::Key_R)
        {
            selectedGroup = 8;
            m_coord = 2;
            m_coordInx = 2;
            startTimer = true;
        }
        if(event->key() == Qt::Key_F)
        {
            selectedGroup = 7;
            m_coord = 2;
            m_coordInx = 1;
            startTimer = true;
        }
        if(event->key() == Qt::Key_V)
        {
            selectedGroup = 6;
            m_coord = 2;
            m_coordInx = 0;
            startTimer = true;
        }
        if(event->key() == Qt::Key_G)
        {
            selectedGroup = 4;
            m_coord = 1;
            m_coordInx = 1;
            startTimer = true;
        }
        if(event->key() == Qt::Key_T)
        {
            selectedGroup = 5;
            m_coord = 1;
            m_coordInx = 2;
            startTimer = true;
        }
        if(event->key() == Qt::Key_B)
        {
            selectedGroup = 3;
            m_coord = 1;
            m_coordInx = 0;
            startTimer = true;
        }
    }
}


void Visualizer::timeout()
{
    //QVector3D upDateRotation;

    if(startTimer && stopRotation!=0)
    {
        isRotating = true;
        QVector3D Rotation;
        if(selectedGroup==3 || selectedGroup==4 || selectedGroup==5)
            Rotation = QVector3D(0,1,0);
        if(selectedGroup==0 || selectedGroup==1 || selectedGroup==2)
            Rotation = QVector3D(1,0,0);
        if(selectedGroup==6 || selectedGroup==7 || selectedGroup==8)
            Rotation = QVector3D(0,0,1);

        for(int i = 0; i<myBlocks.size();i++)
        {
            if(myBlocks[i]->getMembersForRotation(m_coord,m_coordInx))
                myBlocks[i]->mMatrix.rotate(QQuaternion::fromAxisAndAngle(Rotation,-rotationStep));
        }

        stopRotation -= 1;
        if(stopRotation==0)
        {
            for(int i = 0; i<myBlocks.size();i++)
            {
                if(myBlocks[i]->getMembersForRotation(m_coord,m_coordInx))
                    myBlocks[i]->updateLastRotation(Rotation);
            }
        }

    }
    else
    {
        isRotating = false;
        startTimer = false;
        stopRotation = 18;
        selectedGroup = 0;
    }

    lightAngle += 1;
    while (lightAngle >= 360)
        lightAngle -= 360;
    updateGL();
}

int Visualizer::ObjectLoader(QFile *filename)
{

    if(!filename->open(QIODevice::ReadOnly))
    {
        qDebug() << "error opening file: " << filename->error();
        return 0;
    }
    QList<QVector3D> SceneObjectPoints;
    QList<QVector4D> ObjectFaceVertices;
    QList<QVector3D> SceneObjectNormals;
    QList<QVector3D> colors;
    QVector<QVector3D> SceneObjectVertices;
    QVector<QVector3D> SceneObjectColors;
    QVector<QVector3D> SceneObjectFaceNormals;
    QVector<QVector2D> MaterialAssigner;
    QList<QString> tmpFullText;
    QTextStream *in = new QTextStream(filename);
    while(!in->atEnd())
    {
        tmpFullText.append(in->readLine());
    }
    filename->close();
    float tmpx,tmpy,tmpz;
    int a,b,c,d,faceMaterialIndex = 0;

    for(int i=0;i<tmpFullText.size();i++)
    {
        if(tmpFullText[i].toStdString().c_str()[0]=='#')
            continue;
        else if(tmpFullText[i].toStdString().c_str()[0]=='v' && tmpFullText[i].toStdString().c_str()[1]==' ')
        {
            sscanf(tmpFullText[i].toStdString().c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);
            SceneObjectPoints.append(QVector3D(tmpx,tmpy,tmpz));
        }
        else if(tmpFullText[i].toStdString().c_str()[0]=='v' && tmpFullText[i].toStdString().c_str()[1]=='n')
        {
            sscanf(tmpFullText[i].toStdString().c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
            SceneObjectNormals.append(QVector3D(tmpx,tmpy,tmpz));
        }

        else if(tmpFullText[i].toStdString().c_str()[0]=='f' && tmpFullText[i].toStdString().c_str()[1]==' ')
        {
            sscanf(tmpFullText[i].toStdString().c_str(),"f %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b);
            ObjectFaceVertices.append(QVector4D(a,c,d,b));
            faceMaterialIndex += 1;

        }
        else if(tmpFullText[i].toStdString().c_str()[0]=='u' && tmpFullText[i].toStdString().c_str()[1]=='s')
        {
            if(tmpFullText[i].toStdString().c_str()[15]==' ')
                MaterialAssigner.append(QVector2D(0,faceMaterialIndex));
            else
                MaterialAssigner.append(QVector2D(tmpFullText[i].toStdString().c_str()[18],faceMaterialIndex));
        }
    }

    QFile file("../../../../RubicCubeSolver/objects/box3.mtl");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "error opening Material file: " << file.error();
        return 0;
    }
    in = new QTextStream(&file);
    tmpFullText.clear();

    while(!in->atEnd())
    {
        tmpFullText.append(in->readLine());
    }
    file.close();

    for(int i=0;i<tmpFullText.size();i++)
    {
        if(tmpFullText[i].toStdString().c_str()[0]=='K' && tmpFullText[i].toStdString().c_str()[1]=='d')
        {
            sscanf(tmpFullText[i].toStdString().c_str(),"Kd %f %f %f",&tmpx,&tmpy,&tmpz);
            colors.append(QVector3D(tmpx,tmpy,tmpz));
        }
    }

    int counter = 0;

    for(int i=0;i<ObjectFaceVertices.size();i++)
    {

       SceneObjectVertices << SceneObjectPoints[(ObjectFaceVertices[i].x())-1]
                           << SceneObjectPoints[(ObjectFaceVertices[i].y())-1]
                           << SceneObjectPoints[(ObjectFaceVertices[i].z())-1];
       SceneObjectFaceNormals << SceneObjectNormals[(ObjectFaceVertices[i].w())-1]
                              << SceneObjectNormals[(ObjectFaceVertices[i].w())-1]
                              << SceneObjectNormals[(ObjectFaceVertices[i].w())-1];
       if(MaterialAssigner[counter+1].y()==i)
           counter++;
       SceneObjectColors << colors[counter] << colors[counter] << colors[counter];
    }

    QGLBuffer *tmpBuffer = WriteBufferData(SceneObjectVertices, SceneObjectFaceNormals, SceneObjectColors);
    m_pBufferList.append(new m_pBufferShaderList(1, SceneObjectVertices.size(), tmpBuffer));

    delete in;
}

QGLBuffer* Visualizer::WriteBufferData(QVector<QVector3D> vertices, QVector<QVector3D> normals, QVector<QVector3D> colors)
{
    QGLBuffer* tmp = new QGLBuffer;
    tmp->create();
    tmp->bind();
    int offset = 0;
    tmp->allocate(vertices.size() * (3+3+3) * sizeof (GLfloat));
    tmp->write(offset, vertices.constData() , vertices.size() * 3 * sizeof (GLfloat));
    offset += vertices.size() * 3 * sizeof (GLfloat);
    tmp->write(offset, normals.constData(), normals.size() * 3 * sizeof (GLfloat));
    offset += normals.size() * 3 * sizeof (GLfloat);
    tmp->write(offset, colors.constData(), colors.size() * 3 * sizeof (GLfloat));
    tmp->release();
    return tmp;

}

QGLBuffer *Visualizer::WriteBufferData(QVector<QVector3D> vertices, QVector<QVector3D> normals, QVector<QVector2D> textures)
{
    QGLBuffer* tmp = new QGLBuffer;
    tmp->create();
    tmp->bind();
    int offset = 0;
    tmp->allocate(vertices.size() * (3+3+2) * sizeof (GLfloat));
    tmp->write(offset, vertices.constData() , vertices.size() * 3 * sizeof (GLfloat));
    offset += vertices.size() * 3 * sizeof (GLfloat);
    tmp->write(offset, normals.constData(), normals.size() * 3 * sizeof (GLfloat));
    offset += normals.size() * 3 * sizeof (GLfloat);
    tmp->write(offset, textures.constData(), textures.size() * 2 * sizeof (GLfloat));
    tmp->release();
    return tmp;
}

QGLBuffer* Visualizer::WriteBufferData(QVector<QVector3D> vertices, QVector<QVector3D> colors)
{

    QGLBuffer* tmp = new QGLBuffer;
    tmp->create();
    tmp->bind();
    int offset = 0;
    tmp->allocate(vertices.size() * (3+3) * sizeof (GLfloat));
    tmp->write(offset, vertices.constData() , vertices.size() * 3 * sizeof (GLfloat));
    offset += vertices.size() * 3 * sizeof (GLfloat);
    tmp->write(offset, colors.constData(), colors.size() * 3 * sizeof (GLfloat));
    tmp->release();
    return tmp;
}

void Visualizer::WriteBufferToGPU(m_pBufferShaderList* list,int id)
{
    list[id].buffer->bind();
    int offset = 0;
    list[id].shaderProgram->setAttributeBuffer(list[id].variable1.toStdString().c_str(), GL_FLOAT, offset, 3, 0);
    list[id].shaderProgram->enableAttributeArray(list[id].variable1.toStdString().c_str());
    offset += list[id].numVertices * 3 * sizeof (GLfloat);
    list[id].shaderProgram->setAttributeBuffer(list[id].variable2.toStdString().c_str(), GL_FLOAT, offset, 3, 0);
    list[id].shaderProgram->enableAttributeArray(list[id].variable2.toStdString().c_str());
    offset += list[id].numVertices * 3 * sizeof (GLfloat);
    if(list[id].numVaiables==3 && list[id].variable3 == "textureCoordinate")
    {

        list[id].shaderProgram->setAttributeBuffer(list[id].variable3.toStdString().c_str(), GL_FLOAT, offset, 2, 0);
        list[id].shaderProgram->enableAttributeArray(list[id].variable3.toStdString().c_str());
    }
    if(list[id].numVaiables==3 && list[id].variable3 != "textureCoordinate")
    {

        list[id].shaderProgram->setAttributeBuffer(list[id].variable3.toStdString().c_str(), GL_FLOAT, offset, 3, 0);
        list[id].shaderProgram->enableAttributeArray(list[id].variable3.toStdString().c_str());
    }
    //list[id].shaderProgram->release();
}

void Visualizer::releaseShaderProgram(m_pBufferShaderList *list, int id)
{
    list[id].shaderProgram->disableAttributeArray(list[id].variable1.toStdString().c_str());
    list[id].shaderProgram->disableAttributeArray(list[id].variable2.toStdString().c_str());
    if(list[id].variable3!= " ")
        list[id].shaderProgram->disableAttributeArray(list[id].variable3.toStdString().c_str());

    list[id].shaderProgram->release();

}

float Visualizer::degToRad(float n)
{
    return n*3.14/180.0;
}
