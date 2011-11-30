QT += core gui

TARGET = habr
TEMPLATE = app

SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

RESOURCES += \
    images.qrc

macx: {
    #DESTDIR = .
    ICON = myicon.icns
    QMAKE_INFO_PLIST = MyInfo.plist
    QMAKE_LFLAGS += -framework Cocoa
    SOURCES += macintegration.cpp
    HEADERS +=  macintegration.h \
                myprivate.h
    OBJECTIVE_SOURCES += myprivate.mm
    target.path = /Applications
    resources.path = /Applications/habr.app/Contents/Resources
    resources.files = ./resources/*
    INSTALLS = target resources
}
