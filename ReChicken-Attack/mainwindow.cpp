#include "mainwindow.h"
#include "ui_mainwindow.h"


///         CONSTRUCTOR         ///
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ///ASIGNACION DE VALORES
    ui->setupUi(this);



    ///DECLARACION DE OBJETOS
        ///VISUALIZACION Y ESCENA
    view = new QGraphicsView(this);
    scene = new Escena_Juego();
        ///BOTONES
    boton = new QPushButton(QString("COME BACK"));
    boton2 = new QPushButton(QString("ADD 1"));
    boton3 = new QPushButton(QString("ADD 2"));
    boton4 = new QPushButton(QString("ADD 3"));
    //boton5 = new QPushButton(QString("FONDO NEGRO"));

    time = new QTimer;

    ///ASIGNACION DE VALORES
        ///VISUALIZACION Y ESCENA
    view->setScene(scene);
    //view->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
    this->showMaximized();
        ///BOTONES
    boton->setGeometry(100,50,100,80);
    boton2->setGeometry(100,150,100,80);
    boton3->setGeometry(300,150,100,80);
    boton4->setGeometry(600,150,100,80);
    //boton5->setGeometry(600,300,100,80);
    scene->addWidget(boton);
    scene->addWidget(boton2);
    scene->addWidget(boton3);
    scene->addWidget(boton4);
    //scene->addWidget(boton5);

    ///CONEXION DE SIGNALS & SLOTS
    connect(boton,&QPushButton::clicked,this,&MainWindow::comeBack);
    connect(boton2,&QPushButton::clicked,this,&MainWindow::addObjetoMovil1);
    connect(boton3,&QPushButton::clicked,this,&MainWindow::addObjetoMovil2);
    connect(boton4,&QPushButton::clicked,this,&MainWindow::addObjetoMovil3);
    //connect(boton5,&QPushButton::clicked,this,&MainWindow::imagen2);
    connect(time,&QTimer::timeout,this,&MainWindow::serialRead);



    serialInit();
    time->start(500);
}

///         DESTRUCTOR         ///
MainWindow::~MainWindow()
{
    ///ELIMINACION DE MEMORIA
    delete boton;
    delete boton2;
    delete boton3;
    delete boton4;
    delete boton5;
    delete time;
    delete view;
    delete scene;
    delete ui;
}

/// INICIALIZACION DEL PUERTO SERIE     ///
void MainWindow::serialInit()
{
    serial.setPortName("/dev/ttyUSB0"); //Poner el nombre del puerto

    qDebug()<<"Serial init"<<"++++++++++++++++++++";

    if(serial.open(QIODevice::ReadWrite)){
        //Ahora el puerto seria está abierto
        if(!serial.setBaudRate(QSerialPort::Baud9600)) //Configurar la tasa de baudios
            qDebug()<<serial.errorString();

        if(!serial.setDataBits(QSerialPort::Data8))
            qDebug()<<serial.errorString();

        if(!serial.setParity(QSerialPort::NoParity))
            qDebug()<<serial.errorString();

        if(!serial.setStopBits(QSerialPort::OneStop))
            qDebug()<<serial.errorString();

        if(!serial.setFlowControl(QSerialPort::NoFlowControl))
            qDebug()<<serial.errorString();

        qDebug()<<"Serial ok";
        serial_available = true;
    }else{        
        qDebug()<<"Serial ttyACM0 not opened. Error: "<<serial.errorString();
    }

}

///      LECTURA DEL PUERTO SERIE       ///
void MainWindow::serialRead(){
    scene->deleteFromScene();
    if(serial_available){
        serial.read(&serial_char,1); //Leer toda la línea que envía arduino
        if(serial_char!=0){
            cout<<serial_char<<"************+"<<endl;
        }
    }
}


///     FUNCION RETORNO AL MENU     ///
void MainWindow::comeBack()
{
    ///ASIGNACION DE VALORES
    this->hide();
    this->parentWidget()->show();

}

void MainWindow::moveObject()
{
    ///ASIGNACION DE VALORES
    scene->doSome();
}

///     FUNCION SET PROPIEDADES ESCRITORIO      ///
void MainWindow::setDeskProperty(int w, int h)
{
    ///ASIGNACION DE VALORES
   desk_widht = w;
   desk_height = h;   
   view->setGeometry(0,0,w,h);
   scene->setWindowProperty(w,h);
}

void MainWindow::addObjetoGrafico(QString ruta, int x, int y, int w, int h)
{
    ///DECLARACION DE OBJETOS
    scene->addObjetoGrafico(ruta,x,y,w,h);
}

void MainWindow::addObjetoMovil(QString ruta, int xo, int yo, int xf, int yf, int w, int h, int _move)
{
    scene->addObjetoMovil(ruta,xo,yo,xf,yf,w,h,_move);
}

void MainWindow::addObjetoMovil1()
{
    move = 1;
    ///DECLARACION DE OBJETOS
    QString ruta = ":/personajes/imagenes/GIFT.png";int w=80; int h=80;
    int xf = 900,yf = 500;
    scene->addObjetoMovil(ruta,xf,yf,x_sir,y_sir,w,h,move);
}

void MainWindow::addObjetoMovil2()
{
    move = 2;
    ///DECLARACION DE OBJETOS
    QString ruta = ":/personajes/imagenes/GIFT.png"; int w=80; int h=80;
    int xf = 900,yf = 500;
    scene->addObjetoMovil(ruta,xf,yf,x_sir,y_sir,w,h,move);
}

void MainWindow::addObjetoMovil3()
{
    move = 3;
    ///DECLARACION DE OBJETOS
    QString ruta = ":/personajes/imagenes/GIFT.png"; int w=80; int h=80;
    int xf = 900,yf = 500;
    scene->addObjetoMovil(ruta,xf,yf,x_sir,y_sir,w,h,move);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space ){
        qDebug()<<"Space Pressed";
        if(!arcade){
            addObjetoMovil(QString(":/personajes/imagenes/pollo2.png"),
                           desk_widht,300,x_sir,y_sir,100,100,move);
        }
    }
    else if(event->key() == Qt::Key_A){
        qDebug()<<"A Pressed";
        move = 1;
    }
    else if(event->key() == Qt::Key_S){
        qDebug()<<"S Pressed";
        move = 2;
    }
    else if(event->key() == Qt::Key_W){
        qDebug()<<"W Pressed";
        move = 3;
    }
    else if(event->key() == Qt::Key_D){
        qDebug()<<"D Pressed";
        move = 3;
    }
    else if(event->key() == Qt::Key_J){
        qDebug()<<"J Pressed";
        move = 1;
    }
    else if(event->key() == Qt::Key_K){
        qDebug()<<"K Pressed";
        move = 2;
    }
    else if(event->key() == Qt::Key_L){
        qDebug()<<"L Pressed";
        move = 3;
    }
    else if(event->key() == Qt::Key_I){
        qDebug()<<"I Pressed";
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QMainWindow::mousePressEvent(event);
    qDebug()<<"x "<<event->x()<<" y "<<event->y();
    addObjetoMovil(QString(":/personajes/imagenes/Bala2.png"),
                   x_sir,y_sir,event->x(),event->y(),50,50,move);
}


///     FUNCIONES DE PRUEBA     ///
void MainWindow::add()
{
    ///DECLARACION DE OBJETOS
    QString ruta = ":/personajes/imagenes/GIFT.png"; int x=0; int y=100; int w=80; int h=80;
    scene->addObjetoGrafico(ruta,x,y,w,h);
}

void MainWindow::imagen1()
{
    view->setBackgroundBrush(QImage(":/personajes/imagenes/fondo.png"));
}

void MainWindow::imagen2()
{
    if (img) {view->setBackgroundBrush(QImage(":/personajes/imagenes/fondo.png")); img = false;}
    else {view->setBackgroundBrush(QImage(":/personajes/imagenes/GIFT.png")); img = true;}
}

void MainWindow::setPosSir(int x, int y)
{
    x_sir = x; y_sir = y;
}


