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
  // Crear el file system
  FS *fs = new FS();
  // Crear dos archivos b.dat y c.dat
  fs->create("c.dat");
  fs->create("b.dat");
  // Agregar de manera intercambiada contenido a ambos
  fs->append("c.dat", "ccccccccccc");
  fs->append("b.dat", "bb");
  fs->print_unit();
  fs->append("c.dat", "ccccc");
  // Mostrar la unidad
  fs->print_unit();
  // Borrar c
  fs->deep_erase("c.dat");
  fs->append("b.dat", "bbbbbbbbbb");
  fs->append("b.dat", "bbbbbbbbbb");
  fs->create("luis.txt");
  fs->append("luis.txt", "luis");
  fs->print_unit();
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
