/*
Equipo: Los Pollitos
Cristopher Hernández (C13632)
Luis Solano (C17634)
Angie Solís (C17686)
Emilia Víquez (C18625)
*/

#include "file_system.h"
#include <iostream>

int main() {
  FS *fs = new FS();

  std::cout << "\n\nSe crea el archivo a.dat y se agrega un caracter \'a\'" << std::endl;
  fs->crear("a.dat");
  fs->agregar("a.dat","a");
  fs->imprimirUnidad(); //imprime unidad, directorio y tabla fat

  std::cout << "Se crea el archivo b.dat y se agrega: \'b\'" << std::endl;
  fs->crear("b.dat");
  fs->agregar("b.dat", "b");
  fs->imprimirUnidad();

  std::cout << "Se agrega: \'cc\'  al archivo b.dat" << std::endl;
  fs->agregar("b.dat","cc");
  fs->imprimirUnidad();

  std::cout << "Se borra profundamente a.dat" << std::endl;
  fs->borrarProdundo("a.dat");
  fs->imprimirUnidad();

  std::cout << "Se crea x.dat vacio" << std::endl;
  fs->crear("x.dat");
  fs->imprimirUnidad();

  return 0;
}



/*  IMPRIMIR UNIDAD al final

Directorio:
"b.dat"   1
"c.dat"   0

FAT
3 2 x 4 x
0 1 2 3 4 5 6 7 


UNIDAD
c b b 
c c _
_ _ _
*/
  