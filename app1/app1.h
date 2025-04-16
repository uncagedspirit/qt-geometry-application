#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_app1.h"

class app1 : public QMainWindow
{
    Q_OBJECT

public:
    app1(QWidget* parent = nullptr);
    ~app1();

private slots:
    //void onShapeSelected(const QString& shape); // Add this
    void onAddButtonClicked();  // New slot


private:
    Ui::app1Class ui;
};
