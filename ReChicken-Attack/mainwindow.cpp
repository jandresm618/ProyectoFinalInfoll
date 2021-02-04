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

    msgBox = new QMessageBox(this);
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
    timer = new QTimer();
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
            addObjetoGrafico(":/personajes/imagenes/senor1.png",desk_widht/8,2*desk_height/4,200,300,true);
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
                /// IMAGEN DE FONDO PARA LA VENTANA DE MENSAJES
            msgBox->setStyleSheet("border-image:url(:/personajes/imagenes/swamp.png);");
            msgBox->setPalette(p);
            msgBox->setGeometry((desk_widht/2)-100,(2*desk_height/3)-100,300,400);
                ///PUESTA EN ESCENA DEL PERSONAJE
            addObjetoGrafico(main_caracter_path,desk_widht/8,2*desk_height/4,w_sir,h_sir,true);
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
            boton2->setStyleSheet("border-image:url(:/personajes/imagenes/Bala1.png);");
            boton2->setPalette(p);
            boton3->setGeometry(50,210,80,60);
            boton3->setStyleSheet("border-image:url(:/personajes/imagenes/Bomba.png);");
            boton3->setPalette(p);
            boton4->setGeometry(50,270,80,60);
            boton4->setStyleSheet("border-image:url(:/personajes/imagenes/Bala3.png);");
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
    //connect(timer, &QTimer::timeout, this, &MainWindow::cambiofondo);
}

///         FUNCION QUE DISPONE LOS OBJETOS DEL JUEGO         ///
void MainWindow::loadGameWigets()
{
    int opc = 2;
    addItems2Scene(opc);
    connectItems();
}

void MainWindow::startGame(QString title,QString text)
{
        ///INICIALIZAR PARAMETROS
    infoBox(title,text,"");    
    paused = false;
    serialInit();
    serial_timer->start(fs_time);
    seconds->start(time_seconds);
    //timer->start(200);
    if(arcade) enemy_timer->start(time_enemys/level);
}

void MainWindow::loadGame(vector<QString> data, vector<QString> enemys)
{
    loadData(data);
    displayData();
    loadEnemys(enemys);
    loadGameWigets();
    connectItems();
    startGame("GAME LOADED","DO IT BETTER");
    scene->start();
}

void MainWindow::displayData()
{
    display_ammo1->display(ammu1);
    display_ammo1->display(ammu2);
    display_ammo1->display(ammu3);
    life_bar->setValue(cont);
    display_time->display(game_time);
    if(player == 1) display_score->display(score_1*int(increment*game_time));
    else display_score->display(score_2*int(increment*game_time));
}


///         OPCION ARCADE         ///
void MainWindow::setArcade(bool value)
{
    arcade = value; this->player = 1; this->game_time = 0;
}

///         OPCION MULTIJUGADOR         ///
void MainWindow::setMultiplayer()
{
    arcade = false; player = 1; game_time = 0;
}

bool MainWindow::saveMatchData()
{
    // match_name, username, arcade, level , player, blood, game_time, score1, score2, ammo1,ammo2,ammo3
    bool success = false;
    if(player == 1) score_1 = scene->getScore();
    else if(player == 2) score_2 = scene->getScore();
    success = database->insertarDatos(match_name,username,arcade,level,player,scene->getBlood()
                                  ,game_time,score_1,score_2,ammu1,ammu2,ammu3);
    return success;
}

bool MainWindow::saveListEnemies(vector<Objeto_Movil* > vec)
{
    bool success = true,success2 = true;
    vector<Objeto_Movil* >::iterator it;
    for(it = vec.begin();it != vec.end(); it++){
        /// SI ES ENEMIGO
        if(!(*it)->getLado()){
            success = database->insertarEnemigos(match_name,username,(*it)->getX(),(*it)->getY(),(*it)->getV0(),
                                       (*it)->getAngle(),(*it)->getMove());
            if(!success) success2 = false;
        }
    }
    return success2;
}

void MainWindow::loadData(vector<QString> data)
{

    arcade = data.at(0).toInt(); qDebug()<<"Arcade "<<arcade;
    level = data.at(1).toInt();  qDebug()<<"Nivel "<<level;
    player = data.at(2).toInt();  qDebug()<<"Turno "<<player;
    cont = data.at(3).toInt();  qDebug()<<"BLood "<<cont;    
    game_time = data.at(4).toInt();  qDebug()<<"game_time "<<game_time;
    score_1 = data.at(5).toInt();  qDebug()<<"score1 "<<score_1;
    score_2 = data.at(6).toInt();  qDebug()<<"score2 "<<score_2;
    ammu1 = data.at(7).toInt();  qDebug()<<"ammo1 "<<ammu1;
    ammu2 = data.at(8).toInt();  qDebug()<<"ammo2 "<<ammu2;
    ammu3 = data.at(9).toInt();  qDebug()<<"ammo3 "<<ammu3;
}

void MainWindow::loadEnemys(vector<QString> enemys)
{
    int _x,_y,_v0,_angle,_move;
    for(int i = 0; unsigned(i)<enemys.size(); i+=5){
        _x = enemys.at(i).toInt(); qDebug()<<"x "<<_x;
        _y = enemys.at(i+1).toInt(); qDebug()<<"y "<<_y;
        _v0 = enemys.at(i+2).toInt(); qDebug()<<"v0 "<<_v0;
        _angle = enemys.at(i+3).toInt(); qDebug()<<"angle "<<_angle;
        _move = enemys.at(i+4).toInt(); qDebug()<<"move "<<_move;
        addObjetoMovil(enemy_path,_x,_y,_v0,_angle,_move);
    }
}

///         AÑADE OBJETOS SIN MOVIMIENTO         ///
void MainWindow::addObjetoGrafico(QString ruta, int x, int y, int w, int h,bool main)
{
    ///DECLARACION DE OBJETOS
    scene->addObjetoGrafico(ruta,x,y,w,h,main);
}

///         AÑADE OBJETOS CON MOVIMIENTO         ///
void MainWindow::addObjetoMovil(QString ruta, int xo, int yo, int xf, int yf, int w, int h, int _move)
{
    scene->addObjetoMovil(ruta,xo,yo,xf,yf,w,h,_move);
}

void MainWindow::addObjetoMovil(QString ruta, int xo, int yo, int v0, int angle, int _move)
{
    scene->addObjetoMovil(ruta,xo,yo,v0,angle,_move);
}








///         EVENTOS DE TECLADO         ///
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int save = 0;
    bool success = false;
    if(event->key() == Qt::Key_Space ){
        //qDebug()<<"\nAÑADIENDO OBJETO\n";
        if(!arcade){
            if(scene->getHurt() > 0){
                addObjetoMovil(enemy_path,
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
            save = question3Box("PAUSE","GAME PAUSE","CHOSE AN OPTION:","CONTINUE","SAVE","RESTART");
            if(save == 1){
                this->start();
            }
            else if(save == 2){
                qDebug()<<"GUARDANDO PARTIDA";
                success = saveListEnemies(scene->getObjetosMoviles());
                if(success){
                    success = saveMatchData();
                    infoBox("GOTCHA","SAVED SUCCESFULY.","");this->start();
                    if(!success){
                        infoBox("WARNING","CAN`T SAVE THE GAME","");this->start();
                        }
                    else{
                        scene->restart();
                        comeBack();
                    }
                }
                else {infoBox("WARNING","CAN`T SAVE THE GAME","");this->start();}
            }
            else if(save == 3){
                this->restart("RESTART","DO IT BETTER");
            }
            else this->start();

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
            addObjetoMovil(bala1_path,
                           x_sir,y_sir,event->x(),event->y(),50,50,move1);
            ammu1--;
            display_ammo1->display(ammu1);
        }
        else if (move1 == 2 && ammu2 > 0){
            addObjetoMovil(bala2_path,
                           x_sir,y_sir,event->x(),event->y(),50,50,move1);
            ammu2--;
            display_ammo2->display(ammu2);
        }
        else if (move1 == 3 && ammu3 > 0){
            addObjetoMovil(bala3_path,
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
    QString title, infoText,text;
    bool opt = false;
    /// PAUSA A TODO EN ESCENA
    pause();

    if(arcade){
    /// FIN DE JUEGO ARCADE
        score_player1 = scene->getScore()*int(increment*game_time);
        title = "GAME ENDED";
        text = "THE FINAL SCORE IS:";
        infoText = QString::number(score_player1);
        opt = questionBox(title,text,infoText,"MENU","RESTART");
        if(!opt){
            // GO TO MENU
            scene->restart();
            comeBack();
        }
        else{
            // RESTART
            this->restart("¿AGAIN?","TRY TO DO BETTER.");

        }

    }
    else if(player == 2){
        /// FIN DE JUEGO MULTIPLAYER
        score_player2 = scene->getScore()*int(increment*game_time);
        title = "GAME OVER";
        text = "THE WINNER IS:";

        if(score_player1 > score_player2){
            infoText = "PLAYER 1 -> SCORE: "+QString::number(score_player1);
        }
        else {
            infoText = "PLAYER 2 -> SCORE: "+QString::number(score_player2);
        }
        opt = questionBox(title,text,infoText,"MENU","RESTART");
        if (!opt) {
            // GO TO MENU
            scene->restart();
            comeBack();
        } else {
            // RESTART
            this->restart("NICE BATTLE","WHO`S GONNA WIN THIS TIME?");
        }

    }
    else{
        //qDebug()<<"Player "<<player;
        player = 2;
        score_player1 = scene->getScore()*int(increment*game_time);
        this->restart("PLAYER 2","BEAT HIM.");
    }
}

void MainWindow::setGameValues(int _blood, int _score, int _player, int _a1, int _a2, int _a3,bool _arcade)
{
    scene->setBlood(_blood); life_bar->setValue(_blood);
    scene->setScore(_score); display_score->display(_score);
    player = _player;
    ammu1 = _a1;
    ammu2 = _a2;
    ammu3 = _a3;
    arcade = _arcade;
    paused = false;
}

void MainWindow::setDefaultValues()
{
    ammu1 = 30/level; display_ammo1->display(ammu1);
    ammu2 = 30/level; display_ammo2->display(ammu2);
    ammu3 = 30/level; display_ammo3->display(ammu3);
    paused = false;
    enable2Shot = true;
}

void MainWindow::addEnemy()
{
    move2=1+rand()%(4-1);
    addObjetoMovil(enemy_path,
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
    scene->start();
    if(arcade) enemy_timer->start(time_enemys/level);
}

void MainWindow::restart(QString title,QString text)
{

    scene->restart();
    game_time = 0;    
    setDefaultValues();
    this->startGame(title,text);
}

bool MainWindow::questionBox(QString title, QString text, QString infoText, const char * _boton1, const char* _boton2)
{
    bool option = false;
    msgBox->setWindowTitle(title);
    msgBox->setText(text);
    msgBox->setInformativeText(infoText);
    msgBox->setGeometry((desk_widht/2)-100,(2*desk_height/3)-100,300,400);
    QPushButton *menuButton = msgBox->addButton(tr(_boton1), QMessageBox::ActionRole);
    QPushButton *restartButton = msgBox->addButton(tr(_boton2),QMessageBox::ActionRole);
    msgBox->exec();
    if (msgBox->clickedButton() == menuButton) {
        // FALSE -> OPCION 1
        option = false;
    } else if (msgBox->clickedButton() == restartButton) {
        // TRUE -> OPCION 2
        option = true;
    }
    msgBox->removeButton(menuButton);msgBox->removeButton(restartButton);
    delete menuButton; delete restartButton;
    //msgBox->hide();
    return option;
}

int MainWindow::question3Box(QString title, QString text, QString infoText, const char *_boton1, const char *_boton2, const char *_boton3)
{
    int option = 1;
    msgBox->setWindowTitle(title);
    msgBox->setText(text);
    msgBox->setInformativeText(infoText);
    msgBox->setGeometry((desk_widht/2)-100,(2*desk_height/3)-100,300,400);
    QPushButton *menuButton = msgBox->addButton(tr(_boton1), QMessageBox::ActionRole);
    QPushButton *restartButton = msgBox->addButton(tr(_boton2),QMessageBox::ActionRole);
    QPushButton *restart2Button = msgBox->addButton(tr(_boton3),QMessageBox::ActionRole);
    msgBox->exec();
    if (msgBox->clickedButton() == menuButton) {
        // FALSE -> OPCION 1
        option = 1;
    } else if (msgBox->clickedButton() == restartButton) {
        // TRUE -> OPCION 2
        option = 2;
    }
    else if (msgBox->clickedButton() == restart2Button) {
            // TRUE -> OPCION 2
            option = 3;
        }
    msgBox->removeButton(menuButton);msgBox->removeButton(restartButton);
    msgBox->removeButton(restart2Button);
    delete menuButton; delete restartButton; delete restart2Button;
    //msgBox->hide();
    return option;
}

void MainWindow::infoBox(QString title, QString text,QString infoText)
{
    msgBox->setWindowTitle(title);
    msgBox->setText(text);
    msgBox->setInformativeText(infoText);
    msgBox->setGeometry((desk_widht/2)-100,(2*desk_height/3)-100,300,700);
    msgBox->exec();
    //msgBox->removeButton(msgBox->buttons().at(0));
    msgBox->hide();
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
    scene->addObjetoGrafico(ruta,x,y,w,h,false);
}

void MainWindow::cambiofondo()
{
    if (cont == 1) {view->setBackgroundBrush(QImage(":/personajes/imagenes/Fondo_Original1.png"));cont=2;}
        else if (cont == 2) {view->setBackgroundBrush(QImage(":/personajes/imagenes/Fondo_Original22.png"));cont=3;}
        else if (cont == 3) {view->setBackgroundBrush(QImage(":/personajes/imagenes/Fondo_Original33.png"));cont=1;}
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

bool MainWindow::getArcade() const
{
    return arcade;
}

int MainWindow::getPlayer() const
{
    return player;
}

int MainWindow::getGame_time() const
{
    return game_time;
}

void MainWindow::setGame_time(int value)
{
    game_time = value;
}

void MainWindow::setLevel(int value)
{
    level = value;
}

void MainWindow::setDatabase(DataBase *value)
{
    database = value;
}

void MainWindow::setMatch_name(const QString &value)
{
    match_name = value;
}

void MainWindow::setUsername(const QString &value)
{
    username = value;
}


void MainWindow::moveObject()
{
    ///ASIGNACION DE VALORES
    scene->doSome();
}
