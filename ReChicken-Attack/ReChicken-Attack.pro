QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    control_usuario.cpp \
    escena_juego.cpp \
    main.cpp \
    mainwindow.cpp \
    movimiento.cpp \
    objeto_grafico.cpp \
    objeto_movil.cpp

HEADERS += \
    control_usuario.h \
    escena_juego.h \
    mainwindow.h \
    movimiento.h \
    objeto_grafico.h \
    objeto_movil.h

FORMS += \
    control_usuario.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Imagenes.qrc
