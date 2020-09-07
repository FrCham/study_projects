QT += quick \
        core \
        concurrent \
        gui \
        widgets

CONFIG += c++17

SOURCES += \
        engine.cpp \
        main.cpp \
        qmlconnector.cpp

RESOURCES += qml.qrc

HEADERS += \
    engine.h \
    qmlconnector.h
