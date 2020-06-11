TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        CheckPoint.cpp \
        Employee.cpp \
        EmployeeManager.cpp \
        FileIoUtils.cpp \
        ValidateUtils.cpp \
        main.cpp

HEADERS += \
    CheckPoint.h \
    Employee.h \
    EmployeeManager.h \
    FileIoUtils.h \
    ValidateUtils.h
