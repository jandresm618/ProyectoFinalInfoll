#include "database.h"

DataBase::DataBase()
{
    QString nombre;
    nombre.append("database_Chicken_Attack.sqlite");
    database= QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(nombre);

    if(database.open())qDebug()<<"Base de datos creada.";
    else qDebug()<<"Error al crear la base de datos";

    crearTabladeUsuarios();
    crearTabladeDatos();
    crearTabladeEnemigos();
    crearTabladeRecords();
    mostrarUsuarios();

}

void DataBase::crearTabladeUsuarios()
{

    //Name-Password
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS usuarios("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "nombre VARCHAR(100),"
                    "contraseña VARCHAR(100)"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);
    if(crear.exec()){
        qDebug()<<"Se ha creado la tabla de usuarios.";
    }
    else{
        qDebug()<<"No se ha creado la tabla de usuarios.";

        qDebug()<<"ERROR"<<crear.lastError();
    }
}

void DataBase::crearTabladeDatos()
{
    //Name-Vida-Score-Num_jug-turno
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS data("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "nombre VARCHAR(100),"
                    "user VARCHAR(100),"
                    "arcade BIT,"
                    "nivel INTEGER,"
                    "turno INTEGER,"
                    "vida INTEGER,"
                    "segundos INTEGER,"
                    "score_uno INTEGER,"
                    "score_dos INTEGER,"
                    "ammo_uno INTEGER,"
                    "ammo_dos INTEGER,"
                    "ammo_tres INTEGER"

                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);
    if(crear.exec()){
        qDebug()<<"Se ha creado la tabla de DATOS.";
    }
    else{
        qDebug()<<"No se ha creado la tabla de DATOS.";
        qDebug()<<"ERROR"<<crear.lastError();
    }
}

void DataBase::crearTabladeEnemigos()
{
    //Name-Vida-Score-Num_jug-turno
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS enemy("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "nombre VARCHAR(100),"
                    "user VARCHAR(100),"
                    "x INTEGER,"
                    "y INTEGER,"
                    "vo INTEGER,"
                    "angulo INTEGER,"
                    "move INTEGER"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);
    if(crear.exec()){
        qDebug()<<"Se ha creado la tabla de ENEMIGOS.";
    }
    else{
        qDebug()<<"No se ha creado la tabla de ENEMIGOS.";
        qDebug()<<"ERROR"<<crear.lastError();
    }
}

void DataBase::crearTabladeRecords()
{
     //Name-Puntaje
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS record("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "nombre VARCHAR(100),"
                    "best_score INTEGER,"
                    "player INTEGER"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);
    if(crear.exec()){
        qDebug()<<"Se ha creado la tabla de usuarios.";
    }
    else{
        qDebug()<<"No se ha creado la tabla de usuarios.";
        qDebug()<<"ERROR"<<crear.lastError();
    }
}

void DataBase::insertarUsuario()
{
    QString consulta;
    consulta.append("INSERT INTO usuarios("
                    "nombre,"
                    "contraseña"
                    ")"
                    "VALUES("
                    "'"+name+"',"
                    "'"+pass+"'"
                    ");");
    QSqlQuery insertar;
    qDebug()<<consulta;
    insertar.prepare(consulta);
    if(insertar.exec()){
        qDebug()<<"Se ha ingresado el usuario correctamente.";
    }
    else {
        qDebug()<<"El usuario no se ha ingresado";
        qDebug()<<"ERROR!"<<insertar.lastError();
    }
}

void DataBase::insertarUsuario(QString user, QString passw)
{
    QString consulta;
    consulta.append("INSERT INTO usuarios("
                    "nombre,"
                    "contraseña"
                    ")"
                    "VALUES("
                    "'"+user+"',"
                    "'"+passw+"'"
                    ");");
    QSqlQuery insertar;
    qDebug()<<consulta;
    insertar.prepare(consulta);
    if(insertar.exec()){
        qDebug()<<"Se ha ingresado el usuario correctamente.";
    }
    else {
        qDebug()<<"El usuario no se ha ingresado";
        qDebug()<<"ERROR!"<<insertar.lastError();
    }

}
bool DataBase::insertarDatos(QString match_name,QString username,bool arcade,int nivel,int player,int blood,int gameTime,int score_1,int score_2,int ammo1,int ammo2,int ammo3)
{
    bool success = false;
    QString consulta;
    consulta.append("INSERT INTO data("
                    "nombre ,"
                    "user ,"
                    "arcade ,"
                    "nivel ,"
                    "turno ,"
                    "vida ,"
                    "segundos ,"
                    "score_uno ,"
                    "score_dos ,"
                    "ammo_uno ,"
                    "ammo_dos ,"
                    "ammo_tres "
                    ")"
                    "VALUES("
                    "'"+match_name+"',"
                    "'"+username+"',"
                    "'"+QString::number(arcade)+"',"
                    "'"+QString::number(nivel)+"',"
                    "'"+QString::number(player)+"',"
                    "'"+QString::number(blood)+"',"
                    "'"+QString::number(gameTime)+"',"
                    "'"+QString::number(score_1)+"',"
                    "'"+QString::number(score_2)+"',"
                    "'"+QString::number(ammo1)+"',"
                    "'"+QString::number(ammo2)+"',"
                    "'"+QString::number(ammo3)+"'"
                    ")");
    QSqlQuery insertar;
    qDebug()<<consulta;
    insertar.prepare(consulta);
    if(insertar.exec()){
        success = true;
        qDebug()<<"Se ha ingresado los DATOS correctamente.";
    }
    else {
        qDebug()<<"El usuario no se ha ingresado";
        qDebug()<<"ERROR!"<<insertar.lastError();
    }
    return success;
}

bool DataBase::insertarEnemigos(QString match_name,QString username,int x, int y, int v0,int angle,int move)
{
    bool success = false;
    QString consulta;

    consulta.append("INSERT INTO enemy("
                    "nombre ,"
                    "user ,"
                    "x ,"
                    "y ,"
                    "vo ,"
                    "angulo ,"
                    "move "
                    ")"
                    "VALUES("
                    "'"+match_name+"',"
                    "'"+username+"',"
                    "'"+QString::number(x)+"',"
                    "'"+QString::number(y)+"',"
                    "'"+QString::number(v0)+"',"
                    "'"+QString::number(angle)+"',"
                    "'"+QString::number(move)+"'"
                    ")");
    QSqlQuery insertar;
    qDebug()<<consulta;
    insertar.prepare(consulta);
    if(insertar.exec()){
        qDebug()<<"Se ha ingresado los ENEMIGOS correctamente.";
        success = true;
    }
    else {
        qDebug()<<"El usuario no se ha ingresado";
        qDebug()<<"ERROR!"<<insertar.lastError();
    }
    return success;
}


void DataBase::insertarRecord()
{
    QString consulta;
    consulta.append("INSERT INTO record("
                    "nombre ,"
                    "best_score "
                    ")"
                    "VALUES("
                    "'"+name+"',"
                    "'"+high_score+"'"
                    ");");
    QSqlQuery insertar;
    qDebug()<<consulta;
    insertar.prepare(consulta);
    if(insertar.exec()){
        qDebug()<<"Se ha ingresado el usuario correctamente.";
    }
    else {
        qDebug()<<"El usuario no se ha ingresado";
        qDebug()<<"ERROR!"<<insertar.lastError();
    }
}
void DataBase::insertarRecord(QString name,QString high_score, QString player)
{
    QString consulta;
    consulta.append("INSERT INTO record("
                    "nombre ,"
                    "best_score ,"
                    "player "
                    ")"
                    "VALUES("
                    "'"+name+"',"
                    "'"+high_score+"',"
                    "'"+player+"'"
                    ");");
    QSqlQuery insertar;
    qDebug()<<consulta;
    insertar.prepare(consulta);
    if(insertar.exec()){
        qDebug()<<"Se ha ingresado el record correctamente.";
    }
    else {
        qDebug()<<"El record no se ha ingresado";
        qDebug()<<"ERROR!"<<insertar.lastError();
    }
}
void DataBase::mostrarUsuarios()
{
    int i=0;
    QString consulta;
    consulta.append("SELECT * FROM usuarios"
                    );
    QSqlQuery mostrar;
    mostrar.prepare(consulta);
    if(mostrar.exec()){
        qDebug()<<"Se ha mostrado el usuario correctamente.";
    }
    else {
        qDebug()<<"El usuario no se ha mostrado";
        qDebug()<<"ERROR!"<<mostrar.lastError();
    }
    while (mostrar.next()) {
        qDebug()<<mostrar.value(1).toByteArray().constData();
        qDebug()<<" == ";
        qDebug()<<mostrar.value(2).toByteArray().constData();
    }
//    ui->tableWidget->setRowCount(0);
//    while (mostrar.next()) {
//        qDebug()<<mostrar.value(1).toByteArray().constData();
//        ui->tableWidget->insertRow(i);
//        ui->tableWidget->setItem(i,0,new QTableWidgetItem("que pasa"));
    //    }
}

vector<QString> DataBase::mostrarDatos(QString match_name,QString username)
{
    QString r1,r2;
    vector<QString> data;
    QString consulta;
    consulta.append("SELECT * FROM data"
                    );
    QSqlQuery mostrar;
    mostrar.prepare(consulta);
    if(mostrar.exec()){
        qDebug()<<"Se ha mostrado el usuario correctamente.";
    }
    else {
        qDebug()<<"El usuario no se ha mostrado";
        qDebug()<<"ERROR!"<<mostrar.lastError();
    }
    while (mostrar.next()) {
        r1 = mostrar.value(1).toByteArray().constData();
        r2 = mostrar.value(2).toByteArray().constData();
        if((match_name == r1) && (username == r2)){
            data.push_back(mostrar.value(3).toByteArray().constData());
            data.push_back(mostrar.value(4).toByteArray().constData());
            data.push_back(mostrar.value(5).toByteArray().constData());
            data.push_back(mostrar.value(6).toByteArray().constData());
            data.push_back(mostrar.value(7).toByteArray().constData());
            data.push_back(mostrar.value(8).toByteArray().constData());
            data.push_back(mostrar.value(9).toByteArray().constData());
            data.push_back(mostrar.value(10).toByteArray().constData());
            data.push_back(mostrar.value(11).toByteArray().constData());
            data.push_back(mostrar.value(12).toByteArray().constData());

            qDebug()<<"nombre de partida "<<mostrar.value(1).toByteArray().constData();
            qDebug()<<"user "<<mostrar.value(2).toByteArray().constData();
            qDebug()<<"arcade "<<mostrar.value(3).toByteArray().constData();
            qDebug()<<"nivel "<<mostrar.value(4).toByteArray().constData();
            qDebug()<<"turno "<<mostrar.value(5).toByteArray().constData();
            qDebug()<<"vida "<<mostrar.value(6).toByteArray().constData();
            qDebug()<<"segundos "<<mostrar.value(7).toByteArray().constData();
            qDebug()<<" score_uno "<<mostrar.value(8).toByteArray().constData();
            qDebug()<<"score_dos "<<mostrar.value(9).toByteArray().constData();
            qDebug()<<"ammo_uno "<<mostrar.value(10).toByteArray().constData();
            qDebug()<<"ammo_dos "<<mostrar.value(11).toByteArray().constData();
            qDebug()<<"ammo_tres "<<mostrar.value(12).toByteArray().constData();
        }

    }
    return data;
}

vector<QString> DataBase::mostrarEnemigos(QString match_name, QString username)
{
    QString r1,r2;
    vector<QString> enemys;
    QString consulta;
    consulta.append("SELECT * FROM enemy"
                    );
    QSqlQuery mostrar;
    mostrar.prepare(consulta);
    if(mostrar.exec()){
        qDebug()<<"Se ha mostrado el usuario correctamente.";
    }
    else {
        qDebug()<<"El usuario no se ha mostrado";
        qDebug()<<"ERROR!"<<mostrar.lastError();
    }
    while (mostrar.next()) {
        r1 = mostrar.value(1).toByteArray().constData();
        r2 = mostrar.value(2).toByteArray().constData();
        if((match_name == r1) && (username == r2)){
            enemys.push_back(mostrar.value(3).toByteArray().constData());
            enemys.push_back(mostrar.value(4).toByteArray().constData());
            enemys.push_back(mostrar.value(5).toByteArray().constData());
            enemys.push_back(mostrar.value(6).toByteArray().constData());
            enemys.push_back(mostrar.value(7).toByteArray().constData());

            qDebug()<<"nombre de partida "<<mostrar.value(1).toByteArray().constData();
            qDebug()<<"user "<<mostrar.value(2).toByteArray().constData();
            qDebug()<<"x "<<mostrar.value(3).toByteArray().constData();
            qDebug()<<"y "<<mostrar.value(4).toByteArray().constData();
            qDebug()<<"v0 "<<mostrar.value(5).toByteArray().constData();
            qDebug()<<"angle "<<mostrar.value(6).toByteArray().constData();
            qDebug()<<"move "<<mostrar.value(7).toByteArray().constData();
        }
    }
    return enemys;
}

vector<QString> DataBase::mostrarRecord()
{
    vector<QString> data;
    QString r1,r2,r3;
    QString consulta;
    consulta.append("SELECT * FROM record"
                    );
    QSqlQuery mostrar;
    mostrar.prepare(consulta);
    if(mostrar.exec()){
        qDebug()<<"Se ha mostrado el usuario correctamente.";
    }
    else {
        qDebug()<<"El usuario no se ha mostrado";
        qDebug()<<"ERROR!"<<mostrar.lastError();
    }
    while (mostrar.next()) {
        r1 = mostrar.value(1).toByteArray().constData();
        data.push_back(r1);
        r2 = mostrar.value(2).toByteArray().constData();
        data.push_back(r2);
        r2 = mostrar.value(3).toByteArray().constData();
        data.push_back(r3);
        qDebug()<<r1<<" - "<<r2<<" - "<<r3;


    }
    return data;
}

vector<QString> DataBase::mostrarPartidas(QString username)
{
    QString r1,r2,r = "";
    vector<QString> data;
    QString consulta;
    consulta.append("SELECT * FROM data"
                    );
    QSqlQuery mostrar;
    mostrar.prepare(consulta);
    if(mostrar.exec()){
        qDebug()<<"Se ha mostrado el usuario correctamente.";
    }
    else {
        qDebug()<<"El usuario no se ha mostrado";
        qDebug()<<"ERROR!"<<mostrar.lastError();
    }
    while (mostrar.next()) {
        r2 = mostrar.value(2).toByteArray().constData(); //Nombre de usuario
        if((username == r2)){
            r1 = mostrar.value(1).toByteArray().constData(); //Nombre Partida
            if(r1 != r){data.push_back(r1);r = r1;}
        }

    }
    return data;
}

bool DataBase::validarUsuario(QString _name, QString _psswd)
{
    QString consulta;
    bool exist=false;
    consulta.append("SELECT * FROM usuarios"
                    );
    QSqlQuery mostrar;
    mostrar.prepare(consulta);
    if(mostrar.exec()){
        qDebug()<<"Se ha mostrado el usuario correctamente.";
    }
    else {
        qDebug()<<"El usuario no se ha mostrado";
        qDebug()<<"ERROR!"<<mostrar.lastError();
    }
    while(mostrar.next()){
        if(mostrar.value(1).toByteArray().constData()==_name){
            user=true;
            name=_name;
            qDebug()<<"coincide el usuario";
            if(mostrar.value(2).toByteArray().constData()==_psswd){
                qDebug()<<mostrar.value(2).toByteArray().constData();
                qDebug()<<"vs";
                qDebug()<<_psswd;

                password=true;  //Devuelve true si el usuario es correcto
                             //Falso otherwise
            }
        }
    }
    if(user & password)exist=true;
    qDebug()<<"USUARIO VALIDADO";
    return exist;
}

bool DataBase::validarMatchName(QString name)
{
    //Verifica si en la tabla esta disponible el nombre
    QString consulta;
    bool able=true;
    consulta.append("SELECT * FROM data"
                    );
    QSqlQuery mostrar;
    mostrar.prepare(consulta);
    if(mostrar.exec()){
        qDebug()<<"Se ha mostrado el usuario correctamente.";
    }
    else {
        qDebug()<<"El usuario no se ha mostrado";
        qDebug()<<"ERROR!"<<mostrar.lastError();
    }
    while(mostrar.next()){
        if(mostrar.value(1).toByteArray().constData()==name){
            able=false;
            qDebug()<<"Nombre no disponible";
        }        
    }
//    if(able){
//        qDebug()<<"Nombre disponible";
//        name_partida=name;
//    }

    return able;
}


DataBase::~DataBase()
{
}

QString DataBase::getName_partida() const
{
    return name_partida;
}

void DataBase::setName_partida(const QString &value)
{
    name_partida = value;
}

QString DataBase::getName() const
{
    return name;
}

void DataBase::setName(const QString &value)
{
    name = value;
}

bool DataBase::getUser() const
{
    return user;
}

void DataBase::setUser(bool value)
{
    user = value;
}

bool DataBase::getPassword() const
{
    return password;
}

void DataBase::setPassword(bool value)
{
    password = value;
}
