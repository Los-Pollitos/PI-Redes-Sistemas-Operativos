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
  FS* fs = new FS();
  // Crear dos archivos b.dat y c.dat
  fs->crear("c.dat");
  fs->crear("b.dat");
  // Agregar de manera intercambiada contenido a ambos
  fs->agregar("c.dat", "c");
  fs->agregar("b.dat", "bb");
  fs->agregar("c.dat", "cc");
  // Mostrar la unidad
  fs->imprimirUnidad();
  // Borrar c
  fs->borrarProfundo("c.dat");
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
  