#pragma once
#include "shape.h"
#include <QtMath>
#include <QOpenGLFunctions>

class Cylinder : public Shape, protected QOpenGLFunctions {
public:
    Cylinder(const QString& name, float x = 0.0f, float y = 0.0f)
        : Shape(name, x, y) {
    }

    QString type() const override { return "Cylinder"; }

    void render() const override {
        const float radius = 1.0f;
        const float height = 2.0f;
        const int slices = 30;

        for (int i = 0; i < slices; ++i) {
            float angle = 2 * M_PI * i / slices;
            float x = cos(angle) * radius;
            float y = sin(angle) * radius;

            glBegin(GL_LINES);
            glVertex3f(x, -height / 2, y);
            glVertex3f(x, height / 2, y);
            glEnd();
        }

        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < slices; ++i) {
            float angle = 2 * M_PI * i / slices;
            float x = cos(angle) * radius;
            float y = sin(angle) * radius;
            glVertex3f(x, height / 2, y);
        }
        glEnd();

        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < slices; ++i) {
            float angle = 2 * M_PI * i / slices;
            float x = cos(angle) * radius;
            float y = sin(angle) * radius;
            glVertex3f(x, -height / 2, y);
        }
        glEnd();
    }
};
#pragma once
