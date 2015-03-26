QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = phonebook
TEMPLATE = app


HEADERS += \
    addfilterwindow.h \
    addmenu.h \
    exceptions.h \
    findwindow.h \
    incorrectnm.h \
    maindial.h \
    phonebook.h \
    sortdial.h \
    Exceptions.h

SOURCES += \
    addfilterwindow.cpp \
    addmenu.cpp \
    findwindow.cpp \
    incorrectnm.cpp \
    main.cpp \
    maindial.cpp \
    phonebook.cpp \
    sortdial.cpp
