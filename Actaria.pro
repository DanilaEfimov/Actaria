QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += include
SOURCES += \
    src/GUI/codeeditor.cpp \
    src/Entities/counter.cpp \
    src/Entities/contextvar.cpp \
    src/Entities/entity.cpp \
    src/main.cpp \
    src/GUI/mainwindow.cpp \
    src/Entities/trigger.cpp

HEADERS += \
    include/GUI/codeeditor.h \
    include/Entities/counter.h \
    include/Entities/contextvar.h \
    include/Entities/entity.h \
    include/GUI/mainwindow.h \
    include/utils.h \
    include/Entities/trigger.h

FORMS += \
    ui/codeeditor.ui \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    abi \
    target
