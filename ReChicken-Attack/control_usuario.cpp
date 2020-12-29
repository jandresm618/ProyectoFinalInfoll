#include "control_usuario.h"
#include "ui_control_usuario.h"

Control_Usuario::Control_Usuario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Control_Usuario)
{
    ui->setupUi(this);

    go2Main = new QPushButton(QString("MAINWINDOW"),this);
    go2Main->setGeometry(100,100,100,70);

    connect(go2Main,&QPushButton::clicked,this,&Control_Usuario::showMainWindow);
}

Control_Usuario::~Control_Usuario()
{
    delete go2Main;
    delete gameWindow;
    delete ui;
}

void Control_Usuario::showMainWindow()
{
    gameWindow = new MainWindow(this);
    gameWindow->show();
    this->hide();
}
