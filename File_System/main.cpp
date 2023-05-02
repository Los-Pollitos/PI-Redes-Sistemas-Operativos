#include <iostream>

#include "file_system.h"

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
  