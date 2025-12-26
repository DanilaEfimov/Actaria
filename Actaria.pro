QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += include \
            include/Aliases

SOURCES += $$files(src/Entities/*.cpp) \
           $$files(src/GUI/*.cpp) \
           src/main.cpp \
           src/stringlistcursor.cpp

HEADERS += $$files(include/Entities/*.h) \
           $$files(include/GUI/*.h) \
           $$files(include/Aliases/*.h) \
           include/config.h \
           include/engineinfo.h \
           include/readwrite.h \
           include/stringlistcursor.h \
           include/utils.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    abi \
    include/Aliases/variables \
    target
