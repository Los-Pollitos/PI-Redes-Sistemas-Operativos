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
  this->logger =  new log ("Login_LOG.txt", "Login Server");
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
  delete this->logger;
}

/*
 * @brief Loads the file system from a .txt file containing the necessary
 * login information, creating the image of the file system for future uses.
*/
void login_server::load_from_file() {
  //TODO borrar print
  std::cout << "No existe imagen de FS, se va a cargar de archivo\n";

  std::ifstream file("Login.txt");
  if (file.is_open()) {
    std::string buffer;
    // Create the file in the file system
    this->file_system->create("Login.txt", true);
    this->file_system->open("Server", "Login.txt");
    while (std::getline(file, buffer)) {
      buffer += ',';
      this->file_system->append("Login.txt", buffer);
    }
    this->file_system->close("Server", "Login.txt");
    // Unload the image of the file system
    this->file_system->write_unit();
  } else {
    std::cerr << "No hay archivo de Login.txt" << std::endl;
  }
}

/*
 * @brief The server waits for a request from a client to answer it.
 */
void login_server::wait_for_request() {
  int socketServidor = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in ip;

  memset(&ip, '0', sizeof(ip));
  memset(this->data, '\0', sizeof(this->data));
  ip.sin_family = AF_INET;
  ip.sin_addr.s_addr = htonl(INADDR_ANY);
  ip.sin_port = htons(PORT);

  bind(socketServidor, (struct sockaddr*)& ip, sizeof(ip));
  listen(socketServidor, 20);

  sleep(1);
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
    sleep(1);
  }

  std::cout << std::endl << "[SERVIDOR DETENIDO]" << std::endl;
}

/*
 * @brief The server answers a request from a client, validating
 * the data of the user in the file system.
*/
void login_server::answer_request() {
  std::cout << "[MENSAJE RECIBIDO] #" << ++this->message_count;

  char strIpRemoto[INET6_ADDRSTRLEN];
  struct sockaddr_in *s = (struct sockaddr_in*)& this->ipRemoto;
  int port = ntohs(s->sin_port);
  int n = 0;

  inet_ntop(AF_INET, &s->sin_addr, strIpRemoto, sizeof strIpRemoto);
  std::cout << " IP Remoto: " << strIpRemoto << std::endl;
  while (this->connection != -1 &&
         (n = read(this->connection, this->data, DATA_SIZE)) > 0) {
    // connection es socket cliente
    std::cout << "Recibi: " << this->data << std::endl;
    if (this->data[0] == '#') {
      close(this->connection);
    } else {
      // send request to log
      this->logger->add_to_log(strIpRemoto, "received" ,this->data );
      this->process_data(strIpRemoto);
    }
  }
}

// TODOD (us): Document
void login_server::process_data(std::string ip_remote) {
  std::string username = "\0";
  std::string hash = "\0";
  // TODO (stoi)
  switch (data[0]) {
    case LOGIN:
      // Obtain information from buffer
      this->find_data(username, hash);
      this->validate_data(username, hash);
      break;
    case TOKEN: 
      this->give_token();
      break;
    case CHANGE_PASSWORD:
      this->change_password();
      break;
    case CREATE_USER:
      // TODO(luis): hacer (data tiene que quedar con lo que retornó para que la bitácora lo diga)
      this->create_user(username, hash);
      break;
    case DELETE_USER:
      // TODO(luis): hacer (data tiene que quedar con lo que retornó para que la bitácora lo diga)
      username = "hola de login";
      write (this->connection, username.data(), DATA_SIZE);
      break;
  }
  this->logger->add_answer_log(ip_remote,"sent",this->data);
}

//TODO(Luis): documentar y terminar
void login_server::create_user(std::string& username,  std::string& hash) {
  // Find if the user already exists
  if (!this->existing_user(username)) {
    // If not, insert the user with the hash and generate a token
  } else {
    // Answer the request with a 0 indicating failure
  }
}

/**
 * @brief Find if a username exists inside the file system
 * 
 * @param username The username to be found
 * @return true If the username exists 
 * @return false If the username does not exist
*/
bool login_server::existing_user(std::string& username) {
  //TODO(Luis): Hacer
  bool answer = false;
  return answer;
}

// TODO(nosotros): actualizar documentacion
/*
 * @brief Deletes a folder. After this method, it is recomended that the user
 * sets the path in which they want to be.
 *
 * @param user Indicates the username
 * @param folder Indicates the folder that will be deleted
*/
void login_server::find_data(std::string& username, std::string& hash) {
  int i;
  for (i = 1; i < DATA_SIZE && this->data[i] != ','; ++i) {
    if (this->data[i] != ',') {
      username += this->data[i];
    }
  }
  for (int j = i + 1; j < HASH_SIZE + i + 1; ++j) {
    hash += this->data[j];
  }
}

/* 
 * @brief Validates the username and hash of a user trying to log into the
 * system by answering the result to the client through the socket.
*/
void login_server::validate_data(std::string& username, std::string& hash) {
  this->file_system->open("Server", "Login.txt");
  if (this->file_system->is_open("Login.txt")) {
    this->file_system->reset_file_pointer("Server", "Login.txt");
    bool found = false;
    std::string buffer = " ";

    // Find the username in the file
    bool end_of_file = this->file_system->is_eof("Server", "Login.txt");
    while (end_of_file == false && found == false) {
      buffer = this->file_system->read_until("Server", "Login.txt", ',');
      if (buffer != username) {
        // Read the rest of the data
        // descard passsword hash
        buffer = this->file_system->read_until("Server", "Login.txt", ',');
        //discard token
        buffer = this->file_system->read_until("Server", "Login.txt", ',');
      } else {
        found = true;
      }
      buffer = " ";
      end_of_file = this->file_system->is_eof("Server", "Login.txt");
    }
    memset(this->data, '\0', DATA_SIZE);

    // Compare
    if (found) {
      // buffer has username, now we want hash
      buffer = this->file_system->read_until("Server", "Login.txt", ',');
      if (buffer == hash) {
        this->data[0] = '1';
      } else {
        this->data[0] = '0';
      }
    } else {
      this->data[0] = '0';
    }
    write(this->connection, this->data, DATA_SIZE);
    this->file_system->close("Server", "Login.txt");
  }
}

void login_server::adapt_data(std::string& new_info) {
    for (int i = 0; i < DATA_SIZE; ++i){
        this->data[i] = new_info[i];
    }
}

void login_server::give_token(){
  std::string username = "";
  for (int i = 1; i < DATA_SIZE && this->data[i] != ','; ++i) {
    if (this->data[i] != ',') {
      username += this->data[i];
    }
  }

  // Open file in file system
  this->file_system->open("Server", "Login.txt");
  if (this->file_system->is_open("Login.txt")) {
    this->file_system->reset_file_pointer("Server", "Login.txt");
    bool found = false;
    std::string buffer = " ";

    // Find the username in the file
    bool end_of_file = this->file_system->is_eof("Server", "Login.txt");
    while (end_of_file == false && found == false) {
      buffer = this->file_system->read_until("Server", "Login.txt", ',');
      if (buffer != username) {
        // Discard hash
        buffer = this->file_system->read_until("Server", "Login.txt", ',');
        // Discard token
        buffer = this->file_system->read_until("Server", "Login.txt", ',');
      } else {
        found = true;
      }
      buffer = " ";
      end_of_file = this->file_system->is_eof("Server", "Login.txt");
    }
    memset(this->data, '\0', DATA_SIZE);

    // Extract token
    if (found) {
      // buffer has username, now we want to ignore hash
      this->file_system->read_until("Server", "Login.txt", ',');
      buffer  =  this->file_system->read_until("Server", "Login.txt", ',');
      memset(this->data, '\0', DATA_SIZE);
      this->adapt_data(buffer); 
    } else {
      this->data[0] = 'e'; // e == error
    }
    write(this->connection, this->data, strlen(this->data));
    this->file_system->close("Server", "Login.txt");
  }
}


void login_server::change_password() {
  // find username and new_hash in data
  std::string username = "";
  std::string new_hash = "";
  this->find_data(username, new_hash);

  // Open file in file system
  this->file_system->open("Server", "Login.txt");
  if (this->file_system->is_open("Login.txt")) {
    this->file_system->reset_file_pointer("Server", "Login.txt");
    bool found = false;
    std::string buffer = " ";

    // Find the username in the file system
    bool end_of_file = this->file_system->is_eof("Server", "Login.txt");
    while (end_of_file == false && found == false) {
      buffer = this->file_system->read_until("Server", "Login.txt", ',');
      if (buffer != username) {
        // Discard hash
        buffer = this->file_system->read_until("Server", "Login.txt", ',');
        // Discard token
        buffer = this->file_system->read_until("Server", "Login.txt", ',');
      } else {
        found = true;
      }
      buffer = " ";
      end_of_file = this->file_system->is_eof("Server", "Login.txt");
    }
    memset(this->data, '\0', DATA_SIZE);

    // change hash
    if (found) {
      this->file_system->write("Server", "Login.txt", new_hash);
      this->data[0] = '1';
    } else {
      this->data[0] = 'e';
    }
    write(this->connection, this->data, strlen(this->data));
    this->file_system->close("Server", "Login.txt");
  }
}