QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    mythread.cpp \
    singin.cpp

HEADERS += \
    mainwindow.h \
    mythread.h \
    singin.h

FORMS += \
    mainwindow.ui \
    singin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc

QMAKE_CXXFLAGS += -std=c++0x -pthread
QMAKE_CFLAGS += -std=gnu++0x -pthread
LIBS += -pthread
