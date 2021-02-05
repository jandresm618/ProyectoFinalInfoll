#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H
#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <QDebug>

#define G 9.81
#define DT 0.1
#define pi 3.141617


using namespace std;


class Movimiento
{
public:
    /// CONSTRUCTORES
    Movimiento();
    Movimiento(float _x,float _y,int xf,int yf);

    /// MOVIMIENTO RECTILINEO ACELERADO
    void setMUA();
    bool actualizarMUA();

    /// MOVIMIENTO SENOIDAL
    void setMovSeno();
    bool actualizarSeno();

    /// MOVIMIENTO RECTILINEO ACELERADO

    /// MOVIMIENTO PARABOLICO
    bool nParabolicos(float xf,float yf, float d, float factorImpacto);
    bool parabolico(float xf,float yf,int _v0,int _angle,float d, float factorImpacto);
    vector<float> parabolico(float timeStop,float x, float y,int _v0,int _angle);    
    float tiempoParabolico(float xf,float yf,float _angle,float _v0,float d, float factorImpacto);
    /// ACTUALIZACION DE VALORES
    bool actualizar(float dt);

    /// METODOS SET
    void setParametros(int cont);
    void setParamsMove(float v0,float angle);
    void set_vel(int _vx, int _vy, int _px, int _py);


    /// METODOS GET
    map<int,vector<float>> getParametros();
    vector<float> getBest(int param,bool minMax);
    int getPosBestMove(int param,bool minMax);
    float getX() const;
    float getY() const;

    /// IMPRESION DE VALORES
    void imprimirValoresImpacto();
    void imprimirVector(vector<float> vec);

    map<int, vector<float> > getLanzamientos() const;

    bool getLado() const;

    float getVx() const;

    float getVy() const;

    void setReverse();

private:
    bool lado; //Indicador de bando
    //false = Defensivo
                //true = Ofensivo

    float ymax = 0; //Variable Auxiliar
    float x = 0,y = 0;
    float px= 0,py= 0;
    int pfx, pfy;
    float vx= 0,vy= 0;
    float ax= 0,ay = G;
    float v0= 0;
    float v0x= 0,v0y= 0;
    float angulo= 0;
    float time= 0;
    float aux_v= 0,aux_sin= 0;
    float e1 = 1.5,e2 = 0.5;

    float t = 0;

    vector<float> parametrosLanzamiento;
    map<int,vector<float>> lanzamientos;
    map<int,vector<float>>::iterator it;

};

#endif // MOVIMIENTO_H
