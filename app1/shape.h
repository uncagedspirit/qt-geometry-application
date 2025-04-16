#ifndef SHAPE_H
#define SHAPE_H

#include <QString>

struct Shape {
    QString name;
    QString type;
    float posX;
    float posY;

    Shape(const QString& name, const QString& type, float x = 0.0f, float y = 0.0f)
        : name(name), type(type), posX(x), posY(y) {
    }
};


#endif // SHAPE_H
#pragma once
