#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

using namespace std;

int main() {
  int resultado = 0;
  int s = 0, n = 0; // s:socket  n: contador
  char datos[256];  // para escribir lo que se lee
  struct sockaddr_in ipServidor;

  memset(datos, '0', sizeof(datos));

  if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    cout << "Error de creación de socket" << endl;
    resultado = 1;
  } else {
    ipServidor.sin_family = AF_INET;
    ipServidor.sin_port = htons(1337);
    ipServidor.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Se intenta pegar al servidor
    if (connect(s, (struct sockaddr *)&ipServidor, sizeof(ipServidor)) < 0) {
      cout << endl << "Error de conexión por IP o puerto" << endl;
      resultado = 2;
    } else {
      // Se logró pegar, se sacan datos
      datos[0] = 'c';
      datos[1] = 'j';
      datos[2] = 'i';
      datos[3] = 'm';
      datos[4] = ',';
      datos[5] = '2';
      datos[6] = '3';
      std::cout << "Voy a mandar: " << datos << std::endl;
      write(s, datos, strlen(datos));
      memset(datos, '0', sizeof(datos));
      datos[0] = '#';
      std::cout << "Voy a mandar: " << datos << std::endl;
      write(s, datos, strlen(datos));
      // No se logró leer
      if (n < 0) {
        cout << endl << "Error de lectura" << endl;
      }
    }
  }

  return resultado;
}

// respaldo de lo que el profe hizo
int metodo_profe() {
  int resultado = 0;
  int s = 0, n = 0; // s:socket  n: contador
  char datos[256];  // para escribir lo que se lee
  struct sockaddr_in ipServidor;

  memset(datos, '0', sizeof(datos));

  if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    cout << "Error de creación de socket" << endl;
    resultado = 1;
  } else {
    ipServidor.sin_family = AF_INET;
    ipServidor.sin_port = htons(1337);
    ipServidor.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Se intenta pegar al servidor
    if (connect(s, (struct sockaddr *)&ipServidor, sizeof(ipServidor)) < 0) {
      cout << endl << "Error de conexión por IP o puerto" << endl;
      resultado = 2;
    } else {
      // Se logró pegar, se sacan datos
      while ((n = read(s, datos, sizeof(datos))) > 0) {
        datos[n] = 0;
        cout << endl << string(datos) << endl;
      }
      // No se logró leer
      if (n < 0) {
        cout << endl << "Error de lectura" << endl;
      }
    }
  }

  return resultado;
}