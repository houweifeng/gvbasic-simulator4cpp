#-------------------------------------------------
#
# Project created by QtCreator 2017-04-08T21:57:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gvbsim
TEMPLATE = app

CONFIG += c++14

QMAKE_CXXFLAGS += -pthread -fno-operator-names
LIBS += -pthread

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    ../gvb/compile.cpp \
    ../gvb/data_man.cpp \
    ../gvb/device.cpp \
    ../gvb/file.cpp \
    ../gvb/func.cpp \
    ../gvb/gvb.cpp \
    ../gvb/lex.cpp \
    ../gvb/node_man.cpp \
    ../gvb/real.cpp \
    ../gvb/runtime.cpp \
    ../gvb/value.cpp \
    ../gvb/fake6502_wrap.cpp \
    gui_qt.cpp \
    readconfig.cpp \
    screen.cpp \
    var_edit_dlg.cpp

HEADERS  += \
    ../gvb/compile.h \
    ../gvb/data_man.h \
    ../gvb/device.h \
    ../gvb/error.h \
    ../gvb/file.h \
    ../gvb/func.h \
    ../gvb/gvb.h \
    ../gvb/igui.h \
    ../gvb/lex.h \
    ../gvb/node.h \
    ../gvb/node_man.h \
    ../gvb/random.h \
    ../gvb/real.h \
    ../gvb/tree.h \
    ../gvb/value.h \
    ../gvb/fake6502_wrap.h \
    gui_qt.h \
    readconfig.h \
    screen.h \
    var_edit_dlg.h
