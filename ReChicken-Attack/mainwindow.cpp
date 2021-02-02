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
    srand(time(NULL));

}

///         DESTRUCTOR         ///
MainWindow::~MainWindow()
{
    ///ELIMINACION DE MEMORIA
    /// BOTONES
    delete boton;
    delete boton2 ;
    delete boton3 ;
    delete boton4 ;
    delete boton5 ;
        /// LABELS
    delete label1;
    delete label2;
        /// LCD DISPLAYS
    delete display_time;
    delete display_ammo1;
    delete display_ammo2;
    delete display_ammo3;
    delete display_score ;
        /// BARRA DE SANGRE
    delete life_bar;
        /// TIMERS
    delete serial_timer;
    delete enemy_timer;
    delete seconds;
        ///ESCENARIO
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
    int blood;
    canShot(10);
    scene->deleteFromScene(); blood =scene->getHurt();
    life_bar->setValue(blood);
    if(blood == 0) emit end();
    display_score->display(scene->getScore()*int(increment*game_time));


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
        /// ESCENARIO
    view = new QGraphicsView(this);
    scene = new Escena_Juego();
        /// BOTONES
    boton = new QPushButton();
    boton2 = new QPushButton();
    boton3 = new QPushButton();
    boton4 = new QPushButton();
    boton5 = new QPushButton();
        /// LABELS
    label1 = new QLabel;
    label2 = new QLabel;
        /// LCD DISPLAYS
    display_time = new QLCDNumber;
    display_ammo1 = new QLCDNumber;
    display_ammo2 = new QLCDNumber;
    display_ammo3 = new QLCDNumber;
    display_score = new QLCDNumber;
        /// BARRA DE SANGRE
    life_bar = new QProgressBar;
        /// TIMERS
    serial_timer = new QTimer;
    enemy_timer = new QTimer;
    seconds = new QTimer;
}

void MainWindow::hideItems()
{
        /// BOTONES
    boton->hide();
    boton2->hide();
    boton3->hide();
    boton4->hide();
    boton5->hide();
        /// LABELS
    label1->hide();
    label2->hide();
        /// LCD DISPLAYS
    display_time->hide();
    display_ammo1->hide();
    display_ammo2->hide();
    display_ammo3->hide();
    display_score->hide();
        /// BARRA DE SANGRE
    life_bar->hide();
}


///         AÑADE OBJETOS A ESCENA CON SUS RESPECTIVAS PROPIEDADES         ///
void MainWindow::addItems2Scene(int opc)
{
    QColor bg_color(255, 0, 0, 0);
    QPalette p(label1->palette());
    p.setColor(QPalette::Background, bg_color);
    QPalette p1 = palette();
    p1.setColor(QPalette::Highlight, Qt::red);
    switch (opc) {
        case 1:
            addObjetoGrafico(":/personajes/imagenes/senor1.png",desk_widht/8,2*desk_height/4,200,300);
            setPosSir(desk_widht/8,2*desk_height/4);
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
            display_time->display("0:0");

            life_bar->setGeometry(200,80,150,40);
            //life_bar->setPalette(p);
            life_bar->setRange(0,100);
            life_bar->setValue(scene->getHurt());
            life_bar->setPalette(p1);
            break;
        case 2:
                ///PUESTA EN ESCENA DEL PERSONAJE
            addObjetoGrafico(":/personajes/imagenes/senor1.png",desk_widht/8,2*desk_height/4,200,300);
            setPosSir(desk_widht/8,2*desk_height/4);
                ///LABELS
            label1->setGeometry(60,80,100,50);
            label1->setStyleSheet("border-image:url(:/personajes/imagenes/LIFE.png);");
            label1->setPalette(p);
            life_bar->setGeometry(170,80,150,50);
            life_bar->setPalette(p1);
            life_bar->setRange(0,100);

            label2->setGeometry((7*desk_widht/8)-100,desk_height/10,100,50);
            label2->setStyleSheet("border-image:url(:/personajes/imagenes/SCORE.png);");
            label2->setPalette(p);
            display_score->setGeometry((7*desk_widht/8),desk_height/10,100,60);
            display_score->setPalette(p);
            display_score->display(scene->getScore());

                ///BOTONES
            //boton->setGeometry(100,50,100,80);
            boton2->setGeometry(50,150,80,60);
            boton2->setStyleSheet("border-image:url(:/personajes/imagenes/Bala2.png);");
            boton2->setPalette(p);
            boton3->setGeometry(50,210,80,60);
            boton3->setStyleSheet("border-image:url(:/personajes/imagenes/Bala2.png);");
            boton3->setPalette(p);
            boton4->setGeometry(50,270,80,60);
            boton4->setStyleSheet("border-image:url(:/personajes/imagenes/Bala2.png);");
            boton4->setPalette(p);
            //boton5->setGeometry(600,300,100,80);
            display_ammo1->setGeometry(130,150,80,60);
            display_ammo1->setPalette(p);
            display_ammo1->display(ammu1);
            display_ammo2->setGeometry(130,210,80,60);
            display_ammo2->setPalette(p);
            display_ammo2->display(ammu2);
            display_ammo3->setGeometry(130,270,80,60);
            display_ammo3->setPalette(p);
            display_ammo3->display(ammu3);


            display_time->setGeometry((desk_widht/2)-60,20,100,50);
            display_time->setPalette(p);
            display_time->display("0:0");



                    ///AÑADIR OBJETOS A ESCENA
            scene->addWidget(boton2);
            scene->addWidget(boton3);
            scene->addWidget(boton4);
            scene->addWidget(display_ammo1);
            scene->addWidget(display_ammo2);
            scene->addWidget(display_ammo3);
            scene->addWidget(display_time);
            scene->addWidget(life_bar);
            scene->addWidget(label1);
            scene->addWidget(label2);
            scene->addWidget(display_score);



            life_bar->setValue(scene->getHurt());
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
    connect(this,&MainWindow::end,this,&MainWindow::endOfGame);

    connect(enemy_timer,&QTimer::timeout,this,&MainWindow::addEnemy);
    connect(seconds,&QTimer::timeout,this,&MainWindow::secondsPlusPlus);    
    connect(serial_timer,&QTimer::timeout,this,&MainWindow::serialRead);
}

///         FUNCION QUE DISPONE LOS OBJETOS DEL JUEGO         ///
void MainWindow::loadGame()
{
    int opc = 2;
    addItems2Scene(opc);
    connectItems();   

    QMessageBox::information(this,"TURNO 1",  "PLAYER 1");

        ///INICIALIZAR PARAMETROS
    serialInit();
    serial_timer->start(fs_time);
    seconds->start(time_seconds);
    if(arcade) enemy_timer->start(time_enemys);
}


///         OPCION ARCADE         ///
void MainWindow::setArcade()
{
    arcade = true; player = 1; game_time = 0;
    loadGame();
}

///         OPCION MULTIJUGADOR         ///
void MainWindow::setMultiplayer()
{
    arcade = false; player = 1; game_time = 0;
    loadGame();
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
    else if(event->key() == Qt::Key_P){
        if(paused){
            this->start();
        }
        else{
            this->pause();
        }
    }
}

///         EVENTOS DE BOTONES DE MOUSE         ///
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QMainWindow::mousePressEvent(event);
    if(enable2Shot){
        enable2Shot = false;
        if (move1 == 1 && ammu1 > 0){
            addObjetoMovil(QString(":/personajes/imagenes/Bala2.png"),
                           x_sir,y_sir,event->x(),event->y(),50,50,move1);
            ammu1--;
            display_ammo1->display(ammu1);
        }
        else if (move1 == 2 && ammu2 > 0){
            addObjetoMovil(QString(":/personajes/imagenes/Bala2.png"),
                           x_sir,y_sir,event->x(),event->y(),50,50,move1);
            ammu2--;
            display_ammo2->display(ammu2);
        }
        else if (move1 == 3 && ammu3 > 0){
            addObjetoMovil(QString(":/personajes/imagenes/Bala2.png"),
                           x_sir,y_sir,event->x(),event->y(),50,50,move1);
            ammu3--;
            display_ammo3->display(ammu3);
        }
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

void MainWindow::endOfGame()
{
    /*
    QMessageBox msgBox;
    msgBox.setWindowTitle("GAME ENDED");
    msgBox.setText("THE WINNER IS:");
    if(score_2>score_3  || score_4>game->getScore()){
        if(score_2>score_4)msgBox.setInformativeText("PLAYER 1"+QString::number(score_2));
        else msgBox.setInformativeText("PLAYER 3"+QString::number(score_4));
    }
    else {
        if(score_3>game->getScore())msgBox.setInformativeText("PLAYER 2"+QString::number(score_3));
        else msgBox.setInformativeText("PLAYER 4"+QString::number(game->getScore()));
    }

    QPushButton *exitButton = msgBox.addButton(tr("MENU"), QMessageBox::ActionRole);
    QPushButton *abortButton = msgBox.addButton(tr("RESTART"),QMessageBox::ActionRole);


    msgBox.exec();

    if (msgBox.clickedButton() == exitButton) {
        // connect
        this->parentWidget()->show();
        this->close();
        this->deleteLater();
    } else if (msgBox.clickedButton() == abortButton) {
        // abort
        restart();
    }*/
    serial_timer->stop(); enemy_timer->stop(); seconds->stop();
    int score = scene->getScore()*int(increment*game_time);
    scene->pause();
    QMessageBox::information(this,"SCORE",  QString().number(score));
    if(arcade || player == 2){
        ///FIN  DE JUEGO
        scene->restart();
        comeBack();
    }
    else{
        ///REINICIO DE VALORES DE JUEGO
        player = 2;
        this->restart();
        QMessageBox::information(this,"TURNO 2",  "PLAYER 2");
        this->start();
    }
}

void MainWindow::setGameValues(int _blood, int _score, int _player, int _a1, int _a2, int _a3,bool _arcade)
{
    scene->setBlood(_blood);
    scene->setScore(_score);
    player = _player;
    ammu1 = _a1;
    ammu2 = _a2;
    ammu3 = _a3;
    arcade = _arcade;
}

void MainWindow::addEnemy()
{
    move2=1+rand()%(4-1);
    addObjetoMovil(QString(":/personajes/imagenes/pollo2.png"),
                   desk_widht,300,x_sir,y_sir,100,100,move2);
}

void MainWindow::pause()
{
    paused = true;
    seconds->stop();
    enemy_timer->stop();
    serial_timer->stop();
    scene->pause();
}

void MainWindow::start()
{
    paused = false;
    serial_timer->start(fs_time);
    seconds->start(time_seconds);
    if(arcade) enemy_timer->start(time_enemys);
    scene->start();
}

void MainWindow::restart()
{
    scene->restart();
    game_time = 0;

}



                            /////// FUNCIONES DE PRUEBA ////////////////

///     FUNCIONES DE PRUEBA     ///
void MainWindow::addObjetoMovil1()
{
    move1 = 1;
    ///DECLARACION DE OBJETOS
    //QString ruta = ":/personajes/imagenes/GIFT.png";int w=80; int h=80;
    //int xf = 900,yf = 500;
    //scene->addObjetoMovil(ruta,xf,yf,x_sir,y_sir,w,h,move1);
}

void MainWindow::addObjetoMovil2()
{
    move1 = 2;
    ///DECLARACION DE OBJETOS
    //QString ruta = ":/personajes/imagenes/GIFT.png"; int w=80; int h=80;
    //int xf = 900,yf = 500;
    //scene->addObjetoMovil(ruta,xf,yf,x_sir,y_sir,w,h,move1);
}

void MainWindow::addObjetoMovil3()
{
    move1 = 3;
    ///DECLARACION DE OBJETOS
    //QString ruta = ":/personajes/imagenes/GIFT.png"; int w=80; int h=80;
    //int xf = 900,yf = 500;
    //scene->addObjetoMovil(ruta,xf,yf,x_sir,y_sir,w,h,move1);
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
