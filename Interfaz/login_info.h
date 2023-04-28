#ifndef LOGIN_INFO_H
#define LOGIN_INFO_H

#include <string>

#define TOKEN_SIZE 6

struct login_info {
    std::string user;
    std::string password;
    int token[TOKEN_SIZE];
} typedef login_info_t;

#endif // LOGIN_INFO_H
