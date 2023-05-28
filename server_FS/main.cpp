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
  // Create the file system
  FS *fs = new FS();

  // fs->set_path("cjimenez", "Root");
  // fs->create("1.dat");
  // fs->create("11.dat");
  // fs->create("F1", false);
  // fs->change_folder("cjimenez", "F1");
  // fs->create("2.dat");
  // fs->create("22.dat");
  // fs->create("F2", false);

  // std::cout << "\ntrato de crear archivo con mismo nombre. Pude (-1 significa "
  //              "que no pude)? "
  //           << fs->create("2.dat") << std::endl;

  // std::cout << "\n\nAntes de alterar \n";
  // fs->set_path("cjimenez", "Root");
  // std::cout << " Root:  \n";
  // fs->list("cjimenez");

  // fs->set_path("cjimenez", "Root/F1");
  // std::cout << "\n  F1:  \n";
  // fs->list("cjimenez");

  // fs->set_path("cjimenez", "Root/F1/F2");
  // std::cout << "\n  F2:  \n";
  // fs->list("cjimenez");

  // fs->set_path("cjimenez", "Root/F1");
  // std::cout << "\n\nEstoy en carpeta: " << fs->get_actual_path()
  //           << " y voy a mover 2.dat a F2 y F2 a Root:" << std::endl;

  // fs->move("cjimenez", "2.dat", "Root/F1/F2");
  // fs->move("cjimenez", "F2", "Root");

  // std::cout << "\n\n Listo Root: \n";
  // fs->set_path("cjimenez", "Root");
  // fs->list("cjimenez");

  // std::cout << "\n\n Listo folder1: \n";
  // fs->set_path("cjimenez", "Root/F1");
  // fs->list("cjimenez");

  // std::cout << "\nIntento llegar a folder2 en su nueva direccion: "
  //           << fs->set_path("cjimenez", "Root/F2");
  // std::cout << "\n\n Listo folder2: \n";
  // fs->list("cjimenez");
  // std::cout << std::endl;

  // fs->set_path("cjimenez", "Root/F1");
  // fs->delete_folder("cjimenez", "F1");
  // std::cout << "Root despues de borrar F1: " << std::endl;
  // fs->list("cjimenez");
  // std::cout << "Si me trato de mover a F1, puedo? " << fs->set_path("cjimenez", "Root/F1") << std::endl;

  fs->set_path("user", "Root/F2");
  // std::cout << "Cargo archivo de usuarios (a F2) con sus hash e imprimo todo:";
  fs->create("users.dat");
  fs->open("user", "users.dat");
  fs->append("users.dat", "cjimenez,78e8ee0b2f67531b8eda7678fa42fb,34\n");
  fs->append("users.dat", "gmora,012c59ee798d64a93a6f04b63068f0,32\n");
  fs->append("users.dat", "jnunez,8f832c435e055304458eeec4a0e856,32\n");
  fs->append("users.dat", "eguzman,0a5cce9b879d006966d0caffec8e2d,48\n");
  fs->append("users.dat", "alopez,92e9ecfc92ae9546756fffa9916535,40\n");
  fs->append("users.dat", "respinoza,97b76083f03babf865b65f3e7cdb6b,36\n");
  fs->append("users.dat", "gherrera,4e3f6bf544ccf40302f69ce4319617,38\n");
  fs->append("users.dat", "rgang,a0e059e31df4f94a0992291b8d3735,56\n");
  fs->append("users.dat", "dcabezas,d7b5221b92b1be0572afc5980df5e0,56\n");
  fs->append("users.dat", "d_gmora,746af3077841560d8ae21ba6afb0cd,1\n");

  fs->write_unit();

  // std::cout << "\n\nPrueba de metodo write:\n";
  // fs->create("prueba");
  // fs->open("prueba", "prueba");
  // std::cout << "En Folder2 actualmente:\n";
  // fs->list("prueba");
  // std::cout << std::endl;
  // fs->write("prueba", "prueba", "probandoprobandoprobando");
  // fs->reset_file_pointer("prueba", "prueba");
  // std::cout << "Prueba tiene: " << fs->read_line("prueba", "prueba") << std::endl;
  // fs->reset_file_pointer("prueba", "prueba");
  // fs->write("prueba", "prueba", "12345678");
  // fs->write("prueba", "prueba", "91234567");
  // fs->write("prueba", "prueba", "123456bb");
  // fs->write("prueba", "prueba", "1234567cc");
  // fs->write("prueba", "prueba", "hola");
  // std::cout << "Estoy en eof? "<< fs->is_eof("prueba", "prueba") << std::endl; 
  // fs->reset_file_pointer("prueba", "prueba");
  // fs->write("prueba", "prueba", "funcionabien");
  // fs->reset_file_pointer("prueba", "prueba");
  // std::cout << "Prueba tiene: " << fs->read_line("pruebal", "prueba") << std::endl;

 // fs->print_unit();

  delete fs;
  return 0;
}