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
  if (posDirectorio != -1) {
    this->directorio[posDirectorio].bloque = bloque;
    this->directorio[posDirectorio].nombre = nombre;
    time(&this->directorio[posDirectorio].fecha);
    // Se utiliza como EOF pero indica que está vacío
    this->fat[bloque] = RESERVADO;
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

int FS::agregar(std::string nombre, std::string caracter) {
  int posDirectorio = buscarArchivo(nombre);
  if (posDirectorio == -1) {
    return posDirectorio;
  }
  // Se inserta el primer caracter del archivo
  int bloque = this->directorio[posDirectorio].bloque;
  int fila = -1;
  int columna = -1;
  int siguienteVacio = -1;
  for(int i = 0; i < caracter.length(); ++i) {
    if(this->fat[bloque] != RESERVADO) {
      // Se va a insertar un caracter y se ocupa un nuevo bloque
      siguienteVacio = this->buscarBloque();
      // Si se logra encontrar un error
      if (siguienteVacio == -1) {
        return -1;
      }
      // Se le establece un nuevo fin de archivo y se le cambia al pasado para
      // que apunte al siguiente fin de archivo
      this->fat[siguienteVacio] = FIN_ARCHIVO;
      this->fat[bloque] = siguienteVacio;
      this->traducirPos(siguienteVacio, fila, columna);
      this->unidad[fila][columna] = caracter[i];
      bloque = siguienteVacio;
    } else {
      // Es lo primero insertado al archivo
      this->fat[bloque] = FIN_ARCHIVO;
      this->traducirPos(bloque, fila, columna);    
      this->unidad[fila][columna] = caracter[0];
    }
  }
  return bloque;
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
  while(this->fat[posFat] != FIN_ARCHIVO && this->fat[posFat] != RESERVADO) {
    posFat = this->fat[posFat];
  }
  return posFat;
}

void FS::traducirPos(int posicion, int& fila, int& columna) {
  fila = posicion / 10;
  columna = posicion % 10;
}


int FS::borrar(std::string nombre) {
  int posDirectorio = buscarArchivo(nombre);
  if (posDirectorio == -1) {
    return -1;  // Se va del método si el archivo indicado no existía
  }
  int posFat = this->directorio[posDirectorio].bloque;
  this->directorio[posDirectorio].bloque = VACIO;
  this->directorio[posDirectorio].fecha = 0;
  this->directorio[posDirectorio].nombre = "";

  int posAux = posFat;
  while (this->fat[posFat] != FIN_ARCHIVO && this->fat[posFat] != RESERVADO) {
    posAux = this->fat[posFat];
    this->fat[posFat] = VACIO;
    posFat = posAux;
  }
  this->fat[posFat] = VACIO;
  // Exitoso
  return 1;
}

int FS::borrarProfundo(std::string nombre) {
  int posDirectorio = buscarArchivo(nombre);
  if (posDirectorio == -1) {
    return -1;  // Se va del método si el archivo indicado no existía
  }
  int posFat = this->directorio[posDirectorio].bloque;
  this->directorio[posDirectorio].bloque = VACIO;
  this->directorio[posDirectorio].fecha = 0;
  this->directorio[posDirectorio].nombre = "";

  int posAux = posFat;
  int fila = -1;
  int columna = -1;
  while (this->fat[posFat] != FIN_ARCHIVO && this->fat[posFat] != RESERVADO) {
    this->traducirPos(posFat, fila, columna);
    this->unidad[fila][columna] = '\0';
    posAux = this->fat[posFat];
    this->fat[posFat] = VACIO;
    posFat = posAux;
  }
  this->fat[posFat] = VACIO;
  this->traducirPos(posFat, fila, columna);
  this->unidad[fila][columna] = '\0';
  // Exitoso
  return 1;
}

void FS::imprimirUnidad() {
  std::cout << "\n\nDirectorio:" << std::endl;
  for (int i = 0; i < TAMANO_FAT; ++i) {
    if (this->directorio[i].bloque != VACIO) {
      std::cout << this->directorio[i].nombre << "  ";
      std::cout<< this->directorio[i].bloque << std::endl;
    }
  }
  std::cout << "\nFAT:" << std::endl;
  for (int i = 0; i < TAMANO_FAT; ++i) {
    if (this->fat[i] == VACIO) {
      std::cout << "  ";
    } else if (this->fat[i] == FIN_ARCHIVO || this->fat[i] == RESERVADO) {
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