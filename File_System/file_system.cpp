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
  // TODO(nosotros): reconsiderar si esto se queda así
  // int bloque = this->buscarBloque();
  int posDirectorio = this->buscarDirectorio();
  if (posDirectorio != -1) {
    this->directorio[posDirectorio].bloque = FIN_ARCHIVO;
    this->directorio[posDirectorio].nombre = nombre;
    time(&this->directorio[posDirectorio].fecha);
    // this->fat[bloque] = FIN_ARCHIVO;
  }
  return posDirectorio;
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

int FS::agregar(std::string nombre, std::string caracter) {
  int posDirectorio = buscarArchivo(nombre);
  if (posDirectorio == -1) {
    return posDirectorio;
  }
  int posAgregarFat = -1;
  int siguienteVacioFat = -1;
  if (this->directorio[posDirectorio].bloque != FIN_ARCHIVO) {
    posAgregarFat = this->buscarPosFinArchivo(this->directorio[posDirectorio].bloque);
    siguienteVacioFat = this->buscarBloque();
    if (siguienteVacioFat == -1) {
      return -1;
    }
    this->fat[posAgregarFat] = siguienteVacioFat;
    this->fat[siguienteVacioFat] = FIN_ARCHIVO;
    posAgregarFat = siguienteVacioFat;
  } else {
    posAgregarFat = this->buscarBloque();
    this->directorio[posDirectorio].bloque =  posAgregarFat;
  } // después de este if/else, se tiene en posAgregarFat a la próxima
  // dirección FAT y de la unidad que se quiere modificar

  int fila = -1;
  int columna = -1;
  for(int i = 0; i < caracter.length(); ++i) {
    this->traducirPos(posAgregarFat, fila, columna);
    this->unidad[fila][columna] = caracter[i];
    this->fat[posAgregarFat] = FIN_ARCHIVO;
    if (i < caracter.length()-1) {
      siguienteVacioFat = this->buscarBloque();
      if (siguienteVacioFat == -1) {
        return -1;
      }
      this->fat[posAgregarFat] = siguienteVacioFat;
      this->fat[siguienteVacioFat] = FIN_ARCHIVO;
      posAgregarFat = siguienteVacioFat;
    }
  }
  return posAgregarFat;  // retorna el nuevo final
}

int FS::buscarArchivo(std::string& nombre) {
  int posDirectorio = -1;
  for (int i = 0; i < TAMANO_FAT; ++i) {
    if (this->directorio[i].nombre == nombre) {
      posDirectorio = i;
      break;
    }
  }
  return posDirectorio;
}

int FS::buscarPosFinArchivo(int posFat) {
  while(this->fat[posFat] != FIN_ARCHIVO) {
    posFat = this->fat[posFat];
  }
  return posFat;
}

void FS::traducirPos(int posicion, int& fila, int& columna) {
  fila = posicion / 10;
  columna = posicion % 10;
}


void FS::borrar(std::string nombre) {
  int posDirectorio = buscarArchivo(nombre);
  if (posDirectorio == -1) {
    return;  // Se va del método si el archivo indicado no existía
  }
  int posFat = this->directorio[posDirectorio].bloque;
  this->directorio[posDirectorio].bloque = VACIO;
  // TODO(nosotros): considerar si borrar la fecha y el nombre solo lo hacemos en el profundo o en ambos
  // en el profundo de fijo, pq puede ser un archivo de contenido sensible que no quiero que nadie sepa ni que existió
  this->directorio[posDirectorio].fecha = 0;
  this->directorio[posDirectorio].nombre = "";

  int posAux = posFat;
  while (this->fat[posFat] != FIN_ARCHIVO) {
    posAux = this->fat[posFat];
    this->fat[posFat] = VACIO;
    posFat = posAux;
  }
  this->fat[posFat] = VACIO;
}

void FS::borrarProdundo(std::string nombre) {
  int posDirectorio = buscarArchivo(nombre);
  if (posDirectorio == -1) {
    return;  // Se va del método si el archivo indicado no existía
  }
  int posFat = this->directorio[posDirectorio].bloque;
  this->directorio[posDirectorio].bloque = VACIO;
  this->directorio[posDirectorio].fecha = 0;
  this->directorio[posDirectorio].nombre = "";

  int posAux = posFat;
  int fila = -1;
  int columna = -1;
  while (this->fat[posFat] != FIN_ARCHIVO) {
    this->traducirPos(posFat, fila, columna);
    this->unidad[fila][columna] = '\0';
    posAux = this->fat[posFat];
    this->fat[posFat] = VACIO;
    posFat = posAux;
  }
  this->fat[posFat] = VACIO;
  this->traducirPos(posFat, fila, columna);
  this->unidad[fila][columna] = '\0';

}

void FS::imprimirUnidad() {
  std::cout << "\n\nDirectorio:" << std::endl;
  for (int i = 0; i < TAMANO_FAT; ++i) {
    if (this->directorio[i].bloque != VACIO) {
      std::cout << this->directorio[i].nombre << "  ";
      if (this->directorio[i].bloque != FIN_ARCHIVO) {
        std::cout<<this->directorio[i].bloque << std::endl;
      } else {
        std::cout<<"vacio" << std::endl;
      }
    }
  }
  std::cout << "\nFAT:" << std::endl;
  for (int i = 0; i < TAMANO_FAT; ++i) {
    if (this->fat[i] == VACIO) {
      std::cout << "  ";
    } else if (this->fat[i] == FIN_ARCHIVO) {
      std::cout << "F ";
    } else {
      std::cout << this->fat[i] << " ";
    }
    if ((i+1) % 10 == 0) {
      std::cout << std::endl;
      for (int j = i-9; j <= i; ++j) {
        std::cout << j << " ";
      }
      std::cout << std::endl;
    }
  }
  std::cout << "\nUnidad:" << std::endl;
  for (int i = 0; i < TAMANO_MAX; ++i) {
    for (int j = 0; j < TAMANO_MAX; ++j) {
      if (this->unidad[i][j] != '\0') {
        std::cout << this->unidad[i][j] << " ";
      } else {
        std::cout << "  ";
      }
    }
    std::cout << std::endl;
    for (int j = i*10; j <= i*10+9; ++j) {
      std::cout << j << " ";
    }
    std::cout << std::endl;
  }
}