#include "control_usuario.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Control_Usuario wind;
    //MainWindow w;
    //w.show();
    wind.show();
    return a.exec();
}
