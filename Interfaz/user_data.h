#ifndef USER_DATA_H
#define USER_DATA_H

#include <string>

struct user_data {
    std::string user;
    std::string name;
    std::string identification;
    std::string salary;
    std::string job;
    int available_vacations;
};

#endif // USER_DATA_H