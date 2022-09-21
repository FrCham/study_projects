#-------------------------------------------------
#
# Project created by QtCreator 2017-12-20T20:58:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MusicLib
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    item.cpp \
    artist.cpp \
    track.cpp \
    album.cpp \
    musicmodel.cpp \
    albumdialog.cpp \
    artistdialog.cpp \
    ratingwidget.cpp \
    ratingdelegate.cpp

HEADERS += \
        mainwindow.h \
    item.h \
    artist.h \
    track.h \
    album.h \
    musicmodel.h \
    albumdialog.h \
    artistdialog.h \
    ratingwidget.h \
    ratingdelegate.h

TRANSLATIONS += \
        translations/MusicLib_ru.ts \
        translations/MusicLib_en.ts \

FORMS += \
        mainwindow.ui \
    albumdialog.ui \
    artistdialog.ui

RESOURCES += \
    res.qrc
