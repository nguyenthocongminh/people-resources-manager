TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    ActionEvent.h \
    ActionModule.h \
    FileIOModule.h \
    Personnel.h \
    PersonnelBuilder.h \
    PersonnelBuilderFactory.h \
    PersonnelManager.h
