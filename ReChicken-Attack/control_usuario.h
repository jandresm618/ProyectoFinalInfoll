#ifndef CONTROL_USUARIO_H
#define CONTROL_USUARIO_H

#include <QDialog>
#include <QDesktopWidget>
#include "mainwindow.h"

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

    ///DISEÑO DE VENTANA
    void setCredentialsWindow();
    void setMenuWindow();
    void setMatchNameWindow();


    ///Eventos de Teclado
    void keyPressEvent(QKeyEvent *event);

    ///SLOTS BOTONES
    void showMainWindow();
    void showNewMainWindow();    
    void setArcade();
    void setMultiplayer();



private:
    Ui::Control_Usuario *ui;
    MainWindow *gameWindow;
    QDesktopWidget *deskWidget;
    QGraphicsView *view;

    QPushButton *boton1;
    QPushButton *boton2;
    QPushButton *boton3;

    int desk_width,desk_height;

    bool firstTime = true;
    bool arcade = true;

};

#endif // CONTROL_USUARIO_H
