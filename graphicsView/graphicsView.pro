QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DESTDIR = $$PWD/bin
#LIBS += -L $$PWD/bin/-lEeoShapeKit

SOURCES += \
    geometry.cpp \
    mainwindow.cpp \
    model.cpp \
    myTransform.cpp \
    main.cpp \
    myechelon.cpp \
    myequalechelon.cpp \
    myitem.cpp \
    myortechelon.cpp \
    myparallelogram.cpp \
    myrect.cpp \
    myrhombus.cpp \
    mysquare.cpp \
    shapebuilder.cpp \
    toolview.cpp \
    widget.cpp \
    mySize.cpp \

HEADERS += \
    geometry.h \
    mainwindow.h \
    model.h \
    myTransform.h \
    myechelon.h \
    myequalechelon.h \
    myitem.h \
    myortechelon.h \
    myparallelogram.h \
    myrect.h \
    myrhombus.h \
    mysquare.h \
    shapebuilder.h \
    toolview.h \
    widget.h \
    mySize.h \



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    mainwindow.ui \
    toolview.ui
