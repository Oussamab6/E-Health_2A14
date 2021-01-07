QT       += core gui multimedia sql printsupport serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    EMPLOYE.cpp \
    arduino.cpp \
    connection.cpp \
    contrat.cpp \
    don.cpp \
    donneur.cpp \
    dossiermedical.cpp \
    health.cpp \
    machine.cpp \
 main.cpp \
    mainwindow.cpp \
    medicaments.cpp \
    partenaire.cpp \
    patient.cpp \
    qcustomplot.cpp \
    tableprinter.cpp \
    tache.cpp

HEADERS += \
    EMPLOYE.h \
    arduino.h \
    connection.h \
    contrat.h \
    don.h \
    donneur.h \
    dossiermedical.h \
    health.h \
    machine.h \
    mainwindow.h \
    medicaments.h \
    partenaire.h \
    patient.h \
    qcustomplot.h \
    tableprinter.h \
    tache.h

FORMS += \
    health.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Ressource.qrc \
    tanslate.qrc

DISTFILES +=
