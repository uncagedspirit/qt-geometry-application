#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
}

void MyOpenGLWidget::addShape(const QString& name, const QString& type)
{
    std::shared_ptr<Shape> shape;

    if (type == "Sphere")
        shape = std::make_shared<Sphere>(name);
    else if (type == "Cylinder")
        shape = std::make_shared<Cylinder>(name);
    else if (type == "Cuboid")
        shape = std::make_shared<Cuboid>(name);

    if (shape)
        shapesToRender.push_back(shape);  

    update();
}


void MyOpenGLWidget::removeShape(const QString& name)
{

    for (int i = 0; i < shapesToRender.size(); ++i) {
        if (shapesToRender[i]->name == name) {
            shapesToRender.remove(i);
            break;
        }
    }
    update();
}


void MyOpenGLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glShadeModel(GL_SMOOTH);

    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightPosition[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    GLfloat matSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat matShininess[] = { 5.0f };
    // glMaterialfv(GL_FRONT, GL_AMBIENT, lightAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, lightDiffuse);
    // glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

    glEnable(GL_NORMALIZE);
}

void MyOpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = float(w) / float(h ? h : 1);
    float fovY = 45.0f;
    float near = 0.1f;
    float far = 100.0f;
    float top = tan(fovY * M_PI / 360.0f) * near;
    float bottom = -top;
    float right = top * aspect;
    float left = -right;

    glFrustum(left, right, bottom, top, near, far);

    glMatrixMode(GL_MODELVIEW);
}


void MyOpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);

    for (auto shape : shapesToRender) {
        glPushMatrix();
        glTranslatef(shape->posX, shape->posY, 0.0f);

        if (shape->type() == "Sphere")
            renderSphere();
        else if (shape->type() == "Cylinder")
            renderCylinder();

        glPopMatrix();
    }
}

void MyOpenGLWidget::renderSphere()
{
    const float radius = 1.0f;
    const int slices = 30;
    const int stacks = 30;

    for (int i = 0; i < stacks; ++i) {
        float lat0 = M_PI * (-0.5 + (float)i / stacks);
        float lat1 = M_PI * (-0.5 + (float)(i + 1) / stacks);
        float z0 = sin(lat0), zr0 = cos(lat0);
        float z1 = sin(lat1), zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; ++j) {
            float lng = 2 * M_PI * (float)(j) / slices;
            float x = cos(lng), y = sin(lng);

            glNormal3f(x * zr1, z1, y * zr1);
            glVertex3f(x * zr1 * radius, z1 * radius, y * zr1 * radius);

            glNormal3f(x * zr0, z0, y * zr0);
            glVertex3f(x * zr0 * radius, z0 * radius, y * zr0 * radius);
        }
        glEnd();
    }

    for (int j = 0; j <= slices; ++j) {
        float lng = 2 * M_PI * (float)j / slices;
        float x = cos(lng);
        float y = sin(lng);

        glBegin(GL_LINE_STRIP);
        for (int i = 0; i <= stacks; ++i) {
            float lat = M_PI * (-0.5 + (float)i / stacks);
            float z = sin(lat);
            float r = cos(lat);
            // Swap y <-> z
            glVertex3f(x * r * radius, z * radius, y * r * radius);
        }
        glEnd();
    }
}

void MyOpenGLWidget::renderCylinder()
{
    const float radius = 1.0f;
    const float height = 2.0f;
    const int slices = 30;

    // Draw side lines
    for (int i = 0; i < slices; ++i) {
        float angle = 2 * M_PI * i / slices;
        float x = cos(angle) * radius;
        float y = sin(angle) * radius;

        glBegin(GL_LINES);
        glVertex3f(x, -height / 2, y);  // y -> z
        glVertex3f(x, height / 2, y);
        glEnd();
    }

    // Top circle
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < slices; ++i) {
        float angle = 2 * M_PI * i / slices;
        float x = cos(angle) * radius;
        float y = sin(angle) * radius;
        glVertex3f(x, height / 2, y);
    }
    glEnd();

    // Bottom circle
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < slices; ++i) {
        float angle = 2 * M_PI * i / slices;
        float x = cos(angle) * radius;
        float y = sin(angle) * radius;
        glVertex3f(x, -height / 2, y);
    }
    glEnd();
}





