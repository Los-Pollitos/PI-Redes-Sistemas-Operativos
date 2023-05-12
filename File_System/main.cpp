/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
 */

#include "file_system.h"
#include <iostream>

int main() {
  // Crear el file system
  FS *fs = new FS();

  // Crear dos archivos b.dat y c.dat
  // fs->create("b.dat");
  fs->create("c.dat");
  // // Agregar de manera intercambiada contenido a ambos
  fs->append("c.dat", "1234567890");
  // fs->append("b.dat", "bb");
  fs->append("c.dat", "abcdefghi");
  // fs->print_unit();

  char read = fs->read("cjimenez", "c.dat", 4);
  std::cout << "Caracter 4:" << read << std::endl;
  // fs->append("c.dat", "ccccc");
  // // Mostrar la unidad
  // fs->print_unit();
  // // Borrar c
  // fs->deep_erase("c.dat");
  // fs->append("b.dat", "bbbbbbbbbb");
  // fs->print_unit();
  // fs->append("b.dat", "bbbbbbbbbb");
  // fs->create("luis.txt");
  // fs->append("luis.txt", "luis");
  // fs->print_unit();

  fs->create("users.dat");
  fs->append("users.dat", "cjimenez,78e8ee0b2f67531b8eda7678fa42fb,32\n");
  fs->append("users.dat", "gmora,012c59ee798d64a93a6f04b63068f0,32\n");
  fs->append("users.dat", "jnuñez,8f832c435e055304458eeec4a0e856,32\n");
  fs->append("users.dat", "eguzman,0a5cce9b879d006966d0caffec8e2d,48\n");
  fs->append("users.dat", "alopez,92e9ecfc92ae9546756fffa9916535,40\n");
  fs->append("users.dat", "respinoza,97b76083f03babf865b65f3e7cdb6b,36\n");
  fs->append("users.dat", "gherrera,4e3f6bf544ccf40302f69ce4319617,38\n");
  fs->append("users.dat", "rgang,a0e059e31df4f94a0992291b8d3735,56\n");
  fs->append("users.dat", "dcabezas,d7b5221b92b1be0572afc5980df5e0,56\n");
  fs->append("users.dat", "d_gmora,746af3077841560d8ae21ba6afb0cd,1\n");

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
