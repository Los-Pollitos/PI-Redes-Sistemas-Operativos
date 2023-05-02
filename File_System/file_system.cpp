#include <iostream>

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
  char **Unidad ;
  Directorio; // si
  int* FAT;

  // methods
  public: 
  void crear(std::string nombre){};
  void agregar(std::string nombre, char caracter){};
  void imprimirUnidad(){};
};


int main() {
  FS *fs = new FS() ;

  fs->crear("a.dat") ;
  fs->agregar("a.dat",'a') ;
  fs->imprimirUnidad() ; //imprime unidad, directorio y tabla fat

  fs->crear("b.dat") ;
  fs->agregar("b.dat", 'b') ;
  fs->imprimirUnidad() ;
  fs->agregar("b.dat",'c') ;
  fs->imprimirUnidad() ;
  
}



/*  IMPRIMIR UNIDAD al final

Directorio:
"b.dat"   1
"c.dat"   0


FAT
3 2 x 4 x
0 1 2 3 4 5 6 7 


Cla/*

UNIDAD
c b b
c c _
_ _ _
  
*/
  