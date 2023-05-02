#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#define MAX_SIZE 10
#define FAT_SIZE 100

//RESTRICCIONES
//1. bloques son de 1 caracter
//2. Unidad es una matriz de caracteres
//3. Tamaño máximo 100 caracteres, por el momento
//4. Usando FAT
//5. Usando un struct para el directorio (nombre, bloque inicial, fecha, por el momento)


struct entradaDirectorio{
  int bloque;
  std::string nombre;
  time_t fecha;
};

class FS{
  // vars
  private:
    char** unidad;
    entradaDirectorio* directorio; // si
    int* fat;

  // methods
  public:
    FS();
    ~FS();
    int crear(std::string nombre);
    void agregar(std::string nombre, char caracter);
    void imprimirUnidad();
  private:
    int buscarBloque();
};

#endif  //FILE_SYSTEM_H