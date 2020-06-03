TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    FileIOModule.h \
    Personnel.h \
    PersonnelBuilder.h \
    PersonnelBuilderFactory.h \
    PersonnelManager.h
