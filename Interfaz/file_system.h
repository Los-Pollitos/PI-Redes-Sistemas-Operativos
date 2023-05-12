/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
 */

#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#define MAX_SIZE 2048
#define FAT_SIZE 32
#define BLOCK_SIZE 64
// char for end text
#define END_TEXT 3

#define END_OF_FILE -1
#define EMPTY -2
#define RESERVED -3

#include <ctime>
#include <iostream>
#include <string>

typedef struct directory_entry {
    int block;
    int size;
    std::string name;
    time_t date;
    int roles_read;
    int roles_edit;
    char permissions[3]; // u g a
    bool is_file;        // true if file, false if directory
    int read_pointer;
} directory_entry_t;

class FS {
private:
    // private variables
    char *unit;
    directory_entry_t *directory;
    int *fat;

private:
    // private methods
    int search_block();
    int search_directory();
    int search_file(std::string &name);
    int search_end_of_file(int fat_pos, int size);
    int search_end_of_file_fat(int fat_pos, int size);
    bool check_permissions(std::string user, std::string name);
    void add_one_read_pointer(int& local_read_pointer);

public:
    // public methods
    FS();
    ~FS();
    int create(std::string name);
    int append(std::string name, std::string character);
    int erase(std::string name);
    int deep_erase(std::string name);
    char read(std::string user, std::string name, int position);
    std::string read_line(std::string user, std::string name);
    std::string read_until(std::string user, std::string name, char separator);
    void reset_read_pointer(std::string user, std::string name);
    bool is_eof(std::string user, std::string name);
    void print_unit();
};

#endif // FILE_SYSTEM_H
