#-------------------------------------------------
#
# Project created by QtCreator 2015-05-12T12:01:17
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = acopioriback
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ofrecidos.cpp \
    compras.cpp \
    ventas.cpp \
    agregarofrecido.cpp \
    listadoclientes.cpp \
    agregarcliente.cpp \
    concretarofrecido.cpp \
    compraventa.cpp \
    detallecompraventa.cpp \
    agregarventa.cpp \
    nuevocomprador.cpp

HEADERS  += mainwindow.h \
    ofrecidos.h \
    compras.h \
    ventas.h \
    connection.h \
    agregarofrecido.h \
    listadoclientes.h \
    agregarcliente.h \
    concretarofrecido.h \
    compraventa.h \
    detallecompraventa.h \
    agregarventa.h \
    nuevocomprador.h

FORMS    += mainwindow.ui \
    ofrecidos.ui \
    compras.ui \
    ventas.ui \
    agregarofrecido.ui \
    listadoclientes.ui \
    agregarcliente.ui \
    concretarofrecido.ui \
    compraventa.ui \
    detallecompraventa.ui \
    agregarventa.ui \
    nuevocomprador.ui

DISTFILES +=
