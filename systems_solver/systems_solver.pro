QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    firstapproximationtablemodel.cpp \
    gaussmethodsolver.cpp \
    jacobimethodsolver.cpp \
    kramermethodsolver.cpp \
    lesystemsolver.cpp \
    mainwindow.cpp \
    main.cpp \
    matrix.cpp \
    seidelmethodsolver.cpp \
    simpleiterationmethodsolver.cpp \
    systemtablemodel.cpp \
    solutiontablemodel.cpp \
    upperrelaxationmethodsolver.cpp \
    datarequestdialog.cpp

HEADERS += \
    firstapproximationtablemodel.h \
    gaussmethodsolver.h \
    jacobimethodsolver.h \
    kramermethodsolver.h \
    lesystemsolver.h \
    mainwindow.h \
    matrix.h \
    method.h \
    seidelmethodsolver.h \
    simpleiterationmethodsolver.h \
    solution.h \
    systemtablemodel.h \
    solutiontablemodel.h \
    upperrelaxationmethodsolver.h \
    datarequestdialog.h

FORMS += \
    datarequestdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
