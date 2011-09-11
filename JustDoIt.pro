#-------------------------------------------------
#
# Project created by QtCreator 2011-09-04T19:15:59
#
#-------------------------------------------------

QT       += core gui xml

TARGET = JustDoIt
TEMPLATE = app

QMAKE_CXXFLAGS_RELEASE ~= s/-O./-O3/g
QMAKE_LFLAGS_RELEASE ~= s/-O./-O3/g

SOURCES += main.cpp\
        MainWindow.cpp \
    TaskXmlWriter.cpp \
    Task.cpp \
    UserData.cpp \
    TaskXmlReader.cpp \
    TaskTableModel.cpp \
    TaskTableStringListComboboxDelegate.cpp \
    TaskTableColorDoneDelegate.cpp \
    TaskSortFilterProxyModel.cpp

HEADERS  += MainWindow.h \
    TaskXmlWriter.h \
    Task.h \
    UserData.h \
    TaskXmlReader.h \
    TaskTableModel.h \
    TaskTableStringListCombobox.h \
    TaskTableColorDoneDelegate.h \
    TaskSortFilterProxyModel.h

FORMS    += MainWindow.ui

OTHER_FILES += \
    Tasks.xsd



































