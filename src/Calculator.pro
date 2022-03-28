QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
RC_ICONS = logo.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    calculator.cpp \
    compiler.cpp \
    constant.cpp \
    function.cpp \
    main.cpp \
    mainwindow.cpp \
    widgetaddconstant.cpp \
    widgetaddfunction.cpp \
    widgetaddparameter.cpp \
    widgetmodifyconstant.cpp \
    widgetmodifyfunction.cpp

HEADERS += \
    calculator.h \
    compiler.h \
    constant.h \
    function.h \
    mainwindow.h \
    widgetaddconstant.h \
    widgetaddfunction.h \
    widgetaddparameter.h \
    widgetmodifyconstant.h \
    widgetmodifyfunction.h

FORMS += \
    mainwindow.ui \
    widgetaddconstant.ui \
    widgetaddfunction.ui \
    widgetaddparameter.ui \
    widgetmodifyconstant.ui \
    widgetmodifyfunction.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
