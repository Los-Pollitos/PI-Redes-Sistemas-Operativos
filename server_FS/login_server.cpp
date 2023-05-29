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
// TODO(nosotros): bool de que no haga nada si no hay archivo
login_server::login_server() {
  // Create the file system
  this->file_system = new FS();
  this->connection = -1;
  this->message_count = 0;

  // Load the file system from image
  std::ifstream current_file("fs_image.dat");
  if (current_file.is_open()) {
    current_file.close();
    this->file_system->load_unit();
  } else {
    // Load the file system from file
    this->load_from_file();
  }
}

/*
 * @brief Destructor
 */
login_server::~login_server() {
  // Unload the image of the file system
  this->file_system->write_unit();
  // Delete the file system
  delete this->file_system;
}

// TODO(nostros): documentar
void login_server::load_from_file() {
  std::ifstream file("Login.txt");
  if (file.is_open()) {
    std::string buffer;
    // Create the file in the file system
    this->file_system->create("Login.txt", true);
    this->file_system->open("Server", "Login.txt");
    while (std::getline(file, buffer)) {
      this->file_system->append("Login.txt", buffer);
    }
    this->file_system->close("Server", "Login.txt");
    // Unload the image of the file system
    this->file_system->write_unit();
  } else {
    std::cerr << "No hay archivo de Login.txt" << std::endl;
  }
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
    } else {
      // Obtain information from buffer
      std::string username = "";
      std::string hash = "";
      this->find_data(username, hash);
      
      // TODO(nosotros): BORRAR
      std::cout << "username:" << username << "\n";
      std::cout << "hash:" << hash << "\n";

      // TODO(nosotros): descomentar
      this->validate_data(username, hash);
    }
  }
}

void login_server::find_data(std::string& username, std::string& hash) {
  int i;
  for (i = 0; i < DATA_SIZE && this->data[i] != ','; ++i) {
    if (this->data[i] != ',') {
      username += this->data[i];
    }
  }
  for (int j = i + 1; j < HASH_SIZE + i + 1; ++j) {
    hash += this->data[j];
  }
}

// TODO(nostros): documentar
void login_server::validate_data(std::string& username, std::string& hash) {
  this->file_system->open("Server", "Login.txt");
  if (this->file_system->is_open("Login.txt")) {
    // TODO(nosotros): BORRAR
    std::cout << "Si abri archivo " << std::endl;

    this->file_system->reset_file_pointer("Server", "Login.txt");
    bool found = false;
    std::string buffer = " ";

    // Find the username in the file
    bool end_of_file = this->file_system->is_eof("Server", "Login.txt");
    while (end_of_file == false && found == false) {
      buffer = this->file_system->read_until("Server", "Login.txt", ',');

      // TODO(us): borrar
      std::cout << "buffer: " << buffer << "\nusername: " << username << "\n  son iguales: " << (username==buffer) << std::endl;

      if (buffer != username) {
        // Read the rest of the data
        buffer = this->file_system->read_line("Server", "Login.txt");
      } else {
        found = true;

        // TODO(us): borrar
        std::cout << "estoy en else___________________________________________________________________________________" << std::endl;
      }
      buffer = " ";
      end_of_file = this->file_system->is_eof("Server", "Login.txt");
    }
    //TODO(nosotros): definir si cambiar por \0
    memset(this->data, '0', sizeof(this->data));

    // Compare
    if (found) {
      // buffer has username, now we want hash
      buffer = this->file_system->read_until("Server", "Login.txt", ',');

      // TODO(us): borrar
      std::cout << "buffer: " << buffer << "\nhash: " << hash << "\n  son iguales: " << (hash==buffer) << std::endl;

      if (buffer == hash) {
        this->data[0] = '1';

        // TODO(us): borrar
        std::cout << "estoy en if" << std::endl;

      }
    }
    std::cout << "voy a mandar un " << this->data << std::endl;
    write(this->connection, this->data, strlen(this->data));
    this->file_system->close("Server", "Login.txt");
  }
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