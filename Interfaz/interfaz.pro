QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

LIBS += -lcrypto

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    auditor.cpp \
    change_password.cpp \
    client.cpp \
    consult_record.cpp \
    consult_requests.cpp \
    consult_salary.cpp \
    description_button.cpp \
    generate_new_token.cpp \
    handle_requests.cpp \
    initial.cpp \
    log_generator.cpp \
    login.cpp \
    logout_button.cpp \
    main.cpp \
    mainwindow.cpp \
    manage_user.cpp \
    modify_office.cpp \
    modify_user.cpp \
    office_description.cpp \
    payment_proof.cpp \
    request_description.cpp \
    request_vacations.cpp \
    salary_proof.cpp \
    security.cpp \
    sys_config.cpp \
    token.cpp \
    vacation_consult.cpp \
    work_proof.cpp \

HEADERS += \
    auditor.h \
    change_password.h \
    client.h \
    consult_record.h \
    consult_requests.h \
    consult_salary.h \
    description_button.h \
    generate_new_token.h \
    handle_requests.h \
    initial.h \
    log_generator.h \
    login.h \
    login_info.h \
    logout_button.h \
    mainwindow.h \
    manage_user.h \
    modify_office.h \
    modify_user.h \
    office_description.h \
    payment_proof.h \
    request_description.h \
    request_vacations.h \
    salary_proof.h \
    security.h \
    sys_config.h \
    token.h \
    user_data.h \
    vacation_consult.h \
    work_proof.h \

FORMS += \
    auditor.ui \
    change_password.ui \
    consult_record.ui \
    consult_requests.ui \
    consult_salary.ui \
    generate_new_token.ui \
    handle_requests.ui \
    initial.ui \
    login.ui \
    mainwindow.ui \
    manage_user.ui \
    modify_office.ui \
    modify_user.ui \
    office_description.ui \
    payment_proof.ui \
    request_description.ui \
    request_vacations.ui \
    salary_proof.ui \
    sys_config.ui \
    token.ui \
    vacation_consult.ui \
    work_proof.ui \

# Default rules for deployment.
TARGET = "PollitosIncorporated"
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc

DISTFILES += \
    pollitos_icon.png
