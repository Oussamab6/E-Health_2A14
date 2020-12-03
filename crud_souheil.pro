QT       += core gui sql
QT +=sql
QT       += core gui multimedia multimediawidgets printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connecion.cpp \
    emploi_du_temps.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindow2.cpp \
    qcustomplot.cpp \
    reservation.cpp \
    statistique.cpp

HEADERS += \
    connecion.h \
    emploi_du_temps.h \
    mainwindow.h \
    mainwindow2.h \
    qcustomplot.h \
    reservation.h \
    statistique.h

FORMS += \
    mainwindow.ui \
    mainwindow2.ui \
    statistique.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
