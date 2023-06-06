#ifndef USER_DATA_H
#define USER_DATA_H

#include <string>

#define UNEMPLOYEED 64
#define EMPLOYEE 32
#define HUMAN_RESOURCES 16
#define SUPERVISOR 8
#define ADMIN_USER 4
#define ADMIN_CONFIG 2
#define DEBUG 1


struct user_data {
    std::string user;
    std::string name;
    std::string identification;
    std::string phone;
    std::string email;
    std::string job_title;
    char office_id;
    char role;
    int salary_base;
    int deductibles;
    int salary_net;
};

#endif // USER_DATA_H
