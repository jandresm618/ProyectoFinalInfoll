#ifndef ESCENA_JUEGO_H
#define ESCENA_JUEGO_H

#include <QGraphicsScene>
#include <QPushButton>
#include "objeto_grafico.h"
#include "objeto_movil.h"


class Escena_Juego : public QGraphicsScene
{

public:    
    Escena_Juego();
    ~Escena_Juego();

    void setWindowProperty(int desk_w, int desk_h);

    void addObjetoGrafico(QString ruta,int x,int y,int w,int h);
    void addObjetoMovil(QString ruta,int x,int y,int xf,int yf,int w,int h);
    void doSome();

    /// SLOTS DE OBJETOS MOVILES
    void deleteFromScene();

private:
    Objeto_Grafico *personaje;
    Objeto_Movil *muni;

    /// CONTENEDORES DE OBJETOS
    vector<Objeto_Grafico *> objetosGraficos;
    vector<Objeto_Grafico *>::iterator itObjGra;
    vector<Objeto_Movil *> objetosMoviles;
    vector<Objeto_Movil *>::iterator itObjMov;

    int limit_x,limit_y;

};

#endif // ESCENA_JUEGO_H
