#pragma once

#include <QDialog>
#include "ui_namedialog.h"

class NameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NameDialog(QWidget* parent = nullptr);
    QString getShapeName() const;

private:
    Ui::NameDialog ui;
};