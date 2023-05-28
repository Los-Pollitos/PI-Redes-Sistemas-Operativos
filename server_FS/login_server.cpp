/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
*/

#include "login_server.h"

/*
 * @brief Default constructor
 */
login_server::login_server() {
  // Create the file system
  this->file_system = new FS();
  this->connection = -1;
  this->message_count = 0;

  // TODO(nosotros): Load the file system
}

/*
 * @brief Destructor
 */
login_server::~login_server() {
  // TODO(nosotros): Unload the file system

  // Delete the file system
  delete this->file_system;
}

// TODO(nostros): documentar
void login_server::wait_for_request() {
  int socketServidor = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in ip;

  memset(&ip, '0', sizeof(ip));
  memset(this->data, '0', sizeof(this->data));
  ip.sin_family = AF_INET;
  ip.sin_addr.s_addr = htonl(INADDR_ANY);
  ip.sin_port = htons(1337);

  bind(socketServidor, (struct sockaddr*)& ip, sizeof(ip));
  listen(socketServidor, 20);

  sleep(1); // TODO(nosotros): ver si quitar
  socklen_t l = sizeof(this->ipRemoto);
  char strIpRemoto[INET6_ADDRSTRLEN];
  int port;
  std::cout << std::endl << "[SERVIDOR ESCUCHANDO]" << std::endl;
  while (this->message_count < 5000) {
    // Search for a connection
    this->connection = accept(socketServidor, (struct sockaddr *)&ipRemoto, &l);

    // Found a connection
    if (this->connection != -1) {
      answer_request();
    }
    sleep(1); // TODO(nosotros): pensar en quitar
  }

  std::cout << std::endl << "[SERVIDOR DETENIDO]" << std::endl;
}

// TODO(nostros): documentar
void login_server::answer_request() {
  std::cout << "[MENSAJE RECIBIDO] #" << ++this->message_count;

  char strIpRemoto[INET6_ADDRSTRLEN];
  struct sockaddr_in *s = (struct sockaddr_in*)& this->ipRemoto;
  int port = ntohs(s->sin_port);
  int n = 0;

  inet_ntop(AF_INET, &s->sin_addr, strIpRemoto, sizeof strIpRemoto);
  std::cout << " IP Remoto: " << strIpRemoto << std::endl;

  // std::string msj_temp = "El servidor ha recibido " + std::to_string(this->message_count) + " mensajes.";
  // msj_temp.copy(this->data, msj_temp.size() + 1);

  while (this->connection != -1 &&
         (n = read(this->connection, this->data, sizeof(this->data))) > 0) {
    // connection es socket cliente
    std::cout << "Recibi: " << this->data << std::endl;
    if (this->data[0] == '#') {
      close(this->connection);
      std::cout << "Voy a apagar" << std::endl;
    }
    // validate data:
    validate_data();
  }
}

// TODO(nostros): documentar
void login_server::validate_data() {
  // TODO(nosotros): hacer
  write(this->connection, this->data, strlen(this->data));
}

int main() {
  login_server* server = new login_server();
  server->wait_for_request();
  delete server;
}

/*
// TODO(nosotros): CAMBIAR Y BORRAR
int main() {
  char datos[256]; // lo que es enviado al cliente
  int socketServidor = 0;
  int conexion = -1; // cliente
  int n = 0;
  struct sockaddr_in ip;

  // wait:
  socketServidor = socket(AF_INET, SOCK_STREAM, 0);

  memset(&ip, '0', sizeof(ip));
  memset(datos, '0', sizeof(datos));
  ip.sin_family = AF_INET;
  ip.sin_addr.s_addr = htonl(INADDR_ANY);
  ip.sin_port = htons(1337);

  bind(socketServidor, (struct sockaddr *)&ip, sizeof(ip));
  listen(socketServidor, 20);

  // Cantidad de mensajes recibidos
  int msjs = 0;
  sleep(1);
  struct sockaddr_storage ipRemoto;
  socklen_t l = sizeof(ipRemoto);
  char strIpRemoto[INET6_ADDRSTRLEN];
  int port;
  cout << endl << "[SERVIDOR ESCUCHANDO]" << endl;
  while (msjs < 5000) {
    // Se busca una conexión
    conexion = accept(socketServidor, (struct sockaddr *)&ipRemoto, &l);


    // conexion:
    // Hubo una conexión
    if (conexion != -1) {
      cout << "[MENSAJE RECIBIDO] #" << ++msjs;
      struct sockaddr_in *s = (struct sockaddr_in *)&ipRemoto;
      port = ntohs(s->sin_port);
      inet_ntop(AF_INET, &s->sin_addr, strIpRemoto, sizeof strIpRemoto);
      cout << " IP Remoto: " << strIpRemoto << endl;

      string msj = "El servidor ha recibido " + to_string(msjs) + " mensajes.";
      msj.copy(datos, msj.size() + 1);

      while (conexion != -1 && (n = read(conexion, datos, sizeof(datos))) > 0) {
        // conexion es socket cliente
        std::cout << "Recibi: " << datos << std::endl;
        if (datos[0] == '#') {
          close(conexion);
          std::cout << "Voy a apagar" << std::endl;
        } else {
          // validate data:
          write(conexion, datos, strlen(datos));
        }
      }
    }
    sleep(1);
  }

  cout << endl << "[SERVIDOR DETENIDO]" << endl;
  return 0;
}
*/