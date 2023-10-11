# -------------------------------------------------
# Project created by QtCreator 2009-01-10T14:03:23
# -------------------------------------------------
QT += network widgets
TARGET = MyQServer
TEMPLATE = app

SOURCES += ./src/main.cpp \
    ./src/MySocketServer.cpp \
    ./src/MySocketClient.cpp \
    ./src/dialog.cpp \
    src/Fstat.cpp \
    src/FstatManager.cpp \
    src/MyCache.cpp \
    src/Sort.cpp \
    src/cacheelement.cpp \
    src/stats.cpp

HEADERS += ./src/MySocketServer.h \
    ./src/MySocketClient.h \
    ./src/dialog.h \
    src/Fstat.h \
    src/FstatManager.h \
    src/Sort.h \
    src/cache.h \
    src/cacheelement.h \
    src/stats.h

OTHER_FILES += MyQServer.pro
CONFIG += c++11
