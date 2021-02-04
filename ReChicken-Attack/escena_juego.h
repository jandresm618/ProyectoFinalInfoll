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
        /// CONSTRUCTOR Y DESTRUCTOR
    Escena_Juego();
    ~Escena_Juego();

        /// MOVIMIENTO DE MOUSE
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) ;

        /// CARACTERISTICAS DE ESCRITORIO
    void setWindowProperty(int desk_w, int desk_h);
    virtual void drawBackground(QPainter *painter, const QRectF &exposed);


    void arcadeDesing();

        /// FUNCIONES AÑADIR OBJETOS GRAFICOS
    void addObjetoGrafico(QString ruta,int x,int y,int w,int h);
    void addObjetoMovil(QString ruta,int x,int y,int xf,int yf,int w,int h,int move);

        /// FUNCIONES DE PRUEBA
    void doSome();

        /// MANEJO DE ATRIBUTO SANGRE
    void setHurt();
    int getHurt();
    int getBlood() const;
    void setBlood(int value);

        /// FUNCION DE CONTROL DE JUEGO
    void pause();
    void start();
    void restart();

        /// CONTROL DE COLISIONES Y PUESTAS EN ESCENA
    bool deleteFromScene();

        /// MANEJO DE ATRIBUTO SCORE
    int getScore() const;
    void setScore(int value);
    void setScorePlus();


    vector<Objeto_Movil *> getObjetosMoviles() const;

private:
    /// APUNTADOR A OBJETOS GRAFICOS
    Objeto_Grafico *personaje;
    Objeto_Movil *muni;

        /// CONTENEDORES DE OBJETOS
    vector<Objeto_Grafico *> objetosGraficos;
    vector<Objeto_Grafico *>::iterator itObjGra;
    vector<Objeto_Movil *> objetosMoviles;
    vector<Objeto_Movil *>::iterator itObjMov;
    vector<Objeto_Movil *>::iterator itObjMov2;

        /// CARACTERISTICAS DE ESCRITORIO
    int limit_x,limit_y;
    QPixmap *image;

        /// ATRIBUTOS DE JUEGO
    int blood = 100;
    int score = 0;
    int cont_1 = 0;
    int time_move = 60;
};

#endif // ESCENA_JUEGO_H
