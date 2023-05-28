#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define MAX_SIZE 256

using namespace std;

void adapt_data(char* data, string& new_info) {
  for (int i = 0; i < new_info.length(); ++i){
    data[i] = new_info[i];
  }
}

int main() {
  int resultado = 0;
  int s = 0, n = 0; // s:socket  n: contador
  char datos[MAX_SIZE];  // para escribir lo que se lee
  struct sockaddr_in ipServidor;

  // memset(datos, '0', sizeof(datos));

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
      memset(datos, '0', sizeof(datos));
      string new_info = "cjimenez,78e8ee0b2f67531b8eda7678fa42fb";
      adapt_data(datos, new_info);
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
