#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
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

    /// FUNCIONES DE PUERTO SERIAL
    void serialInit();
    void serialRead();

    /// CARACTERISTICAS DE PANTALLA
    void setDeskProperty(int w,int h);

    /// SLOTS DE BOTONES
    void comeBack();
    void moveObject();
    void addObjetoGrafico(QString ruta,int x,int y, int w, int h);
    void addObjetoMovil();

    /// FUNCIONES DE PRUEBA
    void add();
    void imagen1();
    void imagen2();

private:
    Ui::MainWindow *ui;
    /// OBJETO SERIAL
    QSerialPort serial;

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

    char serial_char;
    QString serial_port = "/dev/ttyACM0";

};
#endif // MAINWINDOW_H
