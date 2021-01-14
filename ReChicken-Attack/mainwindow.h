#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsView>
#include <QDebug>
#include "escena_juego.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void comeBack();
    void moveObject();
    void setDeskProperty(int w,int h);

    void addObjetoGrafico(QString ruta,int x,int y, int w, int h);
    void addObjetoMovil();
    void add();

    void imagen1();
    void imagen2();

private:
    Ui::MainWindow *ui;
    QPushButton *boton;
    QPushButton *boton2;
    QPushButton *boton3;
    QPushButton *boton4;
    QPushButton *boton5;
    QGraphicsView *view;

    QTimer *time;

    Escena_Juego *scene;

    int desk_widht,desk_height;
    bool img = true;

};
#endif // MAINWINDOW_H
