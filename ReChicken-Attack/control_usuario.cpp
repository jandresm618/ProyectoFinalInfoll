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
    go2Main = new QPushButton(QString("MainWindow"),this);


    ///ASIGNACION DE VALORES
    desk_width = deskWidget->width();   desk_height = deskWidget->height();
    setGeometry(0,0,desk_width,desk_height);

    go2Main->setGeometry(2*desk_width/3,2*desk_height/3,100,100);
    go2Main->setStyleSheet("border-image: url(:/imagenes/LOAD GAME.png);");


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
    if(firstTime){
        ///DECLARACION DE OBJETO
        gameWindow = new MainWindow(this);

        ///ASIGNACION DE VALORES
        gameWindow->setDeskProperty(desk_width,desk_height);
        gameWindow->addObjetoGrafico(":/personajes/imagenes/senor1.png",desk_width/8,2*desk_height/4,200,300);
        gameWindow->setPosSir(desk_width/8,2*desk_height/4);
        firstTime = false;
    }

    gameWindow->show();
    this->hide();
}
