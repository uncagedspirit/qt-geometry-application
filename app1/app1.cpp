#include "app1.h"
#include "myopenglwidget.h"
#include "namedialog.h"


app1::app1(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.addButton, &QPushButton::clicked, this, &app1::onAddButtonClicked);
}

app1::~app1()
{
}

//void app1::onShapeSelected(const QString& shape)
//{
//    MyOpenGLWidget* glWidget = qobject_cast<MyOpenGLWidget*>(ui.openGLWidget);
//    if (glWidget)
//        glWidget->addShape(shape);
//}

void app1::onAddButtonClicked()
{
    QString shapeType = ui.comboBox->currentText();

    NameDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString shapeName = dialog.getShapeName();
        if (shapeName.isEmpty()) return;

        if (ui.listWidget->findItems(shapeName, Qt::MatchExactly).count() > 0) {
            //QMessageBox::warning(this, "Duplicate", "Shape name already exists.");
            return;
        }

        MyOpenGLWidget* glWidget = qobject_cast<MyOpenGLWidget*>(ui.openGLWidget);
        if (glWidget)
            glWidget->addShape(shapeName, shapeType);

        ui.listWidget->addItem(shapeName);
    }
}