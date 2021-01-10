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
    Movimiento();
    Movimiento(float x,float y,int xf,int yf);
    bool actualizar(float dt);
    bool nParabolicos(float xf,float yf, float d, float factorImpacto);
    bool parabolico(float xf,float yf,int _v0,int _angle,float d, float factorImpacto);
    vector<float> parabolico(float timeStop,float x, float y,int _v0,int _angle);

    float tiempoParabolico(float xf,float yf,float _angle,float _v0,float d, float factorImpacto);
    void setParametros(int cont);
    map<int,vector<float>> getParametros();
    vector<float> getBest(int param,bool minMax);
    void imprimirValoresImpacto();
    void imprimirVector(vector<float> vec);

    int getPosBestMove(int param,bool minMax);

    float getX() const;

    float getY() const;

    void setParamsMove(float v0,float angle);

private:
    bool lado; //Indicador de bando
                //false = Defensivo
                //true = Ofensivo

    float ymax = 0; //Variable Auxiliar
    float x = 0,y = 0;
    float px= 0,py= 0;
    int pfx, pfy;
    float vx= 0,vy= 0;
    float ax= 0,ay= 0;
    float v0= 0;
    float v0x= 0,v0y= 0;
    float angulo= 0;
    float time= 0;
    float aux_v= 0,aux_sin= 0;
    vector<float> parametrosLanzamiento;
    map<int,vector<float>> lanzamientos;
    map<int,vector<float>>::iterator it;

};

#endif // MOVIMIENTO_H
