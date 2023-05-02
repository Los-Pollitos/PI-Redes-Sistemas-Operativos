#include "file_system.h"

FS::FS() {
  this->fat = new int [TAMANO_FAT];
  this->directorio = new entradaDirectorio* [TAMANO_FAT];
  this->unidad = new char* [TAMANO_MAX];

  for(int i = 0; i < TAMANO_FAT; ++i) {
    if (i < TAMANO_MAX) {
      this->unidad[i] = new char [TAMANO_MAX];
    }
    this->fat[i] = VACIO;
    this->directorio[i] = new entradaDirectorio;
    this->directorio[i].bloque = VACIO;
  }
}

FS::~FS() {
  for(int i = 0; i < TAMANO_FAT; ++i) {
    if (i < TAMANO_MAX) {
      delete this->unidad[i];
    }
    delete this->directorio[i];
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
    time(this->directorio[posDirectorio].fecha);
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

int buscarDirectorio() {
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

}