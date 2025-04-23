#pragma once
#include "shape.h"
#include <QtMath>
#include <QOpenGLFunctions>

class Sphere : public Shape, protected QOpenGLFunctions {
public:
    Sphere(const QString& name, float x = 0.0f, float y = 0.0f)
        : Shape(name, x, y) {
    }

    QString type() const override { return "Sphere"; }

    void render() const override {
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
                glVertex3f(x * r * radius, z * radius, y * r * radius);
            }
            glEnd();
        }
    }
};
#pragma once
