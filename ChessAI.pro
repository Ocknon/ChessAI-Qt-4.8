#-------------------------------------------------
#
# Project created by QtCreator 2016-11-28T14:30:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChessAI
TEMPLATE = app


SOURCES += main.cpp \
    game.cpp \
    board.cpp \
    tile.cpp \
    piece.cpp \
    movefactory.cpp \
    overlay.cpp \
    move.cpp \
    alphabeta.cpp \
    weights.cpp

HEADERS  += \
    game.h \
    board.h \
    tile.h \
    piece.h \
    movefactory.h \
    overlay.h \
    move.h \
    alphabeta.h \
    weights.h

RESOURCES += \
    resources.qrc
