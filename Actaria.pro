QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += include/GUI
SOURCES += \
    src/GUI/entity.cpp \
    src/GUI/gamecontext.cpp \
    src/GUI/main.cpp \
    src/GUI/mainwindow.cpp \
    src/GUI/playerinfo.cpp \
    src/GUI/scene.cpp \
    src/GUI/scenecontext.cpp \
    src/GUI/trigger.cpp

HEADERS += \
    include/GUI/entity.h \
    include/GUI/gamecontext.h \
    include/GUI/mainwindow.h \
    include/GUI/playerinfo.h \
    include/GUI/scene.h \
    include/GUI/scenecontext.h \
    include/GUI/trigger.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
