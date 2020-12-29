#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    boton = new QPushButton(QString("COME BACK"),this);
    boton->setGeometry(100,100,100,80);

    connect(boton,&QPushButton::clicked,this,&MainWindow::comeBack);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::comeBack()
{
    this->hide();
    this->parentWidget()->show();

}


