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
#define DIR_SIZE 256

// char for end text
#define END_TEXT 3

#define END_OF_FILE -1
#define EMPTY -2
#define RESERVED -3
#define FOLDER -4

#include <ctime>
#include <iostream>
#include <string>

/*
TODOS:
 - (El profesor lo movió a la siguiente entrega) Permisos y archivos compartidos
*/

typedef struct directory_entry {
  int block;
  int size;
  int file_pointer;  // points to the current character for read and write operations
  time_t date;
  char permissions[3]; // [user, group, all]
  std::string name;
  std::string path;
  bool is_file;        // true if file, false if directory
  
} directory_entry_t;

typedef struct open_file_entry {
  std::string name;
  int open_count;
} open_file_entry_t;

class FS {
  private:
    // Private variables
    int* fat;
    char* unit;
    directory_entry_t* directory;  
    open_file_entry_t* open_file_table;
    std::string actual_path;
  
  private:
    // Private methods
    int search_block();
    int search_directory();
    int search_file(std::string& name);
    int search_end_of_file(int fat_pos, int size);
    int search_end_of_file_fat(int fat_pos, int size);
    int handle_open_close(std::string user, std::string name, bool open);
    bool check_permission(std::string user, std::string name, int permission);
    void add_one_local_read_pointer(int& local_read_pointer);
    void add_one_local_write_pointer(int& local_write_pointer);
    bool can_show(std::string user, std::string name);
    bool is_valid_path(std::string path);
  
  public:
    // Public methods
    FS();
    ~FS();
    // For files
    int create(std::string name, bool is_file = true);
    int open(std::string user, std::string name);
    int close(std::string user, std::string name);
    int write(std::string user, std::string name, std::string line);
    int append(std::string name, std::string character);
    int erase(std::string name);
    int deep_erase(std::string name);
    char read(std::string user, std::string name, int position);
    std::string read_line(std::string user, std::string name); 
    std::string read_until(std::string user, std::string name, char separator);
    bool is_eof(std::string user, std::string name);
    int is_open(std::string name);
    void print_unit();
    void print_open_file_table();
    void reset_file_pointer(std::string user, std::string name);
  
    // For folders
    // create uses the same method as files
    std::string get_actual_path();
    bool up_folder();
    void list(std::string user);
    bool change_folder(std::string user,std::string folder);
    bool set_path(std::string user, std::string path);
    bool delete_folder(std::string user, std::string folder);
    bool move(std::string user, std::string name, std::string new_abs_path);
};

#endif // FILE_SYSTEM_H
