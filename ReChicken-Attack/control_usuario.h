#ifndef CONTROL_USUARIO_H
#define CONTROL_USUARIO_H

#include <QDialog>
#include <QDesktopWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QSpinBox>
#include "mainwindow.h"
#include "database.h"

namespace Ui {
class Control_Usuario;
}

class Control_Usuario : public QDialog
{
    Q_OBJECT

public:
    explicit Control_Usuario(QWidget *parent = nullptr);
    ~Control_Usuario();

    ///FUNCIONES
    void crearObjetos();
    void hideItems();
    void disconnectAll();

    ///DISEÑO DE VENTANA
    void welcomeWindow();
    void setCredentialsWindow();
    void setMenuWindow();
    void loadGameWindow();
    void recordsWindow();
    void setMatchNameWindow();
    void matchNameWindow();


    ///Eventos de Teclado
    void keyPressEvent(QKeyEvent *event);

    ///SLOTS BOTONES
    void showMainWindow();   
    void setArcade();
    void setMultiplayer();
    void logIn();
    void signIn();
    void validateUser();
    void createUser();
    void startGame();
    void loadDataGame();

    void printVector(vector<QString> vec);



private:
    Ui::Control_Usuario *ui;
    MainWindow *gameWindow;
    QDesktopWidget *deskWidget;
    DataBase *database;

    QPushButton *boton1;
    QPushButton *boton2;
    QPushButton *boton3;
    QPushButton *boton4;
    QPushButton *boton5;

    QLabel *label1;
    QLabel *label2;
    QLabel *label3;

    QLineEdit *line_Edit1;
    QLineEdit *line_Edit2;
    QLineEdit *line_Edit3;
    QSpinBox *spin_box1;

    QTableWidget *table_widget;

    int desk_width,desk_height;
    QString user_name ;
;

    bool arcade = true;
    bool newUser = true;

};

#endif // CONTROL_USUARIO_H
