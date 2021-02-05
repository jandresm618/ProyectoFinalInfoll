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
    QColor bg_color(255, 0, 0, 0);
    QPalette p;
    p.setColor(QPalette::Background, bg_color);

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
    boton6 = new QPushButton(this);
    boton7 = new QPushButton(this);
    label1 = new QLabel(this);
    label2 = new QLabel(this);
    label3 = new QLabel(this);
    line_Edit1 = new QLineEdit(this);
    line_Edit2 = new QLineEdit(this);
    line_Edit3 = new QLineEdit(this);
    spin_box1 = new QSpinBox(this);
    table_widget = new QTableWidget(this);
    table_widget->setPalette(p);
}

void Control_Usuario::hideItems()
{
    boton1->hide();
    boton2->hide();
    boton3->hide();
    boton4->hide();
    boton5->hide();
    boton6->hide();
    boton7->hide();
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
    disconnect(boton3,&QPushButton::clicked,this,&Control_Usuario::loadGame);
    disconnect(boton4,&QPushButton::clicked,this,&Control_Usuario::showRecordsWindow);
    disconnect(boton5,&QPushButton::clicked,this,&Control_Usuario::exit);
    disconnect(boton6,&QPushButton::clicked,this,&Control_Usuario::setBackground1);
    disconnect(boton7,&QPushButton::clicked,this,&Control_Usuario::setBackground2);
    disconnect(boton2,&QPushButton::clicked,this,&Control_Usuario::loadDataGame);
}

void Control_Usuario::showSavedGames()
{
    vector<QString> data = database->mostrarPartidas(user_name);
    QStringList l;
    l<<"MATCH NAME";
    printVectorInTable(data,l,1);
}

void Control_Usuario::showRecords()
{
    vector<QString> data = database->mostrarRecord();
    QStringList l;
    l<<"MATCH NAME"<<"SCORE"<<"PLAYER";
    printVectorInTable(data,l,3);
}

void Control_Usuario::exit()
{
    gameWindow->close();
    this->close();
    delete this;
}

void Control_Usuario::welcomeWindow()
{

    /// VENTANA DE TIPO DE REGISTRO

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
    connect(boton4,&QPushButton::clicked,this,&Control_Usuario::showRecordsWindow);
    connect(boton5,&QPushButton::clicked,this,&Control_Usuario::exit);
}

void Control_Usuario::setMatchNameWindow()
{
    ///CONEXION DE SIGNAL & SLOT
    disconnectAll();
    hideItems();

    boton6->setStyleSheet("border-image:url(:/personajes/imagenes/fondo.png);");
    boton6->setGeometry((1*desk_width/3)+250,(1*desk_height/5)-50,300,200);
    boton6->show();

    boton7->setStyleSheet("border-image:url(:/personajes/imagenes/Fondo_Original1.png);");
    boton7->setGeometry((2*desk_width/3)+120,(1*desk_height/5)-50,300,200);
    boton7->show();

    label1->setGeometry((2*desk_width/3)-80,(2*desk_height/5)+50,280,130);
    label1->setStyleSheet("border-image:url(:/personajes/imagenes/MATCH NAME.png);");
    label1->show();

    line_Edit1->setGeometry((2*desk_width/3)+200,(2*desk_height/5)+50,200,70);
    line_Edit1->setStyleSheet("border-image:url(:/personajes/imagenes/index.png);");
    line_Edit1->setText("");
    line_Edit1->show();

    if(arcade){
        label2->setGeometry((2*desk_width/3),(4*desk_height/5)-150,200,100);
        label2->setStyleSheet("border-image:url(:/personajes/imagenes/DIFICULT.png);");
        label2->show();

        spin_box1->setGeometry((2*desk_width/3)+200,(4*desk_height/5)-150,100,60);
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
    connect(boton6,&QPushButton::clicked,this,&Control_Usuario::setBackground1);
    connect(boton7,&QPushButton::clicked,this,&Control_Usuario::setBackground2);


}

void Control_Usuario::loadGame()
{
    ///CONEXION DE SIGNAL & SLOT
    disconnectAll();
    hideItems();

    showSavedGames();
    table_widget->setGeometry((2*desk_width/3)-80,(1*desk_height/5)-50,300,300);
    table_widget->setStyleSheet("border-image:url(:/personajes/imagenes/index.png);");
    table_widget->show();

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

void Control_Usuario::showRecordsWindow()
{
    ///CONEXION DE SIGNAL & SLOT
    disconnectAll();
    hideItems();

    showRecords();
    table_widget->setGeometry((2*desk_width/3)-80,(2*desk_height/5)-50,300,300);
    table_widget->setStyleSheet("border-image:url(:/personajes/imagenes/index.png);");
    table_widget->show();


    boton1->setGeometry((2*desk_width/3),desk_height-200,200,100);
    boton1->setStyleSheet("border-image:url(:/personajes/imagenes/BACK.png);");
    boton1->show();

    connect(boton1,&QPushButton::clicked,this,&Control_Usuario::setMenuWindow);
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

    database->mostrarUsuarios();
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
                //qDebug()<<"USUARIO CORRECTO";
            }
            else if(database->getUser()) infoBox("WARNING","INCORRECT PASSWORD","");
            else infoBox("WARNING","INCORRECT USERNAME.","");
            //qDebug()<<"USUARIO CHEQUEADO";
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

void Control_Usuario::setBackground1()
{
    gameWindow->setBackground1();
}

void Control_Usuario::setBackground2()
{
    gameWindow->setBackground2();
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

void Control_Usuario::printVectorInTable(vector<QString> vec,QStringList l, int columns)
{
    vector<QString>::iterator it;
    QString row;
    int cont = 0;
    table_widget->setHorizontalHeaderLabels(l);
    if(!vec.empty()){
        table_widget->setRowCount(vec.size());
        for(it = vec.begin(); it !=  vec.end();it++,cont+=columns){
            //table_widget->setColumnCount(columns);
            table_widget->setColumnCount(columns);
            //table_widget->insertRow(table_widget->rowCount());
            table_widget->insertRow(0);
            for(int i=0;i<columns;i++){
                if(i!=0) it++;
                //row = row + " | " + *(it+i);
                table_widget->setColumnWidth(i,300/columns);
                qDebug()<<"-> "<<*(it);
                table_widget->setItem(0,i,new QTableWidgetItem(*(it))); row.clear();
            }
        }
    }
    //    ui->tableWidget->setRowCount(0);
    //    while (mostrar.next()) {
    //        qDebug()<<mostrar.value(1).toByteArray().constData();
    //        ui->tableWidget->insertRow(i);
    //        ui->tableWidget->setItem(i,0,new QTableWidgetItem("que pasa"));
        //    }
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
