#-------------------------------------------------
#
# Project created by QtCreator 2014-12-07T20:45:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProyectoVisionEstereo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    capturarealizada.cpp \
    rectificar.cpp \
    rectificacion.cpp \
    mapadisparidad.cpp \
    distanciasnavegacion.cpp \
    calibrarcamaraest.cpp

HEADERS  += mainwindow.h \
    capturarealizada.h \
    rectificar.h \
    rectificacion.h \
    mapadisparidad.h \
    distanciasnavegacion.h \
    calibrarcamaraest.h

FORMS    += mainwindow.ui \
    capturarealizada.ui \
    rectificar.ui \
    rectificacion.ui \
    mapadisparidad.ui \
    distanciaobjetos.ui \
    distanciasnavegacion.ui \
    calibrarcamaraest.ui

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_ml
LIBS += -lopencv_video
LIBS += -lopencv_features2d
LIBS += -lopencv_calib3d
LIBS += -lopencv_objdetect
LIBS += -lopencv_contrib
LIBS += -lopencv_legacy
LIBS += -lopencv_flann
LIBS += -lopencv_nonfree
