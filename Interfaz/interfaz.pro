QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    change_password.cpp \
    consult_record.cpp \
    consult_requests.cpp \
    consult_salary.cpp \
    description_button.cpp \
    file_system.cpp \
    handle_requests.cpp \
    initial.cpp \
    login.cpp \
    logout_button.cpp \
    main.cpp \
    mainwindow.cpp \
    manage_user.cpp \
    modify_user.cpp \
    payment_proof.cpp \
    request_description.cpp \
    request_vacations.cpp \
    salary_proof.cpp \
    token.cpp \
    vacation_consult.cpp \
    work_proof.cpp

HEADERS += \
    change_password.h \
    consult_record.h \
    consult_requests.h \
    consult_salary.h \
    description_button.h \
    file_system.h \
    handle_requests.h \
    initial.h \
    login.h \
    login_info.h \
    logout_button.h \
    mainwindow.h \
    manage_user.h \
    modify_user.h \
    payment_proof.h \
    request_description.h \
    request_vacations.h \
    salary_proof.h \
    token.h \
    user_data.h \
    vacation_consult.h \
    work_proof.h

FORMS += \
    change_password.ui \
    consult_record.ui \
    consult_requests.ui \
    consult_salary.ui \
    handle_requests.ui \
    initial.ui \
    login.ui \
    mainwindow.ui \
    manage_user.ui \
    modify_user.ui \
    payment_proof.ui \
    request_description.ui \
    request_vacations.ui \
    salary_proof.ui \
    token.ui \
    vacation_consult.ui \
    work_proof.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc
