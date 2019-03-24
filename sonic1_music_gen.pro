QT += core gui widgets

TARGET = sonic1_music_gen
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    smps_voice.cpp \
    pattern_edit_box.cpp

HEADERS += \
    mainwindow.h \
    smps_voice.h \
    pattern_edit_box.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
