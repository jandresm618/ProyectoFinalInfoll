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
#include "database.h"



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

        /// FUNCIONES DE CARGA DE OBJETOS Y PRESENTACION
    void instanceItems();
    void hideItems();
    void addItems2Scene(int opc);
    void connectItems();
    void loadGameWigets();
    void startGame(QString title,QString text);
    void loadGame(vector<QString> data, vector<QString> enemys);
    void displayData();

        /// FUNCIONES CONTROL DEL JUEGO
    void endOfGame();
    void pause();
    void start();
    void restart(QString title,QString text);
    bool questionBox(QString title,  QString text,QString infoText,
                     const char *_boton1, const char *_boton2);
    int question3Box(QString title,  QString text,QString infoText,
                     const char *_boton1, const char *_boton2,const char *_boton3);
    void infoBox(QString title, QString text, QString infoText);

        /// MODOS DE JUEGO
    void setMultiplayer();

        /// FUNCIONES DE GUARDADO
    bool saveMatchData();
    bool saveListEnemies(vector<Objeto_Movil *> vec);
    void loadData(vector<QString> data);
    void loadEnemys(vector<QString> enemys);

        /// SLOTS
    void comeBack();
    void moveObject();
    void addObjetoGrafico(QString ruta, int x, int y, int w, int h, bool main);
    void addObjetoMovil(QString ruta,int xo,int yo,int xf,int yf,int w,int h,int _move);
    void addObjetoMovil(QString ruta,int xo,int yo,int v0,int angle,int _move);
    void addObjetoMovil1();
    void addObjetoMovil2();
    void addObjetoMovil3();
    void secondsPlusPlus();
    void addEnemy();

        ///Eventos de Teclado
    void keyPressEvent(QKeyEvent *event);
        ///Eventos del Mouse
    void mousePressEvent(QMouseEvent *event) ;


        /// FUNCIONES AUXILIARES
    int sec2min(int _seconds,bool out);
    bool canShot(int limit);
    void setGameValues(int _blood, int _score, int _player, int _a1, int _a2, int _a3, bool _arcade);
    void setDefaultValues();


        /// FUNCIONES DE PRUEBA
    void add();
    void cambiofondo();
    void actualizarcronometro();
    void Estado();

    void imagen1();
    void imagen2();
    void setPosSir(int x, int y);

    bool getArcade() const;
    void setArcade(bool value);

    int getPlayer() const;

    int getGame_time() const;
    void setGame_time(int value);

    void setLevel(int value);

    void setDatabase(DataBase *value);

    void setMatch_name(const QString &value);

    void setUsername(const QString &value);

private:
    Ui::MainWindow *ui;

    DataBase *database;
    QMessageBox *msgBox;
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
    QTimer *timer;


        /// ESCENARIO
    Escena_Juego *scene;
    QGraphicsView *view;
        /// MEDIDAS DE ESCRITORIO
    int desk_widht,desk_height;
        /// VARIABLES DE PUERTO SERIAL
    bool serial_available = false;
    char serial_char;
    string serial_port = "/dev/ttyUSB0";

        /// VARIABLES AUXILIARES
    QString time_format;
    bool img = true;
    int cont_aux = 0;
    int cont=1;

        /// VARIABLES DE CONTROL
    QString match_name,username;
    QString main_caracter_path = ":/personajes/imagenes/senor11.png";
    QString enemy_path = ":/personajes/imagenes/pollo.png";
    QString bala1_path = ":/personajes/imagenes/Bala1.png";
    QString bala2_path = ":/personajes/imagenes/Bomba.png";
    QString bala3_path = ":/personajes/imagenes/Bala3.png";
    bool arcade = true;
    bool paused = false;
    int player = 1;
    bool enable2Shot = true;
    float increment = 1.3;
    int score_player1 = 0,score_player2 = 0;
    int score_1 = 0,score_2 = 0;

        ///POSICION DE PERSONAJE PRINCIPAL
    int x_sir = desk_widht/8, y_sir = desk_height-310;
    int w_sir = 200, h_sir = 300;
        /// NUMERO DE MUNICIONES
    int ammu1 = 10, ammu2 = 10, ammu3 =  10;
        /// INDICADOR DE TIPO MOVIMIENTO
    int move1 = 1 , move2 = 1;
        /// VALORES DE TIMERS
    int fs_time = 50, game_time = 0;
    int time_enemys = 1500,time_seconds = 1000;
    int level = 1;



signals:
    void end();

};
#endif // MAINWINDOW_H
