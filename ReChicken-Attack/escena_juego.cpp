#include "escena_juego.h"

///         CONSTRUCTOR         ///
Escena_Juego::Escena_Juego()
{

}

Escena_Juego::~Escena_Juego()
{
    ///ELIMINACION DE MEMORIA
    delete personaje;
    delete muni;
}

void Escena_Juego::setWindowProperty(int desk_w, int desk_h)
{
    limit_x = desk_w;
    limit_y = desk_h;
    setSceneRect(0,0,desk_w,desk_h);
}

void Escena_Juego::addObjetoGrafico(QString ruta, int x, int y, int w, int h)
{
    ///DECLARACION DE OBJETO
    personaje = new Objeto_Grafico(ruta,x,y,w,h);
    ///ASIGNACION DE VALORES
    this->addItem(personaje);
}

void Escena_Juego::addObjetoMovil(QString ruta, int x, int y,int xf,int yf, int w, int h)
{
    ///DECLARACION DE VARIABLES AUXILIARES LOCALES
    int param = 5;              //Parametro Altura Maxima
    bool minMax = true;         //Minimo Valor del Parametro

    ///ASIGNACION DE VALORES
    muni = new Objeto_Movil(ruta,x,y,limit_x,limit_y,w,h);
    objetosMoviles.push_back(muni);
    qDebug()<<"Get Parametros";
    muni->getVel(xf,yf,param,minMax);
    qDebug()<<"Añadiendo a la escena";
    this->addItem(muni);
    qDebug()<<"Empezando el movimiento";
    muni->startMove(50);
}

void Escena_Juego::doSome()
{
    ///ASIGNACION DE VALORES
    personaje->set_Pos(personaje->getX()+50,personaje->getY());
}

void Escena_Juego::deleteFromScene()
{
    int cont = 0;
    if(!objetosMoviles.empty()){
        for(itObjMov = objetosMoviles.begin();itObjMov != objetosMoviles.end();itObjMov++,cont++){
            if((*itObjMov)->getOutOfScene()){
                qDebug()<<"Fuera de Escena, Eliminando "<<cont;
                (*itObjMov)->deleteObject();
                objetosMoviles.erase(itObjMov);
                break;
            }
        }
    }

}
