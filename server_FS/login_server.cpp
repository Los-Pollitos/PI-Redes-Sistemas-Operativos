/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
*/

#include "login_server.h"
#include "security.h"

/*
 * @brief Default constructor
*/
login_server::login_server() {
  // Create the file system
  this->file_system = new FS();
  this->connection = -1;
  this->message_count = 0;
  this->logger =  new log ("Login_LOG.txt", "Login Server");
  this->continue_waiting = true;
  // Load the file system from image
  std::ifstream current_file("fs_image.dat");
  if (current_file.is_open()) {
    current_file.close();
    // this->file_system->load_unit();
    this->load_from_file();
  } else {
    // Load the file system from file
    this->load_from_file();
  }
  // Set a seed to generate token for the first time
  srand(time(NULL));
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

  socklen_t l = sizeof(this->ipRemoto);
  char strIpRemoto[INET6_ADDRSTRLEN];
  int port;
  std::cout << std::endl << "[SERVIDOR LOGIN ESCUCHANDO]" << std::endl;
  while (this->continue_waiting) {
    // Search for a connection
    this->connection = accept(socketServidor, (struct sockaddr *)&ipRemoto, &l);

    // Found a connection
    if (this->connection != -1) {
      answer_request();
    }
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
    std::cout << "[SERVIDOR LOGIN RECIBIO]: " << this->data << std::endl;
    if (this->data[0] == '#') {
      close(this->connection);
    } else {
      // send request to log
      this->logger->add_to_log(strIpRemoto, "RECEIVED" ,this->data );
      this->process_data(strIpRemoto);
    }
  }
}

/**
 * @brief Gets data received from intermediary and answers the request
 * 
 * @param ip_remote The ip needed to generate the log entry
 */
void login_server::process_data(std::string ip_remote) {
  std::string username = "\0";
  std::string hash = "\0";
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
    case CHANGE_TOKEN:
      this->change_token();
      break;
    case CREATE_USER:
      this->create_user();
      break;
    case DELETE_USER:
      this->delete_user();
      break;
  }
  this->logger->add_answer_log(ip_remote, "SENT", this->data);
  this->file_system->write_unit();
}

/**
 * @brief Creates an user inside the login file when received with a
 * request to do so
 */
void login_server::create_user() {
  std::string username = "";
  std::string hash = "";
  // Obtain from data the username and hash information
  this->find_create_info(username, hash);
  // Set the data to \0
  memset(this->data, '\0', DATA_SIZE);
  // Assume the user exists
  this->data[0] = '0';
  if (!this->existing_user(username)) {
    // The user does not exist
    this->append_the_user(username,hash);
    // Change data to success
    this->data[0] = '1';
  }
  // Write to the intermediary the answer
  std::cout << "[SERVIDOR LOGIN -> INTERMEDIARIO] " << this->data << "\n";
  write(this->connection, this->data, DATA_SIZE);
}

/**
 * @brief Adds to the Login file the username, hash, and generates a token
 * 
 * @param username The desired username to be inserted
 * @param hash The associated hash to be inserted
 */
void login_server::append_the_user(std::string& username, std::string& hash) {
  // Prepare the string with the necessary info
  std::string to_write = username;
  to_write += "," + hash + ",";
  // Generate the token
  int current_token = 0;
  for (int i = 0; i < 6; ++i) {
    // Generate integer numbers between 10 and 99
    current_token = rand() % 90 + 10;
    to_write += std::to_string(current_token);
  }
  // Add a final comma
  to_write += ",";
  // Append it to the file
  // Open and close the file
  this->file_system->open("Server", "Login.txt");
  this->file_system->append("Login.txt", to_write);
  this->file_system->close("Server", "Login.txt");
}

/**
 * @brief Finds the username and hash to be added inside the datagram
 * 
 * @param username The username to be inserted
 * @param hash The hash to be associated to the username
 */
void login_server::find_create_info(std::string& username, std::string& hash) {
  // Used to store the position of the first comma
  int i = 2;
  for (i = 2; this->data[i] != ','; ++i) {
    // The other username, used for log only
  }
  // Increase one more to avoid the comma
  ++i;
  for (i; this->data[i] != ','; ++i) {
    username += this->data[i];
  }
  // Increase one more to avoid the comma
  ++i;
  for (i; this->data[i] != ','; ++i) {
    hash += this->data[i];
  }
}

/**
 * @brief Handles deletion of an user from the login file
 * 
 * @param username Username to be deleted
 */
void login_server::delete_user() {
  // Find the username
  std::string username = "";
  for (int i = 2; i < 12 && this->data[i] != ','; ++i) {
    username += this->data[i];
  }
  // Set the data to \0
  memset(this->data, '\0', DATA_SIZE);
  if (this->existing_user(username)) {
    // The user exists
    this->remove_the_user(username);
    this->data[0] = '1';
  } else {
    // The user does not exist, answer with 0
    this->data[0] = '0';
  }
  // Write to the intermediary the answer
  std::cout << "[SERVIDOR LOGIN -> INTERMEDIARIO] " << this->data << "\n";
  write(this->connection, this->data, DATA_SIZE);
}

/**
 * @brief Removes the username from the login file if it is confirmed
 * to exist in it
 * 
 * @param username Username to be deleted
 */
void login_server::remove_the_user(std::string& username) {
  std::vector<std::string> container;
  std::string buffer = "";
  this->file_system->open("Server", "Login.txt");
  this->file_system->reset_file_pointer("Server", "Login.txt");
  // Store the current contents
  while (!this->file_system->is_eof("Server", "Login.txt")) {
    buffer = this->file_system->read_until("Server", "Login.txt", ',');
    if (buffer != username) {
      // Store and read
      buffer += "," + this->file_system->read_until("Server", "Login.txt", ',');
      buffer += "," + this->file_system->read_until("Server", "Login.txt", ',');
      buffer += ",";
      container.emplace_back(buffer);
    } else {
      // Read the remaining information without storing it
      this->file_system->read_until("Server", "Login.txt", ',');
      this->file_system->read_until("Server", "Login.txt", ',');
    }
  }
  this->file_system->close("Server", "Login.txt");
  // Remove the login file
  this->file_system->erase("Login.txt");
  this->file_system->create("Login.txt");
  // Readd everything
  this->file_system->open("Server", "Login.txt");
  for (int i = 0; i < container.size(); ++i) {
    this->file_system->append("Login.txt", container[i]);
  }
  this->file_system->close("Server", "Login.txt");
}

/**
 * @brief Find if a username exists inside the file system
 * 
 * @param username The username to be found
 * @return true If the username exists 
 * @return false If the username does not exist
*/
bool login_server::existing_user(std::string& username) {
  bool answer = false;
  this->file_system->open("Server", "Login.txt");
  this->file_system->reset_file_pointer("Server", "Login.txt");
  std::string buffer = "";
  // Read the whole file or until the username is found
  while (buffer != username && !this->file_system->is_eof("Server", "Login.txt")) {
    buffer = this->file_system->read_until("Server", "Login.txt", ',');
    if (buffer != username) {
      // Read the hash and token
      this->file_system->read_until("Server", "Login.txt", ',');
      this->file_system->read_until("Server", "Login.txt", ',');
    } else {
      // THe username is found
      answer = true;
    }
  }
  // Close the login file
  this->file_system->close("Server", "Login.txt");
  return answer;
}

/**
 * @brief Finds the username and hash inside received data
 * 
 * @param username String where username will be placed
 * @param hash String where hash will be placed
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

/**
 * @brief Validates the username and hash of a user trying to log into the
 * system by answering the result to the client through the socket.
 * 
 * @param username String with the username to validate
 * @param hash String with the received hash of the user
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

/**
 * @brief Takes data and inserts received string into data
 * 
 * @param new_info Information to be inserted into data
 */
void login_server::adapt_data(std::string& new_info) {
    for (int i = 0; i < DATA_SIZE; ++i){
        this->data[i] = new_info[i];
    }
}

/**
 * @brief Sends a user's token to the server who asked for it
 * 
 */
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
      security security_manager;
      // buffer has username, now we want to ignore hash
      this->file_system->read_until("Server", "Login.txt", ',');
      // get token
      buffer  =  this->file_system->read_until("Server", "Login.txt", ',');
      buffer = security_manager.encrypt(buffer);
      std::string token_ascii = "";
      int i = 0;
      for (i = 0; i < 12; ++i) {
        token_ascii += std::to_string((int)buffer[i]);
        token_ascii += ',';
      }
      token_ascii += '\0';
      this->adapt_data(token_ascii);
    } else {
      this->data[0] = 'e'; // e == error
    }
    write(this->connection, this->data, DATA_SIZE);
    this->file_system->close("Server", "Login.txt");
  }
}

/**
 * @brief Changes the password form received user (inside data) for a new password that
 * is also received in data.
 */
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

/**
 * @brief Extracts usernamen and new token in order to change it
 * in the file system
 */
void login_server::change_token() {
  std::string username = "";
  std::string new_token = "";
  int i = 1;
  for (i = 1; i < DATA_SIZE && this->data[i] != ','; ++i) {
    // discard first user (it is just for log)
  }
  for (i = i+1; i < DATA_SIZE && this->data[i] != ','; ++i) {
    if (this->data[i] != ',') {
      username += this->data[i];
    }
  }
  ++i; // skip comma
  for (int j = 0; j < 12; ++j) {
      if (this->data[i+1] == ',') {
          new_token += (char)(this->data[i]-48);
      } else if (this->data[i+2] == ','){
        new_token += (char)(((int)this->data[i]) - 48)*10 +(((int)this->data[i+1]) - 48);
      ++i; // ignore i+1
      } else {
        new_token += (char)(((int)this->data[i] - 48)*100 + ((int)this->data[i+1] -48)*10 - +(((int)this->data[i+2] -48)));
        i+=2; // ignore i+2
      }
      // next one would be a ,
      i+=2;
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
      buffer = this->file_system->read_until("Server", "Login.txt", ',');
      // modify token
      security security_manager;
      new_token = security_manager.decrypt(new_token);
      this->file_system->write("Server","Login.txt", new_token);
      memset(this->data, '\0', DATA_SIZE);
      this->data[0] = '1';
    } else {
      this->data[0] = '0';
    }
    write(this->connection, this->data, strlen(this->data));
    this->file_system->close("Server", "Login.txt");
  }
 }