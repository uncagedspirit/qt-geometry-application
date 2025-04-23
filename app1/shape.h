#pragma once
#include <QString>

class Shape {
public:
    QString name;
    float posX = 0.0f, posY = 0.0f;

    Shape(const QString& name, float x = 0.0f, float y = 0.0f)
        : name(name), posX(x), posY(y) {
    }

    virtual void render() const = 0;
    virtual QString type() const = 0;
    virtual ~Shape() {}
};
