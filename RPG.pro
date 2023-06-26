QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
win32 {
    LIBS += -lwinmm
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    attack.cpp \
    character.cpp \
    demon.cpp \
    game.cpp \
    health.cpp \
    main.cpp \
    score.cpp

HEADERS += \
    attack.h \
    character.h \
    demon.h \
    game.h \
    health.h \
    score.h

FORMS +=

TRANSLATIONS += \
    RPG_es_CL.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
