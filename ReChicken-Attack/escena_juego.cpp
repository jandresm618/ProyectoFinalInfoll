#include "escena_juego.h"

///         CONSTRUCTOR         ///
Escena_Juego::Escena_Juego()
{

}

///         DESTRUCTOR         ///
Escena_Juego::~Escena_Juego()
{
    ///ELIMINACION DE MEMORIA
    delete personaje;
    delete muni;
}

///         PROPIEDADES DE VENTANA         ///
void Escena_Juego::setWindowProperty(int desk_w, int desk_h)
{
    limit_x = desk_w;
    limit_y = desk_h;
    setSceneRect(0,0,desk_w,desk_h);
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
void Escena_Juego::addObjetoMovil(QString ruta, int x, int y,int xf,int yf, int w, int h)
{
    ///DECLARACION DE VARIABLES AUXILIARES LOCALES
    int param = 5;              //Parametro Altura Maxima
    bool minMax = true;         //Minimo Valor del Parametro

    ///CREACION DE OBJETO MOVIL
    muni = new Objeto_Movil(ruta,x,y,limit_x,limit_y,w,h);
    objetosMoviles.push_back(muni);     //Añadir objeto a la lista de objetos moviles

    /// ASIGNACION DE MOVIMIENTO PARABOLICO
    muni->setMovParabolico(xf,yf,param,minMax);   //Calcula velocidad y angulo inicial

    //ASIGNACION DE MOVIMIENTO SENOIDAL
    //muni->setMovSenoidal();

    /// INICIALIZACION DE OBJETO EN ESCENA
    this->addItem(muni);                //Se añade el objeto a la escena
    muni->startMove(50);                //Asigna valor de timeout para el movimiento
}

///         FUNCION MOVIMIENTO DE PRUEBA         ///
void Escena_Juego::doSome()
{
    ///ASIGNACION DE VALORES
    personaje->set_Pos(personaje->getX()+50,personaje->getY());
}

///         ELIMINA LOS OBJETOS QUE ESTEN FUERA DE ESCENA´         ///
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
