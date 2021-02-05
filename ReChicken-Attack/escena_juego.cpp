#include "escena_juego.h"

///         CONSTRUCTOR         ///
Escena_Juego::Escena_Juego()
{
    image = new QPixmap(":/personajes/imagenes/fondo.png");
    image2 = new QPixmap(":/personajes/imagenes/Fondo_Original1.png");

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
    if(backGround) painter->drawPixmap(QRectF(0,0,limit_x,limit_y),*image,image->rect());
    else painter->drawPixmap(QRectF(0,0,limit_x,limit_y),*image2,image2->rect());
}


///         AÑADIR OBJETOS GRAFICOS         ///
void Escena_Juego::addObjetoGrafico(QString ruta, int x, int y, int w, int h,bool main)
{
    if(main){
        ///DECLARACION DE OBJETO
        personaje = new Objeto_Grafico(ruta,x,y,w,h);
        ///ASIGNACION DE VALORES
        this->addItem(personaje);

    }else{
        explosiones = new Objeto_Grafico(ruta,x,y,w,h);
        ///ASIGNACION DE VALORES
        this->addItem(explosiones);
        objetosGraficos.push_back(explosiones);
    }
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
    if(move == 1) {
        muni->setMovParabolico(xf,yf,param,minMax);
        muni->setInverseMove();
    }   //Calcula velocidad y angulo inicial

    //qDebug()<<"No hay problemas con la inicializacion del movimiento";

    //ASIGNACION DE MOVIMIENTO SENOIDAL
    //muni->setMovSenoidal();

    /// INICIALIZACION DE OBJETO EN ESCENA
    this->addItem(muni);                //Se añade el objeto a la escena
    muni->startMove(time_move);                //Asigna valor de timeout para el movimiento
}

void Escena_Juego::addObjetoMovil(QString ruta, int x, int y, int v0, int angle, int move)
{
    ///CREACION DE OBJETO MOVIL
    muni = new Objeto_Movil(ruta,x,y,0,500,100,100,move);
    objetosMoviles.push_back(muni);     //Añadir objeto a la lista de objetos moviles
    muni->setVel(v0,angle);

    /// INICIALIZACION DE OBJETO EN ESCENA
    this->addItem(muni);                //Se añade el objeto a la escena
}

void Escena_Juego::explodeObject(int _x, int _y, int _w, int _h)
{
    muni = new Objeto_Movil(":/personajes/imagenes/explode.png",_x,_y,_w,_h);
}

///         FUNCION MOVIMIENTO DE PRUEBA         ///
void Escena_Juego::doSome()
{
    ///ASIGNACION DE VALORES
    personaje->set_Pos(personaje->getX()+50,personaje->getY());
}

void Escena_Juego::explode(Objeto_Movil *enem)
{
    int x,y;
    x=enem->getX();
//    y=enem->getY()-100;
    y=enem->getY();
    explosiones = new Objeto_Grafico(":/personajes/imagenes/explode.png",x,y,80,80);
    explosiones->setEscala(1.6);
    this->addItem(explosiones);
    objetosGraficos.push_back(explosiones);
}

void Escena_Juego::explodePlusPlus()
{
    if(!objetosGraficos.empty()){
        for(itObjGra=objetosGraficos.begin();itObjGra!=objetosGraficos.end();itObjGra++){
            if((*itObjGra)->cont > 15){
                //this->removeItem((*itObjGra));
                delete (*itObjGra);
                objetosGraficos.erase(itObjGra);
                return;
            }
            else {(*itObjGra)->cont++;}
        }
    }
}

int Escena_Juego::getHurt()
{
    return blood;
}

void Escena_Juego::pause()
{
    if(!objetosMoviles.empty()){
        for(itObjMov = objetosMoviles.begin();itObjMov != objetosMoviles.end();itObjMov++){
            (*itObjMov)->stop();
        }
    }
}

void Escena_Juego::start()
{
    if(!objetosMoviles.empty()){
        for(itObjMov = objetosMoviles.begin();itObjMov != objetosMoviles.end();itObjMov++){
            (*itObjMov)->startMove(time_move);
        }
    }
}

void Escena_Juego::restart()
{
    if(!objetosMoviles.empty()){
        for(itObjMov = objetosMoviles.begin();itObjMov != objetosMoviles.end();itObjMov++){
            (*itObjMov)->deleteObject();
        }
        objetosMoviles.clear();
    }
    if(!objetosGraficos.empty()){
        for(itObjGra = objetosGraficos.begin();itObjGra != objetosGraficos.end();itObjGra++){
            delete (*itObjGra);
        }
        objetosGraficos.clear();
    }
    score = 0;
    blood = 100;
}

void Escena_Juego::setHurt()
{
    blood -= 10;
}


///         ELIMINA LOS OBJETOS QUE ESTEN FUERA DE ESCENA´         ///
bool Escena_Juego::deleteFromScene()
{
    cont_1++;
    bool collides = false;
    int cont = 0,cont2 = 0;
    explodePlusPlus();
    if(!objetosMoviles.empty()){
        for(itObjMov = objetosMoviles.begin();itObjMov != objetosMoviles.end();itObjMov++,cont++){
            if((*itObjMov)->getOutOfScene()){
                collides = true;
                explode((*itObjMov));
                if(!(*itObjMov)->getLado()){
                    ///SE REDUCE LA VIDA DEL JUGADOR
                    this->setHurt();
                }
                if((*itObjMov) == objetosMoviles.at(cont)){
                    (*itObjMov)->deleteObject();
                    objetosMoviles.erase(itObjMov);
                }
                return collides;
            }
            else if((*itObjMov)->getY() > limit_y-200){
                (*itObjMov)->set_vel((*itObjMov)->get_velX(),-1*e*(*itObjMov)->get_velY(),
                                     (*itObjMov)->getX(),(*itObjMov)->getY()-10);
            }
            else{
                for (itObjMov2 = objetosMoviles.begin(),cont2=0;itObjMov2 != objetosMoviles.end();itObjMov2++,cont2++) {
                    /// Si es bala ///              ///Si es Enemigo///
                    if((*itObjMov)->getLado() && !(*itObjMov2)->getLado()){                        
                        if((*itObjMov)->collidesWithItem((*itObjMov2))
                                && ((*itObjMov2)->collidesWithItem((*itObjMov)))
                                /*|| (*itObjMov)->closeness((*itObjMov2),10)*/){
                            collides = true; setScorePlus();
                            explode((*itObjMov));
                            //this->explodeObject((*itObjMov)->getX(),(*itObjMov)->getY(),100,100);
                            (*itObjMov)->deleteObject();
                            objetosMoviles.erase(itObjMov);
                            (*itObjMov2)->deleteObject();
                            objetosMoviles.erase(itObjMov2);


                            return collides;
                        }
                    }
                }
            }
        }
    }
    return collides;

}

int Escena_Juego::getScore() const
{
    return score;
}

void Escena_Juego::setScore(int value)
{
    score = value;
}

void Escena_Juego::setScorePlus()
{
    score ++;
}

vector<Objeto_Movil *> Escena_Juego::getObjetosMoviles() const
{
    return objetosMoviles;
}

void Escena_Juego::setBackGround(bool value)
{
    backGround = value;
}

int Escena_Juego::getBlood() const
{
    return blood;
}

void Escena_Juego::setBlood(int value)
{
    blood = value;
}
