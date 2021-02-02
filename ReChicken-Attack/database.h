#ifndef DATABASE_H
#define DATABASE_H

#include <QDialog>

#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>


class DataBase
{
public:
    //CONSTRUCTOR
    DataBase();

    //CREAR TABLAS
    void crearTabladeUsuarios();
    void crearTabladeDatos();
    void crearTabladeRecords();

    //INSERTAR VALORES A LAS TABLAS
    void insertarUsuario();
    void insertarUsuario(QString user, QString pass);
    void insertarDatos();
    void insertarDatos(QString name, QString user, QString turno, QString level, QString vida,
                       QString score, QString num_jug, QString score_2, QString score_3, QString score_4);
    void insertarDatos(QString name, QString user, int turno, int level, int vida, int score,
                                 int num_jug, int score_2, int score_3, int score_4);
    void insertarRecord();
    void insertarRecord(QString name, QString high_score);

    //MUESTRA CON QDEBUG LOS DATOS EN LAS TABLAS

    void mostrarUsuarios();
    void mostrarDatos();
    void mostrarRecord();

    //VERIFICA QUE LOS DATOS ESTEN O NO

    bool validarUsuario(QString _name, QString _psswd);
    bool validarMatchName(QString name);


    //METODOS GET Y SET DE VARIABLES
    bool getUser() const;
    bool getPassword() const;

    void setUser(bool value);
    void setPassword(bool value);


    int level;

    bool turno;
    int vida_1,score_1;
    int vida_2,score_2;

    ~DataBase();



    QString getName_partida() const;
    void setName_partida(const QString &value);

    QString getName() const;
    void setName(const QString &value);

private:
    QSqlDatabase database;
    QString name;
    QString pass;
    QString name_partida;

    int high_score;
    bool user, password;

};

#endif // DATABASE_H
