#ifndef ESCENA_JUEGO_H
#define ESCENA_JUEGO_H

#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsSceneMouseEvent>
#include "objeto_grafico.h"
#include "objeto_movil.h"


class Escena_Juego : public QGraphicsScene
{

public:    
    Escena_Juego();
    ~Escena_Juego();

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) ;

    void setWindowProperty(int desk_w, int desk_h);
    virtual void drawBackground(QPainter *painter, const QRectF &exposed);

    void arcadeDesing();

    void addObjetoGrafico(QString ruta,int x,int y,int w,int h);
    void addObjetoMovil(QString ruta,int x,int y,int xf,int yf,int w,int h,int move);
    void doSome();

    void setHurt();
    int getHurt();

    void pause();
    void start();
    void restart();

    /// SLOTS DE OBJETOS MOVILES
    bool deleteFromScene();

    int getScore() const;
    void setScore(int value);
    void setScorePlus();

    int getBlood() const;
    void setBlood(int value);

private:
    Objeto_Grafico *personaje;
    Objeto_Movil *muni;

    /// CONTENEDORES DE OBJETOS
    vector<Objeto_Grafico *> objetosGraficos;
    vector<Objeto_Grafico *>::iterator itObjGra;
    vector<Objeto_Movil *> objetosMoviles;
    vector<Objeto_Movil *>::iterator itObjMov;
    vector<Objeto_Movil *>::iterator itObjMov2;

    int limit_x,limit_y;
    QPixmap *image;

    int blood = 100;
    int score = 0;
    int cont_1 = 0;
    int time_move = 60;
};

#endif // ESCENA_JUEGO_H
