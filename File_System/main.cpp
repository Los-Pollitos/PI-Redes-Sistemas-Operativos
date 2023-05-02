/*
Equipo: Los Pollitos
Cristopher Hernández (C13632)
Luis Solano (C17634)
Angie Solís (C17686)
Emilia Víquez (C18625)
*/

#include "file_system.h"

int main() {
  FS *fs = new FS();

  fs->crear("a.dat");
  fs->agregar("a.dat",'a');
  fs->imprimirUnidad(); //imprime unidad, directorio y tabla fat

  fs->crear("b.dat");
  fs->agregar("b.dat", 'b');
  fs->imprimirUnidad();
  fs->agregar("b.dat",'c');
  fs->imprimirUnidad();
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
  