QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
LIBS += -lcrypto

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    auditor.cpp \
    client.cpp \
    log_generator.cpp \
    login.cpp \
    logout_button.cpp \
    main.cpp \
    mainwindow.cpp \
    security.cpp \
    token.cpp

HEADERS += \
    auditor.h \
    client.h \
    common.h \
    log_generator.h \
    login.h \
    login_info.h \
    logout_button.h \
    mainwindow.h \
    security.h \
    token.h

FORMS += \
    auditor.ui \
    login.ui \
    mainwindow.ui \
    token.ui

# Default rules for deployment.
TARGET = "PollitosIncorporated"
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc

DISTFILES += \
    pollitos_icon.png
