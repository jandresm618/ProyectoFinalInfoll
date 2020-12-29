#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void comeBack();
    //void setControl(Control_Usuario *_control = nullptr);

private:
    Ui::MainWindow *ui;
    QPushButton *boton;

};
#endif // MAINWINDOW_H
