#include "objeto_movil.h"

Objeto_Movil::Objeto_Movil()
{

}

Objeto_Movil::Objeto_Movil(QString _ruta, int _x, int _y,int _xf,int _yf, int _w, int _h) : Objeto_Grafico(_ruta,_x,_y,_w,_h)
{
    ///DECLARACION DE OBJETOS
    movimiento = new Movimiento(_x,_y,_xf,_yf); //De derecha a Izquierda
    time_move = new QTimer;

    ///CONEXION DE SIGNAL & SLOT
    connect(time_move,&QTimer::timeout,this,&Objeto_Movil::updatePos);
}

Objeto_Movil::~Objeto_Movil()
{
    ///ELIMINACION DE MEMORIA
    delete movimiento;
    delete time_move;
}

QRectF Objeto_Movil::boundingRect() const
{
    ///RETORNO DE OBJETO
    return QRectF(0,0,this->getW(),this->getH());
}

void Objeto_Movil::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    ///ASIGNACION DE VALORES
    painter->drawPixmap(boundingRect(),*(this->getImage()),this->getImage()->rect());
}

void Objeto_Movil::getVel(int xf, int yf,int param,bool minMax)
{
    ///DECLARACION DE VARIABLES AUXILIARES LOCALES
    vector<float> params;                                //Vector de Parametros de Lanzamiento
    int d = sqrt(pow(xf-this->getX(),2)+pow(yf-this->getY(),2)); //Distancia entre Objetos                              //Porcentaje de Impacto

    ///ASIGNACION DE VALORES
    movimiento->nParabolicos(xf,yf,d,factorImpacto);    //Se calculan las velocidades de lanzamiento

    ///DEBUG
    //qDebug()<<"GEtting Best...";

    ///ASIGNACION DE VALORES
    params = movimiento->getBest(param,minMax);         //Parametros para lanzamiento con altura minima
    angle = params.at(3);
    v0 = params.at(4);
    movimiento->setParamsMove(v0,angle);
}

void Objeto_Movil::setVel(float _v0, float _angle)
{
    ///ASIGNACION DE VALORES
    angle = _angle;
    v0 = _v0;
    movimiento->setParamsMove(v0,angle);
}

void Objeto_Movil::startMove(int msec)
{
    ///ASIGNACION DE VALORES
    time_move->start(msec);
}

void Objeto_Movil::stopMove()
{
    ///ASIGNACION DE VALORES
    time_move->stop();
}

void Objeto_Movil::updatePos()
{
    ///ASIGNACION DE VALORES

    if (movimiento->actualizar(0.1)) qDebug()<<"Eliminando de escena";
    this->set_Pos(movimiento->getX(),movimiento->getY());
}

