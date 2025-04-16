#include "namedialog.h"

NameDialog::NameDialog(QWidget* parent)
    : QDialog(parent)
{
    ui.setupUi(this);
}

QString NameDialog::getShapeName() const
{
    return ui.nameLineEdit->text();
}