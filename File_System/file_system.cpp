#include "file_system.h"

FS::FS() {
  this->fat = new int [FAT_SIZE];
  this->unidad = new char [MAX_SIZE];
  for(int i = 0; i < MAX_SIZE; ++i) {
    this->unidad[i] = new char [MAX_SIZE];
  }
}

FS::~FS() {
  delete [] this->fat;
  for(int i = 0; i < MAX_SIZE; ++i) {
    delete this->unidad[i];
  }
  delete [] this->unidad;
}

int FS::crear(std::string nombre) {
  
}

int FS::buscarBloque() {

}

void FS::agregar(std::string nombre, char caracter) {

}

void FS::imprimirUnidad() {

}