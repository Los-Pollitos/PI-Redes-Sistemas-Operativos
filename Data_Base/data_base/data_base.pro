QT += core gui
QT += sql
CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        data_base.cpp \
        data_server.cpp \
        log.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    data_base.h \
    data_server.h \
    log.h

DISTFILES += \
    employees.txt \
    laboral_datas.txt \
    offices.txt \
    records.txt \
    requests.txt
