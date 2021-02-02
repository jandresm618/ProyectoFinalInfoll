#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QKeyEvent>
#include <QPushButton>
#include <QGraphicsView>
#include <QDebug>
#include <QLCDNumber>
#include <QLabel>
#include <QProgressBar>
#include <QMessageBox>
#include <stdlib.h>
#include <time.h>
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

    void instanceItems();
    void hideItems();
    void addItems2Scene(int opc);
    void connectItems();
    void loadGame();

    /// MODOS DE JUEGO
    void setArcade();
    void setMultiplayer();

    /// SLOTS
    void comeBack();
    void moveObject();
    void addObjetoGrafico(QString ruta,int x,int y, int w, int h);
    void addObjetoMovil(QString ruta,int xo,int yo,int xf,int yf,int w,int h,int _move);
    void addObjetoMovil1();
    void addObjetoMovil2();
    void addObjetoMovil3();
    void secondsPlusPlus();

    ///Eventos de Teclado
    void keyPressEvent(QKeyEvent *event);
    ///Eventos del Mouse
    void mousePressEvent(QMouseEvent *event) ;



    /// FUNCIONES DE PRUEBA
    int sec2min(int _seconds,bool out);
    bool canShot(int limit);
    void endOfGame();
    void setGameValues(int _blood, int _score, int _player, int _a1, int _a2, int _a3, bool _arcade);
    void addEnemy();
    void pause();
    void start();
    void restart(int player);
    void add();
    void imagen1();
    void imagen2();
    void setPosSir(int x, int y);

private:
    Ui::MainWindow *ui;
        /// OBJETO PUERTO SERIAL
    QSerialPort serial;
        /// BOTONES
    QPushButton *boton;
    QPushButton *boton2;
    QPushButton *boton3;
    QPushButton *boton4;
    QPushButton *boton5;
        /// LABELS
    QLabel *label1;
    QLabel *label2;
        /// LCD DISPLAYS
    QLCDNumber *display_time;
    QLCDNumber *display_ammo1;
    QLCDNumber *display_ammo2;
    QLCDNumber *display_ammo3;
    QLCDNumber *display_score;
        /// BARRA DE SANGRE
    QProgressBar *life_bar;

        /// TIMERS
    QTimer *serial_timer;
    QTimer *enemy_timer;
    QTimer *seconds;
        /// ESCENARIO
    Escena_Juego *scene;
    QGraphicsView *view;

    int desk_widht,desk_height;
    bool img = true;

    bool serial_available = false;
    char serial_char;
    string serial_port = "/dev/ttyUSB0";
    QString time_format;

        ///POSICION DE PERSONAJE PRINCIPAL
    int x_sir = 0, y_sir = 500;
        /// NUMERO DE MUNICIONES
    int ammu1 = 10, ammu2 = 10, ammu3 =  10;
        /// INDICADOR DE TIPO MOVIMIENTO
    int move1 = 1 , move2 = 1;
    int fs_time = 50, game_time = 0;
    bool arcade = true;
    bool paused = false;
    int time_enemys = 1500,time_seconds = 1000;


    int player = 1;    
    int cont_aux = 0;
    bool enable2Shot = true;
    float increment = 1.3;

signals:
    void end();

};
#endif // MAINWINDOW_H
