#include "control_usuario.h"
#include "ui_control_usuario.h"

///         CONSTRUCTOR          ///
Control_Usuario::Control_Usuario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Control_Usuario)
{
    ///ASIGNACION DE VALORES
    ui->setupUi(this);


    ///DECLARACION DE OBJETOS
    deskWidget = new QDesktopWidget;
    go2Main = new QPushButton(QString("MAINWINDOW"),this);

    ///ASIGNACION DE VALORES
    desk_width = deskWidget->width();   desk_height = deskWidget->height();
    go2Main->setGeometry(100,100,100,70);

    ///CONEXION DE SIGNAL & SLOT
    connect(go2Main,&QPushButton::clicked,this,&Control_Usuario::showMainWindow);
}


///     DESTRUCTOR       ///
Control_Usuario::~Control_Usuario()
{
    delete go2Main;
    delete gameWindow;
    delete deskWidget;
    delete ui;
}


///     FUNCION INICIAR JUEGO       ///
void Control_Usuario::showMainWindow()
{
    ///DECLARACION DE OBJETO
    gameWindow = new MainWindow(this);

    ///ASIGNACION DE VALORES
    gameWindow->setDeskProperty(desk_width,desk_height);
    gameWindow->show();
    gameWindow->addObjetoGrafico(":/personajes/imagenes/bullet.png",250,300,100,100);
    this->hide();
}
