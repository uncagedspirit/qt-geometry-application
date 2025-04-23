#pragma once
#include "shape.h"
#include <QOpenGLFunctions>

class Cuboid : public Shape, protected QOpenGLFunctions {
public:
    Cuboid(const QString& name, float x = 0.0f, float y = 0.0f)
        : Shape(name, x, y) {
    }

    QString type() const override { return "Cuboid"; }

    void render() const override {
        float w = 2.0f, h = 1.5f, d = 1.0f;

        static const GLfloat vertices[8][3] = {
            {-w, -h, -d}, {w, -h, -d}, {w, h, -d}, {-w, h, -d},
            {-w, -h, d},  {w, -h, d},  {w, h, d},  {-w, h, d}
        };

        static const int edges[12][2] = {
            {0,1}, {1,2}, {2,3}, {3,0},
            {4,5}, {5,6}, {6,7}, {7,4},
            {0,4}, {1,5}, {2,6}, {3,7}
        };

        glBegin(GL_LINES);
        for (int i = 0; i < 12; ++i) {
            glVertex3fv(vertices[edges[i][0]]);
            glVertex3fv(vertices[edges[i][1]]);
        }
        glEnd();
    }
};
