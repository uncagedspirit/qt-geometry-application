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
    void onAddButtonClicked();  
    void onDeleteButtonClicked();


private:
    Ui::app1Class ui;
};