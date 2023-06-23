#ifndef LOGIN_INFO_H
#define LOGIN_INFO_H

#include <string>

#define TOKEN_SIZE 6

#define SUPERUSER 128
#define UNEMPLOYEED 64
#define EMPLOYEE 32
#define HUMAN_RESOURCES 16
#define SUPERVISOR 8
#define ADMIN_USER 4
#define ADMIN_CONFIG 2
#define AUDITOR 1


struct login_info {
    std::string user;
    std::string password;
    int token[TOKEN_SIZE];
    char roles;
} typedef login_info_t;

#endif // LOGIN_INFO_H
