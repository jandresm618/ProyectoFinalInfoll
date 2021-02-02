#include "mainwindow.h"
#include "ui_mainwindow.h"


///         CONSTRUCTOR         ///
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
        ///SE ASIGNA UN PADRE A LA INTERFAZ GRAFICA
    ui->setupUi(this);

        ///SE CREAN LOS OBJETOS EN MEMORIA DINAMICA
    instanceItems();

        ///VISUALIZACION Y ESCENA
    view->setScene(scene);
    //view->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));

        ///MAXIMIZAR VENTANA
    this->showMaximized();
    game_time = 0;

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
    delete serial_timer;
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
    canShot(10);
    life_bar->setValue(scene->getHurt());
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


///     FUNCION SET PROPIEDADES ESCRITORIO      ///
void MainWindow::setDeskProperty(int w, int h)
{
    ///ASIGNACION DE VALORES
   desk_widht = w;
   desk_height = h;   
   view->setGeometry(0,0,w,h);
   scene->setWindowProperty(w,h);
}

///         FUNCION QUE CREA OBJETOS EN MEMORIA DINAMICA         ///
void MainWindow::instanceItems()
{
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

    label1 = new QLabel;

    display_time = new QLCDNumber;
    life_bar = new QProgressBar;


    serial_timer = new QTimer;
    seconds = new QTimer;
}


///         AÑADE OBJETOS A ESCENA CON SUS RESPECTIVAS PROPIEDADES         ///
void MainWindow::addItems2Scene(int opc)
{
    QColor bg_color(255, 0, 0, 0);
    QPalette p(label1->palette());
    QPalette p1 = palette();
    p1.setColor(QPalette::Highlight, Qt::red);
    switch (opc) {
        case 1:

            label1->setGeometry((desk_widht/2)-150,desk_height/10,100,50);
            label1->setStyleSheet("border-image:url(:/personajes/imagenes/SCORE.png);");
            p.setColor(QPalette::Background, bg_color);
            label1->setPalette(p);
                ///BOTONES
            //boton->setGeometry(100,50,100,80);
            boton2->setGeometry(100,150,100,80);
            boton2->setStyleSheet("border-image:url(:/personajes/imagenes/Bala2.png);");
            boton2->setPalette(p);
            boton3->setGeometry(200,150,100,80);
            boton3->setStyleSheet("border-image:url(:/personajes/imagenes/Bala2.png);");
            boton3->setPalette(p);
            boton4->setGeometry(300,150,100,80);
            boton4->setStyleSheet("border-image:url(:/personajes/imagenes/Bala2.png);");
            boton4->setPalette(p);

            //boton5->setGeometry(600,300,100,80);

                    ///CASO DE PRUEBA
            /// scene->addWidget(boton);
            scene->addWidget(boton2);
            scene->addWidget(boton3);
            scene->addWidget(boton4);
            //scene->addWidget(boton5);
            scene->addWidget(display_time);
            scene->addWidget(life_bar);
            scene->addWidget(label1);

            display_time->setGeometry(desk_widht/2,desk_height/10,100,50);
            display_time->setPalette(p);
            life_bar->setGeometry(200,80,150,40);
            //life_bar->setPalette(p);
            life_bar->setRange(0,100);
            life_bar->setValue(scene->getHurt());
            life_bar->setPalette(p1);
            break;


        default:
            break;
    }
}

///         FUNCION QUE CONECTA SIGNALS Y SLOTS         ///
void MainWindow::connectItems()
{
    ///CONEXION DE SIGNALS & SLOTS
    connect(boton,&QPushButton::clicked,this,&MainWindow::comeBack);
    connect(boton2,&QPushButton::clicked,this,&MainWindow::addObjetoMovil1);
    connect(boton3,&QPushButton::clicked,this,&MainWindow::addObjetoMovil2);
    connect(boton4,&QPushButton::clicked,this,&MainWindow::addObjetoMovil3);
    //connect(boton5,&QPushButton::clicked,this,&MainWindow::imagen2);
    connect(seconds,&QTimer::timeout,this,&MainWindow::secondsPlusPlus);
    connect(serial_timer,&QTimer::timeout,this,&MainWindow::serialRead);
}

///         FUNCION QUE DISPONE LOS OBJETOS DEL JUEGO         ///
void MainWindow::setGameWidgets()
{
    int opc = 1;
    addItems2Scene(opc);
    connectItems();

    addObjetoGrafico(":/personajes/imagenes/senor1.png",desk_widht/8,2*desk_height/4,200,300);
    setPosSir(desk_widht/8,2*desk_height/4);

    display_time->display("0:0");

        ///INICIALIZAR PARAMETROS
    serialInit();
    serial_timer->start(fs_time);
    seconds->start(1000);
}


///         OPCION ARCADE         ///
void MainWindow::setArcade()
{
    arcade = true;
    setGameWidgets();
}

///         OPCION MULTIJUGADOR         ///
void MainWindow::setMultiplayer()
{
    arcade = false;
    setGameWidgets();
}

///         AÑADE OBJETOS SIN MOVIMIENTO         ///
void MainWindow::addObjetoGrafico(QString ruta, int x, int y, int w, int h)
{
    ///DECLARACION DE OBJETOS
    scene->addObjetoGrafico(ruta,x,y,w,h);
}

///         AÑADE OBJETOS CON MOVIMIENTO         ///
void MainWindow::addObjetoMovil(QString ruta, int xo, int yo, int xf, int yf, int w, int h, int _move)
{
    scene->addObjetoMovil(ruta,xo,yo,xf,yf,w,h,_move);
}








///         EVENTOS DE TECLADO         ///
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space ){
        //qDebug()<<"\nAÑADIENDO OBJETO\n";
        if(!arcade){
            if(scene->getHurt() > 0){
                addObjetoMovil(QString(":/personajes/imagenes/pollo2.png"),
                               desk_widht,300,x_sir,y_sir,100,100,move2);
            }
        }
    }
    else if(event->key() == Qt::Key_A){
        //qDebug()<<"A Pressed";
        move1 = 1;
    }
    else if(event->key() == Qt::Key_S){
        //qDebug()<<"S Pressed";
        move1 = 2;
    }
    else if(event->key() == Qt::Key_W){
        //qDebug()<<"W Pressed";
        move1 = 3;
    }
    else if(event->key() == Qt::Key_D){
        //qDebug()<<"D Pressed";
        move1 = 3;
    }
    else if(event->key() == Qt::Key_J){
        //qDebug()<<"J Pressed";
        move2 = 1;
    }
    else if(event->key() == Qt::Key_K){
        //qDebug()<<"K Pressed";
        move2 = 2;
    }
    else if(event->key() == Qt::Key_L){
        //qDebug()<<"L Pressed";
        move2 = 3;
    }
    else if(event->key() == Qt::Key_I){
        //qDebug()<<"I Pressed";
    }
}

///         EVENTOS DE BOTONES DE MOUSE         ///
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QMainWindow::mousePressEvent(event);
    if(enable2Shot){
        enable2Shot = false;
        if (move1 == 1 && ammu1 > 0)addObjetoMovil(QString(":/personajes/imagenes/Bala2.png"),
                       x_sir,y_sir,event->x(),event->y(),50,50,move1);
        else if (move1 == 2 && ammu2 > 0)addObjetoMovil(QString(":/personajes/imagenes/Bala2.png"),
                       x_sir,y_sir,event->x(),event->y(),50,50,move1);
        else if (move1 == 3 && ammu3 > 0)addObjetoMovil(QString(":/personajes/imagenes/Bala2.png"),
                       x_sir,y_sir,event->x(),event->y(),50,50,move1);
    }
}

int MainWindow::sec2min(int _seconds, bool out)
{
    int min = _seconds/60;
    float sec = _seconds%60;
        ///Salida en minutos
    if(out) return min;
    else return sec;
}

bool MainWindow::canShot(int limit)
{
    if(!enable2Shot){
        cont_aux++;
        if(cont_aux >= limit) {enable2Shot = true; cont_aux = 0;}
    }
    return enable2Shot;
}


                            /////// FUNCIONES DE PRUEBA ////////////////

///     FUNCIONES DE PRUEBA     ///
void MainWindow::addObjetoMovil1()
{
    move1 = 1;
    ///DECLARACION DE OBJETOS
    QString ruta = ":/personajes/imagenes/GIFT.png";int w=80; int h=80;
    int xf = 900,yf = 500;
    scene->addObjetoMovil(ruta,xf,yf,x_sir,y_sir,w,h,move1);
}

void MainWindow::addObjetoMovil2()
{
    move1 = 2;
    ///DECLARACION DE OBJETOS
    QString ruta = ":/personajes/imagenes/GIFT.png"; int w=80; int h=80;
    int xf = 900,yf = 500;
    scene->addObjetoMovil(ruta,xf,yf,x_sir,y_sir,w,h,move1);
}

void MainWindow::addObjetoMovil3()
{
    move1 = 3;
    ///DECLARACION DE OBJETOS
    QString ruta = ":/personajes/imagenes/GIFT.png"; int w=80; int h=80;
    int xf = 900,yf = 500;
    scene->addObjetoMovil(ruta,xf,yf,x_sir,y_sir,w,h,move1);
}

void MainWindow::secondsPlusPlus()
{
    game_time += 1;
    QString timing = QString(to_string(sec2min(game_time,true)).data())+":"+QString(to_string(sec2min(game_time,false)).data());
    display_time->display(timing);
}
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


void MainWindow::moveObject()
{
    ///ASIGNACION DE VALORES
    scene->doSome();
}
