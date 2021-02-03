#include "control_usuario.h"
#include "ui_control_usuario.h"

///         CONSTRUCTOR          ///
Control_Usuario::Control_Usuario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Control_Usuario)
{
    ///ASIGNACION DE VALORES
    ui->setupUi(this);

    crearObjetos();     /// Inicializa los objetos que necesitan memoria dinamica
    setCredentialsWindow(); /// Dispone los botones necesarios para la primera visualizacion
    ///ASIGNACION DE VALORES DE VENTANA
    setGeometry(0,0,desk_width,desk_height);    /// Geometria de la Ventana
}


///     DESTRUCTOR       ///
Control_Usuario::~Control_Usuario()
{
    delete boton1;
    delete boton2;
    delete boton3;
    delete gameWindow;
    delete deskWidget;
    delete ui;
}

void Control_Usuario::crearObjetos()
{
    ///DECLARACION DE OBJETOS
    deskWidget = new QDesktopWidget;
    desk_width = deskWidget->width();   desk_height = deskWidget->height();
    boton1 = new QPushButton(QString("Arcade"),this); boton1->hide();
    boton2 = new QPushButton(this);
    boton3 = new QPushButton(this);
    //label1 = new QLabel(this);
}

void Control_Usuario::setCredentialsWindow()
{
    ///POR AHORA
    boton1->setGeometry(desk_width/3,2*desk_height/3,100,100);
    boton1->setStyleSheet("border-image:url(:/personajes/imagenes/ARCADE.png);");
    boton2->setGeometry(2*desk_width/3,desk_height/3,100,100);
    boton2->setStyleSheet("border-image:url(:/personajes/imagenes/ARCADE.png);");
    boton3->setGeometry(2*desk_width/3,2*desk_height/3,200,100);
    boton3->setStyleSheet("border-image:url(:/personajes/imagenes/MULTIPLAYER.png);");

    //label1->setGeometry(200,100,100,100);
    //label1->setStyleSheet("border-image:url(:/personajes/imagenes/ARCADE.png);");


    ///CONEXION DE SIGNAL & SLOT
    connect(boton1,&QPushButton::clicked,this,&Control_Usuario::showMainWindow);
    connect(boton2,&QPushButton::clicked,this,&Control_Usuario::setArcade);
    connect(boton3,&QPushButton::clicked,this,&Control_Usuario::setMultiplayer);

}

void Control_Usuario::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter ){
        qDebug()<<"Enter Pressed";
    }
}


///     FUNCION INICIAR JUEGO       ///
void Control_Usuario::showMainWindow()
{
    if(firstTime) showNewMainWindow();
    gameWindow->show();
    this->hide();
}

void Control_Usuario::showNewMainWindow()
{
    ///DECLARACION DE OBJETO
    gameWindow = new MainWindow(this);

    ///ASIGNACION DE VALORES
    gameWindow->setDeskProperty(desk_width,desk_height);

    firstTime = false;
}

void Control_Usuario::setArcade()
{
    arcade = true;
    showMainWindow();
    gameWindow->setArcade();
    gameWindow->setDefaultValues();
}

void Control_Usuario::setMultiplayer()
{
    arcade = false;
    showMainWindow();
    gameWindow->setMultiplayer();
    gameWindow->setDefaultValues();
}
