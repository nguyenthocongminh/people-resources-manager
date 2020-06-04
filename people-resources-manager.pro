TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Employee.cpp \
        EmployeeManager.cpp \
        FileIoUtils.cpp \
        main.cpp

HEADERS += \
    Employee.h \
    EmployeeManager.h \
    FileIoUtils.h
