#include "file_system.h"

FS::FS() {
  this->fat = new int [TAMANO_FAT];
  this->unidad = new char [TAMANO_MAX];
  for(int i = 0; i < TAMANO_FAT; ++i) {
    if (i < TAMANO_MAX) {
      this->unidad[i] = new char [TAMANO_MAX];
    }
    this->fat[i] = VACIO;
  }
}

FS::~FS() {
  delete [] this->fat;
  for(int i = 0; i < TAMANO_MAX; ++i) {
    delete this->unidad[i];
  }
  delete [] this->unidad;
}

int FS::crear(std::string nombre) {
  
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

void FS::agregar(std::string nombre, char caracter) {

}

void FS::imprimirUnidad() {

}