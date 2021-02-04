#include "control_usuario.h"
#include "ui_control_usuario.h"

///         CONSTRUCTOR          ///
Control_Usuario::Control_Usuario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Control_Usuario)
{
    ///ASIGNACION DE VALORES
    ui->setupUi(this);

    /// Inicializa los objetos que necesitan memoria dinamica
    crearObjetos();

    ///ASIGNACION DE VALORES DE VENTANA
    setGeometry(0,0,desk_width,desk_height);    /// Geometria de la Ventana

    //setMenuWindow(); /// Dispone los botones necesarios para la primera visualizacion
    welcomeWindow();


}


///     DESTRUCTOR       ///
Control_Usuario::~Control_Usuario()
{
    delete boton1;
    delete boton2;
    delete boton3;
    delete boton4;
    delete boton5;
    delete label1;
    delete label2;
    delete label3;
    delete line_Edit1;
    delete line_Edit2;
    delete line_Edit3;
    delete spin_box1;
    delete table_widget;
    delete gameWindow;
    delete deskWidget;
    delete ui;
}

void Control_Usuario::crearObjetos()
{
    ///DECLARACION DE OBJETOS
    deskWidget = new QDesktopWidget;
    gameWindow = new MainWindow(this);gameWindow->hide();
    database = new DataBase;
    desk_width = deskWidget->width();   desk_height = deskWidget->height();
    gameWindow->setDeskProperty(desk_width,desk_height);
    gameWindow->setDatabase(database);
    msgBox = new QMessageBox(this);
    msgBox->setStyleSheet("border-image:url(:/personajes/imagenes/index.png);");
    msgBox->setGeometry((desk_width/2)-100,(2*desk_height/3)-100,300,400);
    boton1 = new QPushButton(this);
    boton2 = new QPushButton(this);
    boton3 = new QPushButton(this);
    boton4 = new QPushButton(this);
    boton5 = new QPushButton(this);
    label1 = new QLabel(this);
    label2 = new QLabel(this);
    label3 = new QLabel(this);
    line_Edit1 = new QLineEdit(this);
    line_Edit2 = new QLineEdit(this);
    line_Edit3 = new QLineEdit(this);
    spin_box1 = new QSpinBox(this);
    table_widget = new QTableWidget(this);
}

void Control_Usuario::hideItems()
{
    boton1->hide();
    boton2->hide();
    boton3->hide();
    boton4->hide();
    boton5->hide();
    label1->hide();
    label2->hide();
    label3->hide();
    line_Edit1->hide();
    line_Edit2->hide();
    line_Edit3->hide();
    spin_box1->hide();
    table_widget->hide();
}

void Control_Usuario::disconnectAll()
{
    disconnect(boton1,&QPushButton::clicked,this,&Control_Usuario::welcomeWindow);
    disconnect(boton2,&QPushButton::clicked,this,&Control_Usuario::validateUser);
    disconnect(boton1,&QPushButton::clicked,this,&Control_Usuario::signIn);
    disconnect(boton2,&QPushButton::clicked,this,&Control_Usuario::logIn);
    disconnect(boton1,&QPushButton::clicked,this,&Control_Usuario::setMenuWindow);
    disconnect(boton2,&QPushButton::clicked,this,&Control_Usuario::startGame);
    disconnect(boton1,&QPushButton::clicked,this,&Control_Usuario::setArcade);
    disconnect(boton2,&QPushButton::clicked,this,&Control_Usuario::setMultiplayer);
    disconnect(boton3,&QPushButton::clicked,this,&Control_Usuario::setMultiplayer);
    disconnect(boton4,&QPushButton::clicked,this,&Control_Usuario::setMultiplayer);
    disconnect(boton5,&QPushButton::clicked,this,&Control_Usuario::setMultiplayer);
}

void Control_Usuario::welcomeWindow()
{
    /*
    if(s1){
        disconnect(boton1,&QPushButton::clicked,this,&Control_Usuario::welcomeWindow);
        disconnect(boton2,&QPushButton::clicked,this,&Control_Usuario::validateUser);
    }
    /// VENTANA DE TIPO DE REGISTRO
    s1 = true; s2 = false;*/
    disconnectAll();
    hideItems();

    boton1->setGeometry((2*desk_width/3),(2*desk_height/4)-100,300,140);
    boton1->setStyleSheet("border-image:url(:/personajes/imagenes/SING UP.png);");
    boton1->show();

    boton2->setGeometry((2*desk_width/3),(3*desk_height/4)-150,300,140);
    boton2->setStyleSheet("border-image:url(:/personajes/imagenes/LOG IN.png);");
    boton2->show();


    connect(boton1,&QPushButton::clicked,this,&Control_Usuario::signIn);
    connect(boton2,&QPushButton::clicked,this,&Control_Usuario::logIn);
}

void Control_Usuario::setCredentialsWindow()
{
    /*
    if(!s2){
        disconnect(boton1,&QPushButton::clicked,this,&Control_Usuario::signIn);
        disconnect(boton2,&QPushButton::clicked,this,&Control_Usuario::logIn);
    }
    s2 = true;*/
    disconnectAll();
    hideItems();

    label1->setGeometry((2*desk_width/3),(desk_height/5),200,100);
    label1->setStyleSheet("border-image:url(:/personajes/imagenes/NICKNAME.png);");
    label1->show();

    line_Edit1->setGeometry((2*desk_width/3)+200,(desk_height/5),200,70);
    line_Edit1->setStyleSheet("border-image:url(:/personajes/imagenes/index.png);");
    line_Edit1->show();

    label2->setGeometry((2*desk_width/3),(2*desk_height/5),200,100);
    label2->setStyleSheet("border-image:url(:/personajes/imagenes/PASSWORD.png);");
    label2->show();

    line_Edit2->setGeometry((2*desk_width/3)+200,(2*desk_height/5),200,70);
    line_Edit2->setStyleSheet("border-image:url(:/personajes/imagenes/index.png);");
    line_Edit2->show();

    if(newUser){
        label3->setGeometry((2*desk_width/3),(3*desk_height/5),200,100);
        label3->setStyleSheet("border-image:url(:/personajes/imagenes/PASSWORD.png);");
        label3->show();
        line_Edit3->setGeometry((2*desk_width/3)+200,(3*desk_height/5),200,70);
        line_Edit3->setStyleSheet("border-image:url(:/personajes/imagenes/index.png);");
        line_Edit3->show();
    }
    boton1->setGeometry((2*desk_width/3),desk_height-200,200,100);
    boton1->setStyleSheet("border-image:url(:/personajes/imagenes/BACK.png);");
    boton1->show();
    boton2->setGeometry((2*desk_width/3)+250,desk_height-200,200,100);
    boton2->setStyleSheet("border-image:url(:/personajes/imagenes/DONE.png);");
    boton2->show();

    connect(boton1,&QPushButton::clicked,this,&Control_Usuario::welcomeWindow);
    connect(boton2,&QPushButton::clicked,this,&Control_Usuario::validateUser);

}

void Control_Usuario::setMenuWindow()
{
    /*
    s1 = false; s2 = false;

    if(!s3){
        disconnect(boton1,&QPushButton::clicked,this,&Control_Usuario::welcomeWindow);
        disconnect(boton2,&QPushButton::clicked,this,&Control_Usuario::validateUser);
    }
    else if(s4){
        disconnect(boton1,&QPushButton::clicked,this,&Control_Usuario::setMenuWindow);
        disconnect(boton2,&QPushButton::clicked,this,&Control_Usuario::startGame);
    }
    s3 = true;*/


    ///POR AHORA
    disconnectAll();
    hideItems();
    boton1->setGeometry(2*desk_width/3,desk_height/7,200,100);
    boton1->setStyleSheet("border-image:url(:/personajes/imagenes/ARCADE.png);");
    boton1->show();
    boton2->setGeometry((2*desk_width/3)-25,(2*desk_height/7),250,100);
    boton2->setStyleSheet("border-image:url(:/personajes/imagenes/MULTIPLAYER.png);");
    boton2->show();
    boton3->setGeometry(2*desk_width/3,3*desk_height/7,200,100);
    boton3->setStyleSheet("border-image:url(:/personajes/imagenes/LOAD GAME.png);");
    boton3->show();
    boton4->setGeometry(2*desk_width/3,4*desk_height/7,200,100);
    boton4->setStyleSheet("border-image:url(:/personajes/imagenes/RECORDS.png);");
    boton4->show();
    boton5->setGeometry(2*desk_width/3,5*desk_height/7,200,100);
    boton5->setStyleSheet("border-image:url(:/personajes/imagenes/EXIT.png);");
    boton5->show();


    ///CONEXION DE SIGNAL & SLOT
    connect(boton1,&QPushButton::clicked,this,&Control_Usuario::setArcade);
    connect(boton2,&QPushButton::clicked,this,&Control_Usuario::setMultiplayer);
    connect(boton3,&QPushButton::clicked,this,&Control_Usuario::loadGame);
    connect(boton4,&QPushButton::clicked,this,&Control_Usuario::setMultiplayer);
    connect(boton5,&QPushButton::clicked,this,&Control_Usuario::setMultiplayer);
}

void Control_Usuario::setMatchNameWindow()
{
    ///CONEXION DE SIGNAL & SLOT
    disconnectAll();
    hideItems();
    label1->setGeometry((2*desk_width/3)-80,(2*desk_height/5),280,130);
    label1->setStyleSheet("border-image:url(:/personajes/imagenes/MATCH NAME.png);");
    label1->show();

    line_Edit1->setGeometry((2*desk_width/3)+200,(2*desk_height/5),200,70);
    line_Edit1->setStyleSheet("border-image:url(:/personajes/imagenes/index.png);");
    line_Edit1->setText("");
    line_Edit1->show();
    if(arcade){
        label2->setGeometry((2*desk_width/3),(4*desk_height/5)-200,200,100);
        label2->setStyleSheet("border-image:url(:/personajes/imagenes/DIFICULT.png);");
        label2->show();

        spin_box1->setGeometry((2*desk_width/3)+200,(4*desk_height/5)-200,100,60);
        spin_box1->setStyleSheet("border-image:url(:/personajes/imagenes/index.png);");
        spin_box1->show();
        spin_box1->setRange(1,3);
        spin_box1->setValue(1);
    }

    boton1->setGeometry((2*desk_width/3),desk_height-200,200,100);
    boton1->setStyleSheet("border-image:url(:/personajes/imagenes/BACK.png);");
    boton1->show();
    boton2->setGeometry((2*desk_width/3)+250,desk_height-200,200,100);
    boton2->setStyleSheet("border-image:url(:/personajes/imagenes/DONE.png);");
    boton2->show();

    connect(boton1,&QPushButton::clicked,this,&Control_Usuario::setMenuWindow);
    connect(boton2,&QPushButton::clicked,this,&Control_Usuario::startGame);

}

void Control_Usuario::loadGame()
{
    ///CONEXION DE SIGNAL & SLOT
    disconnectAll();
    hideItems();
    label1->setGeometry((2*desk_width/3)-80,(3*desk_height/5),280,130);
    label1->setStyleSheet("border-image:url(:/personajes/imagenes/MATCH NAME.png);");
    label1->show();

    line_Edit1->setGeometry((2*desk_width/3)+200,(3*desk_height/5),200,70);
    line_Edit1->setStyleSheet("border-image:url(:/personajes/imagenes/index.png);");
    line_Edit1->setText("");
    line_Edit1->show();

    boton1->setGeometry((2*desk_width/3),desk_height-200,200,100);
    boton1->setStyleSheet("border-image:url(:/personajes/imagenes/BACK.png);");
    boton1->show();
    boton2->setGeometry((2*desk_width/3)+250,desk_height-200,200,100);
    boton2->setStyleSheet("border-image:url(:/personajes/imagenes/DONE.png);");
    boton2->show();

    connect(boton1,&QPushButton::clicked,this,&Control_Usuario::setMenuWindow);
    connect(boton2,&QPushButton::clicked,this,&Control_Usuario::loadDataGame);
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
    gameWindow->show();
    this->hide();
}


void Control_Usuario::setArcade()
{
    arcade = true;
    setMatchNameWindow();
    qDebug()<<"ESCOGIDO "<<arcade;

}

void Control_Usuario::setMultiplayer()
{
    arcade = false;
    setMatchNameWindow();

}

void Control_Usuario::logIn()
{
    /// INDICADOR DE QUE EL USUARIO YA EXISTE
    newUser = false;
    setCredentialsWindow();
}

void Control_Usuario::signIn()
{
    /// INDICADOR DE QUE SE QUIERE UN NUEVO USUARIO
    newUser = true;
    setCredentialsWindow();
}

void Control_Usuario::validateUser()
{
    bool proced = false;
    QString username = line_Edit1->text();
    QString password1 = line_Edit2->text();
    QString password2 = line_Edit3->text();

    bool validate;
    if(username != ""){
        /// VALIDAR QUE EL USUARIO EXISTA Y LAS CONTRASEÑAS COINCIDAN
        validate = database->validarUsuario(username,password1);
        if(newUser){
            /// USUARIO NUEVO-> VERIFICAR QUE EL NOMBRE NO EXISTA Y CONTRASEÑAS COINCIDAN
            if(!database->getUser()){
                /// EL USUARIO NO EXISTE
                if(password1 == password2){
                    database->insertarUsuario(username,password1);
                    user_name = username;
                    proced = true;

                }
                else infoBox("WARNING","PASSWORD DON`T MATCH.","");
            }
            else{
                /// EL USUARIO YA EXISTE
                infoBox("WARNING","USER ALREADY EXIST.","");
            }
        }
        else{
            /// USUARIO EXISTENTE -> VERIFICAR QUE SEA CIERTO Y CONTRASEÑAS COINCIDAN
            if(validate){
                proced = true;
                user_name = username;
            }
            qDebug()<<"USUARIO CHEQUEADO";
        }
    }
    else infoBox("WARNING","INCORECT USERNAME.","");
    if(proced) setMenuWindow();
}

void Control_Usuario::createUser()
{
    /// VALIDAR QUE EL USUARIO NO EXISTA Y LAS CONTRASEÑAS COINCIDAN
}

void Control_Usuario::startGame()
{
    int level = 1;
    if(arcade) level = spin_box1->value();
    QString match_name = line_Edit1->text();
    if(database->validarMatchName(match_name)){
        showMainWindow();
        gameWindow->setArcade(arcade);
        gameWindow->loadGameWigets();
        gameWindow->setMatch_name(match_name);
        gameWindow->setUsername(user_name);
        gameWindow->setLevel(level);
        gameWindow->startGame("NEW GAME","DO YOUR BEST.");
        gameWindow->setDefaultValues();
    }
    else{
        infoBox("WARNING","THIS NAME ALREADY EXISTS.","");
        //infoBox("WARNING","","");
        //qDebug()<<"NOMBRE NO VALIDO";
    }

}

void Control_Usuario::loadDataGame()
{
    vector<QString> data,enemys;
    QString match_n = line_Edit1->text();
    data = database->mostrarDatos(match_n,user_name);
    enemys = database->mostrarEnemigos(match_n,user_name);
    if(!data.empty() && !enemys.empty()){
        showMainWindow();
        gameWindow->loadGame(data,enemys);
    }
    else{
        /// PROBLEMAS AL CARGAR PARTIDA 
        infoBox("WARNING.","CANNOT LOAD GAME.","");
        //qDebug()<<"NO SE HA PODIDO CARGAR LA PARTIDA";
    }
}

void Control_Usuario::printVector(vector<QString> vec)
{
    vector<QString>::iterator it;
    if(!vec.empty()){
        for(it = vec.begin(); it !=  vec.end();it++){
            qDebug()<<"-> "<<(*it);
        }
    }
}

void Control_Usuario::infoBox(QString title, QString text, QString infoText)
{
    msgBox->setWindowTitle(title);
    msgBox->setText(text);
    msgBox->setInformativeText(infoText);
    msgBox->setGeometry((desk_width/2)-100,(2*desk_height/3)-100,300,700);
    msgBox->exec();
    //msgBox->removeButton(msgBox->buttons().at(0));
    msgBox->hide();
}
