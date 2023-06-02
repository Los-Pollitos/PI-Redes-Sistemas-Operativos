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
  char* data = new char[MAX_SIZE];  // para escribir lo que se lee
  struct sockaddr_in ipServidor;

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
      // Se logró pegar, se sacan data
      memset(data, '0', MAX_SIZE);
      string new_info = "0cjimenez,78e8ee0b2f67531b8eda7678fa42fb";
      adapt_data(data, new_info);
      std::cout << "Voy a mandar: " << data << std::endl;
      write(s, data, strlen(data));

      if ((n = read(s, data, MAX_SIZE)) > 0) {
        // connection es socket cliente
        std::cout << "Recibi: " << data << std::endl;
      }
      
      memset(data, '1', MAX_SIZE);
      data[0] = '#';
      std::cout << "Voy a mandar: " << data << std::endl;
      write(s, data, strlen(data));
      // No se logró leer
      if (n < 0) {
        cout << endl << "Error de lectura" << endl;
      }
    }
    delete [] data;
  }
  return resultado;
}