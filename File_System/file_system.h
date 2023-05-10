/*
Team: Los Pollitos
Cristopher Hernández (C13632)
Luis Solano (C17634)
Angie Solís (C17686)
Emilia Víquez (C18625)
*/

#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H
// No se tiene espacio para manejar tanta memoria
// Tamaño recomendado: 1440000 (matriz 1200 x 1200)

// #define MAX_SIZE 90000
// #define BLOCK_SIZE 10
// TODO(nosotros): Cambiar
#define MAX_SIZE 100
#define BLOCK_SIZE 10

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
} directory_entry_t;

class FS {
private:
  // private variables
  char *unit;
  directory_entry_t *directory;
  int *fat;

  // private methods
private:
  int search_block(int position);
  int search_directory();
  int search_file(std::string &name);
  int search_end_of_file(int fat_pos, int size);

  // public methods
public:
  FS();
  ~FS();
  int create(std::string name);
  int append(std::string name, std::string character);
  int erase(std::string name);
  int deep_erase(std::string name);
  void print_unit();
};

#endif // FILE_SYSTEM_H