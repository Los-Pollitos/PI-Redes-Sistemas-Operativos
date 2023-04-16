# QT mainly uses core library and GUI library
# Adds the two libraries into your project
QT += core gui

# Next step is to define the QT version
# Major version greater than 4
# We want to make a widgets application
greaterThan(QT_MAJOR_VERSION, 4) : QT += widgets

# QT += widgets

SOURCES += \
    main.cpp
