#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
}

void MyOpenGLWidget::addShape(const QString& name, const QString& type)
{
    shapesToRender.append(Shape(name, type));
    update();
}

void MyOpenGLWidget::removeShape(const QString& name)
{
    for (int i = 0; i < shapesToRender.size(); ++i) {
        if (shapesToRender[i].name == name) {
            shapesToRender.removeAt(i);
            update();
            break;
        }
    }
}




void MyOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
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

    for (const Shape& shape : shapesToRender) {
        glPushMatrix();
        glTranslatef(shape.posX, shape.posY, 0.0f);

        if (shape.type == "Sphere")
            renderSphere();
        else if (shape.type == "Cylinder")
            renderCylinder();

        glPopMatrix();
    }

}

void MyOpenGLWidget::renderSphere()
{
    const float radius = 1.0f;
    const int slices = 30;
    const int stacks = 30;

    for (int i = 0; i <= stacks; ++i) {
        float lat = M_PI * (-0.5 + (float)i / stacks);
        float z = sin(lat);
        float r = cos(lat);

        glBegin(GL_LINE_LOOP);
        for (int j = 0; j <= slices; ++j) {
            float lng = 2 * M_PI * (float)j / slices;
            float x = cos(lng);
            float y = sin(lng);
            // Swap y <-> z
            glVertex3f(x * r * radius, z * radius, y * r * radius);
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





