// EJEMPLO DE SOCKETS - SOCKETS LINUX - ricardo.gang@ucr.ac.cr

// OJO:

using namespace std;

int main() {
  char datos[256]; // lo que es enviado al cliente
  int socketServidor = 0;
  int conexion = -1; // cliente
  int n = 0;
  struct sockaddr_in ip;
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
          write(conexion, datos, strlen(datos));
        }
      }
    }
    sleep(1);
  }

  cout << endl << "[SERVIDOR DETENIDO]" << endl;
  return 0;
}

// Respaldo del metodo original
int metodo_profe() {
  char datos[256]; // lo que es enviado al cliente
  int socketServidor = 0, conexion = 0;
  struct sockaddr_in ip;
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
    // Hubo una conexión
    if (conexion != -1) {
      cout << "[MENSAJE RECIBIDO] #" << ++msjs;
      struct sockaddr_in *s = (struct sockaddr_in *)&ipRemoto;
      port = ntohs(s->sin_port);
      inet_ntop(AF_INET, &s->sin_addr, strIpRemoto, sizeof strIpRemoto);
      cout << " IP Remoto: " << strIpRemoto << endl;

      string msj = "El servidor ha recibido " + to_string(msjs) + " mensajes.";
      msj.copy(datos, msj.size() + 1);

      write(conexion, datos, strlen(datos));
      close(conexion);
    }
    sleep(1);
  }

  cout << endl << "[SERVIDOR DETENIDO]" << endl;
  return 0;
}
