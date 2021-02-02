#include "escena_juego.h"

///         CONSTRUCTOR         ///
Escena_Juego::Escena_Juego()
{
    image = new QPixmap(":/personajes/imagenes/fondo.png");
}

///         DESTRUCTOR         ///
Escena_Juego::~Escena_Juego()
{
    ///ELIMINACION DE MEMORIA
    delete personaje;
    delete muni;
}

void Escena_Juego::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
    //qDebug()<<"x "<<event->scenePos().x()<<" y "<<event->scenePos().y();
}

///         PROPIEDADES DE VENTANA         ///
void Escena_Juego::setWindowProperty(int desk_w, int desk_h)
{
    limit_x = desk_w;
    limit_y = desk_h;
    setSceneRect(0,0,desk_w,desk_h);
}

void Escena_Juego::drawBackground(QPainter *painter, const QRectF &exposed)
{
    painter->drawPixmap(QRectF(0,0,limit_x,limit_y),*image,image->rect());
}

///         ESTABLECER ESCENA ARCADE         ///
void Escena_Juego::arcadeDesing()
{
    int x_1 = 100, y_1 = 500;
    int w_1 = 100, h_1 = 100;
    QString path_1 = ":/personajes/imagenes/mario.png";
    addObjetoGrafico(path_1,x_1,y_1,w_1,h_1);
}

///         AÑADIR OBJETOS GRAFICOS         ///
void Escena_Juego::addObjetoGrafico(QString ruta, int x, int y, int w, int h)
{
    ///DECLARACION DE OBJETO
    personaje = new Objeto_Grafico(ruta,x,y,w,h);
    ///ASIGNACION DE VALORES
    this->addItem(personaje);
    objetosGraficos.push_back(personaje);
}

///         AÑADIR OBJETOS GRAFICOS MOVILES         ///
void Escena_Juego::addObjetoMovil(QString ruta, int x, int y,int xf,int yf, int w, int h, int move)
{
    ///DECLARACION DE VARIABLES AUXILIARES LOCALES
    int param = 5;              //Parametro Altura Maxima
    bool minMax = true;         //Minimo Valor del Parametro

    ///CREACION DE OBJETO MOVIL
    muni = new Objeto_Movil(ruta,x,y,xf,yf,w,h,move);
    objetosMoviles.push_back(muni);     //Añadir objeto a la lista de objetos moviles

    /// ASIGNACION DE MOVIMIENTO PARABOLICO
    if(move == 1) muni->setMovParabolico(xf,yf,param,minMax);   //Calcula velocidad y angulo inicial

    //qDebug()<<"No hay problemas con la inicializacion del movimiento";

    //ASIGNACION DE MOVIMIENTO SENOIDAL
    //muni->setMovSenoidal();

    /// INICIALIZACION DE OBJETO EN ESCENA
    this->addItem(muni);                //Se añade el objeto a la escena
    muni->startMove(60);                //Asigna valor de timeout para el movimiento
}

///         FUNCION MOVIMIENTO DE PRUEBA         ///
void Escena_Juego::doSome()
{
    ///ASIGNACION DE VALORES
    personaje->set_Pos(personaje->getX()+50,personaje->getY());
}

int Escena_Juego::getHurt()
{
    return blood;
}

void Escena_Juego::setHurt()
{
    blood -= 10;
}


///         ELIMINA LOS OBJETOS QUE ESTEN FUERA DE ESCENA´         ///
bool Escena_Juego::deleteFromScene()
{
    bool collides = false;
    int cont = 0,cont2 = 0;
    //qDebug()<<"Verificando Chequeo\n";
    if(!objetosMoviles.empty()){
        //qDebug()<<"Listo Para Chequeo de objetos";
        for(itObjMov = objetosMoviles.begin();itObjMov != objetosMoviles.end();itObjMov++,cont++){
            if(collides) qDebug()<<"OJOOOOOOOOOOOOO";
            //qDebug()<<"Iterador 1 asignado";
            if((*itObjMov)->getOutOfScene()){
                collides = true;
                //qDebug()<<"Eliminando por Limite";
                if(!(*itObjMov)->getLado()){
                    ///SE REDUCE LA VIDA DEL JUGADOR
                    this->setHurt();
                    // qDebug()<<"Vida: "<<getHurt();
                }
                if((*itObjMov) == objetosMoviles.at(cont)){
                    (*itObjMov)->deleteObject();
                    //qDebug()<<"Objeto a Eliminar"<<&(objetosMoviles.at(cont));
                    objetosMoviles.erase(itObjMov);
                }
                return collides;
            }
            else{
                //qDebug()<<"Eliminando por colision";
                for (itObjMov2 = objetosMoviles.begin(),cont2=0;itObjMov2 != objetosMoviles.end();itObjMov2++,cont2++) {
                    /// Si es bala ///              ///Si es Enemigo///
                    if(collides) qDebug()<<"OJOOOOOOOOOOOOO";
                    if((*itObjMov)->getLado() && !(*itObjMov2)->getLado()){
                        //qDebug()<<"Detectando Colision de objeto "<<cont+1<<"  con objeto "<<cont2+1;
                        if((*itObjMov)->collidesWithItem((*itObjMov2))
                                /*|| (*itObjMov)->closeness((*itObjMov2),10)*/){
                            collides = true; setScore();
                            //qDebug()<<"Score: "<<getScore();

                            objetosMoviles.erase(itObjMov);
                            objetosMoviles.erase(itObjMov2);
                            delete (*itObjMov);
                            delete (*itObjMov2);
                            /*
                            if((*itObjMov) == objetosMoviles.at(cont)){
                                qDebug()<<"Iguales 1";
                                objetosMoviles.erase(itObjMov);
                            }
                            if((*itObjMov2) == objetosMoviles.at(cont2)){
                                qDebug()<<"Iguales 2";
                                objetosMoviles.erase(itObjMov2);
                            }*/



                            return collides;
                        }
                    }//qDebug()<<"Iteracion Interna "<<cont2;
                }
            }
            //qDebug()<<"Iteracion "<<cont;
        }
    }
    /*else{if(this->items().size()>1) qDebug()<<"Aun hay elementos en escena";}*/

    return collides;

}

int Escena_Juego::getScore() const
{
    return score;
}

void Escena_Juego::setScore()
{
    score ++;
}
