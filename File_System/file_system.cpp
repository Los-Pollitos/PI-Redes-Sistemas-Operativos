/*
Equipo: Los Pollitos
Cristopher Hernández (C13632)
Luis Solano (C17634)
Angie Solís (C17686)
Emilia Víquez (C18625)
*/

#include "file_system.h"

FS::FS() {
  this->fat = new int [TAMANO_FAT];
  this->directorio = new entradaDirectorio_t [TAMANO_FAT];
  this->unidad = new char* [TAMANO_MAX];

  for(int i = 0; i < TAMANO_FAT; ++i) {
    if (i < TAMANO_MAX) {
      this->unidad[i] = new char [TAMANO_MAX];
    }
    this->fat[i] = VACIO;
    this->directorio[i].bloque = VACIO;
  }
}

FS::~FS() {
  for(int i = 0; i < TAMANO_FAT; ++i) {
    if (i < TAMANO_MAX) {
      delete this->unidad[i];
    }
  }

  delete [] this->fat;
  delete [] this->unidad;
  delete [] this->directorio;
}

int FS::crear(std::string nombre) {
  int bloque = this->buscarBloque();
  int posDirectorio = this->buscarDirectorio();
  if (bloque != -1 && posDirectorio != -1) {
    this->directorio[posDirectorio].bloque = bloque;
    this->directorio[posDirectorio].nombre = nombre;
    time(&this->directorio[posDirectorio].fecha);
    this->fat[bloque] = FIN_ARCHIVO;
  }
  return bloque;
}

// busca el bloque vacío más próximo
int FS::buscarBloque() {
  int bloque = -1;
  for (int i = 0; i < TAMANO_FAT; ++i) {
    if (this->fat[i] == VACIO) {
      bloque = i;
      break;
    }
  }
  return bloque;
}

int FS::buscarDirectorio() {
  int posDirectorio = -1;
  for (int i = 0; i < TAMANO_FAT; ++i) {
    if (this->directorio[i].bloque == VACIO) {
      posDirectorio = i;
      break;
    }
  }
  return posDirectorio;
}

void FS::agregar(std::string nombre, char caracter) {

}

void FS::imprimirUnidad() {
  std::cout << "Directorio:" << std::endl;
  for (int i = 0; i < TAMANO_FAT; ++i) {
    if (this->directorio[i].bloque != VACIO) {
      std::cout << this->directorio[i].nombre << "  " <<
        this->directorio[i].bloque << std::endl;
    }
  }
  std::cout << "FAT:" << std::endl;
  for (int i = 0; i < TAMANO_FAT; ++i) {
    std::cout << this->fat[i] << " ";
    if ((i+1) % 10 == 0) {
      std::cout << std::endl;
      for (int j = i-9; j <= i; ++j) {
        std::cout << j << " ";
      }
      std::cout << std::endl;
    }
  }
}