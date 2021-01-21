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

    void showMainWindow();

private:
    Ui::Control_Usuario *ui;
    MainWindow *gameWindow;
    QPushButton *go2Main;
    QDesktopWidget *deskWidget;
    QGraphicsView *view;

    int desk_width,desk_height;

    bool firstTime = true;

};

#endif // CONTROL_USUARIO_H
