#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QKeyEvent>
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

    /// MODOS DE JUEGO
    void setArcade();
    void setMultiplayer();

    /// SLOTS DE BOTONES
    void comeBack();
    void moveObject();
    void addObjetoGrafico(QString ruta,int x,int y, int w, int h);
    void addObjetoMovil(QString ruta,int xo,int yo,int xf,int yf,int w,int h,int _move);
    void addObjetoMovil1();
    void addObjetoMovil2();
    void addObjetoMovil3();

    ///Eventos de Teclado
    void keyPressEvent(QKeyEvent *event);
    ///Eventos del Mouse
    void mousePressEvent(QMouseEvent *event) ;



    /// FUNCIONES DE PRUEBA
    void add();
    void imagen1();
    void imagen2();
    void setPosSir(int x, int y);

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

    bool serial_available = false;
    char serial_char;
    string serial_port = "/dev/ttyUSB0";

    int x_sir = 0, y_sir = 500;
    int move = 1;
    bool arcade = true;

};
#endif // MAINWINDOW_H
