#pragma once
#include "shape.h"
#include <QtMath>
#include <QOpenGLFunctions>

class Cone : public Shape, protected QOpenGLFunctions {
public:
    Cone(const QString& name, float x = 0.0f, float y = 0.0f)
        : Shape(name, x, y) {
    }

    QString type() const override { return "Cone"; }

    void render() const override {
        const int slices = 30;
        const float radius = 1.0f;
        const float height = 2.0f;

        glBegin(GL_LINE_LOOP);  // Base
        for (int i = 0; i < slices; ++i) {
            float angle = 2 * M_PI * i / slices;
            float x = cos(angle) * radius;
            float z = sin(angle) * radius;
            glVertex3f(x, 0, z);
        }
        glEnd();

        // Sides
        for (int i = 0; i < slices; ++i) {
            float angle = 2 * M_PI * i / slices;
            float x = cos(angle) * radius;
            float z = sin(angle) * radius;
            glBegin(GL_LINES);
            glVertex3f(x, 0, z);
            glVertex3f(0, height, 0);
            glEnd();
        }
    }
};
#pragma once
