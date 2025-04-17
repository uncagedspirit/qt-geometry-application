#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QString>

#include "shape.h"


class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MyOpenGLWidget(QWidget* parent = nullptr);
    void addShape(const QString& name, const QString& type);
    void removeShape(const QString& name);


protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    QVector<Shape> shapesToRender;

    void renderSphere();
    void renderCylinder();



    QString currentShape;
};