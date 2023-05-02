/*
Equipo: Los Pollitos
Cristopher Hernández (C13632)
Luis Solano (C17634)
Angie Solís (C17686)
Emilia Víquez (C18625)
*/
#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#define TAMANO_MAX 10
#define TAMANO_FAT 100
#define FIN_ARCHIVO -1
#define VACIO -2

#include <iostream>
#include <string>

// RESTRICCIONES
// 1. bloques son de 1 caracter
// 2. Unidad es una matriz de caracteres
// 3. Tamaño máximo 100 caracteres, por el momento
// 4. Usando FAT
// 5. Usando un struct para el directorio (nombre, bloque inicial, fecha)

typedef struct entradaDirectorio{
  int bloque;
  std::string nombre;
  time_t fecha;
}entradaDirectorio_t;

class FS{
  // variables
  private:
    char** unidad;
    entradaDirectorio_t* directorio;
    int* fat;

  // métodos
  public:
    FS();
    ~FS();
    int crear(std::string nombre);
    void agregar(std::string nombre, char caracter);
    void imprimirUnidad();
  private:
    int buscarBloque();
    int buscarDirectorio();
};

#endif  //FILE_SYSTEM_H