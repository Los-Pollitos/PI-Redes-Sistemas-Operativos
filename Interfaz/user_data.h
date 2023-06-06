#ifndef USER_DATA_H
#define USER_DATA_H

#include <string>

#define EMPLOYEE 32
#define HUMAN_RESOURCES 16
#define SUPERVISOR 8
#define ADMIN_USER 4
#define ADMIN_CONFIG 2
#define DEBUG 1


struct user_data {
    std::string user;
    std::string name;
    int identification;
    std::string salary;
    int role;
    int assigned_vacations;
    int available_vacations;
};

#endif // USER_DATA_H
