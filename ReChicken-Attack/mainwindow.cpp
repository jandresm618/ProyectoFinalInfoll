#include "mainwindow.h"
#include "ui_mainwindow.h"


///         CONSTRUCTOR         ///
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    view = new QGraphicsView(this);
    scene = new Escena_Juego();

    view->setScene(scene);
    view->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));    
    this->showMaximized();


    boton = new QPushButton(QString("COME BACK"));
    boton->setGeometry(100,100,100,80);
    boton2 = new QPushButton(QString("MOVE"));
    boton2->setGeometry(300,100,100,80);
    boton3 = new QPushButton(QString("ADD"));
    boton3->setGeometry(600,100,100,80);
    scene->addWidget(boton);
    scene->addWidget(boton2);
    scene->addWidget(boton3);

    connect(boton,&QPushButton::clicked,this,&MainWindow::comeBack);
    connect(boton2,&QPushButton::clicked,this,&MainWindow::moveObject);
    connect(boton3,&QPushButton::clicked,this,&MainWindow::addObjetoMovil);
}

///         DESTRUCTOR         ///
MainWindow::~MainWindow()
{
    delete boton;
    delete boton2;
    delete view;
    delete scene;
    delete ui;
}

///     FUNCION RETORNO AL MENU     ///
void MainWindow::comeBack()
{
    this->hide();
    this->parentWidget()->show();

}

void MainWindow::moveObject()
{
    scene->doSome();
}

///     FUNCION SET PROPIEDADES ESCRITORIO      ///
void MainWindow::setDeskProperty(int w, int h)
{
   desk_widht = w;
   desk_height = h;   
   view->setGeometry(0,0,w,h);
   scene->setWindowProperty(w,h);
}

void MainWindow::addObjetoGrafico(QString ruta, int x, int y, int w, int h)
{
    scene->addObjetoGrafico(ruta,x,y,w,h);
}

void MainWindow::addObjetoMovil()
{
    QString ruta = ":/personajes/imagenes/GIFT.png"; int x=0; int y=500; int w=80; int h=80;
    int xf = 900,yf = 500;
    scene->addObjetoMovil(ruta,x,y,xf,yf,w,h);
}

void MainWindow::add()
{
    QString ruta = ":/personajes/imagenes/GIFT.png"; int x=0; int y=100; int w=80; int h=80;
    scene->addObjetoGrafico(ruta,x,y,w,h);
}


