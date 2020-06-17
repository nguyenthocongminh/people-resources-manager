TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        CheckPoint.cpp \
        DateUtils.cpp \
        Employee.cpp \
        EmployeeDTO.cpp \
        EmployeeManager.cpp \
        FileIoUtils.cpp \
        StringUtils.cpp \
        ValidateUtils.cpp \
        main.cpp

HEADERS += \
    CheckPoint.h \
    DateUtils.h \
    Employee.h \
    EmployeeDTO.h \
    EmployeeManager.h \
    FileIoUtils.h \
    StringUtils.h \
    ValidateUtils.h
