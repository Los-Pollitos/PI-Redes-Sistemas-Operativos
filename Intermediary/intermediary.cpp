/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
 */

#include "intermediary.h"

/**
 * @brief Construct a new intermediary::intermediary object
 * 
 */
intermediary::intermediary() {
  this->logger = new log ("intermediary_LOG.txt", "Intermediary Server");
  this->decrypter = new common();
  this->continue_waiting = true;
  this->client_port = PORT_C;

  std::string encrypted;
  std::string temp;

  std::ifstream config_file("intermediary.config");
    if (config_file.is_open()) {
      // file system
      getline(config_file, encrypted);
      this->decrypter->decrypt(encrypted, this->file_system_ip);
      getline(config_file, encrypted);
      this->decrypter->decrypt(encrypted, temp);
      this->file_system_port = std::stoi(temp);

      // data base
      getline(config_file, encrypted);
      this->decrypter->decrypt(encrypted, this->data_base_ip);
      getline(config_file, encrypted);
      this->decrypter->decrypt(encrypted, temp);
      this->data_base_port = std::stoi(temp);

      config_file.close();
    } else {
        std::cout << "ERROR: config file no existente";
    }

    std::cout << this->file_system_ip << "\n";
    std::cout << this->file_system_port << "\n";
    std::cout << this->data_base_ip << "\n";
    std::cout << this->data_base_port << "\n";
}

/**
 * @brief Destroy the intermediary::intermediary object
 * 
 */
intermediary::~intermediary() {
  delete this->logger;
  delete this->decrypter;
}

/*
 * @brief The intermediary waits for a request from a client to answer it.
 */
void intermediary::wait_for_request() {
  int socketServidor = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in ip;

  memset(&ip, '0', sizeof(ip));
  memset(this->data, '\0', sizeof(this->data));
  ip.sin_family = AF_INET;
  ip.sin_addr.s_addr = htonl(INADDR_ANY);
  ip.sin_port = htons(this->client_port);

  bind(socketServidor, (struct sockaddr*)& ip, sizeof(ip));
  listen(socketServidor, 20);

  socklen_t l = sizeof(this->ipRemoto);
  char strIpRemoto[INET6_ADDRSTRLEN];
  int port;
  std::cout << std::endl << "[INTERMEDIARIO ESCUCHANDO]" << std::endl;
  while (continue_waiting) {
    // Search for a connection
    this->connection = accept(socketServidor, (struct sockaddr *)&ipRemoto, &l);

    // Found a connection
    if (this->connection != -1) {
      answer_request();
    }
  }

  std::cout << std::endl << "[INTERMEDIARIO DETENIDO]" << std::endl;
}

/*
 * @brief The intermediaty answers a request from a client.
*/
void intermediary::answer_request() {
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
    std::cout << "[INTERMEDIARIO RECIBE DE CLIENTE] " << this->data << std::endl;
    if (this->data[0] == '#') {
      close(this->connection);
    } else {
      this->logger->add_to_log(strIpRemoto, "FROM_CLIENT", this->data);
      this->send_to_server(strIpRemoto);
    }
  }
}

/**
 * @brief Sends and receives one message to/from login server
 * 
 * @param ip_remote Ip to save in log
 * @return std::string String received from login server
 */
std::string intermediary::send_and_receive_login(std::string ip_remote) {
  std::string result = "\0";
  int s = 0, n = 0; // s:socket  n: contador
  struct sockaddr_in ipServidorLogin;

  if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    std::cout << "Error de creación de socket" << std::endl;
    this->logger->add_answer_log(ip_remote, "ERROR", "Error de creación de socket");

  } else {
    ipServidorLogin.sin_family = AF_INET;
    ipServidorLogin.sin_port = htons(this->file_system_port);
    ipServidorLogin.sin_addr.s_addr = inet_addr(this->file_system_ip.data());

    // Attempt connection with login server
    if (connect(s, (struct sockaddr *)&ipServidorLogin, sizeof(ipServidorLogin)) < 0) {
      std::cout << std::endl << "Error de conexión por IP o puerto con login" << std::endl;
      this->logger->add_answer_log(ip_remote, "ERROR", "Error de conexión por IP o puerto con login");
      // Prepare answer to be the error
      result = "LOGIN_SERVER_ERROR";
    } else {
      std::cout << "[INTERMEDIARIO -> AUTENTICACION] " << this->data  << std::endl;
      write(s, this->data, DATA_SIZE);
      this->logger->add_to_log(ip_remote, "TO_LOGIN", this->data);

      if ((n = read(s, this->data, DATA_SIZE)) > 0) {
        std::cout << "[INTERMEDIARIO RECIBE DE AUTENTICACION] " << this->data << std::endl;
        result = this->data;
        this->logger->add_answer_log(ip_remote, "FROM_LOGIN", this->data);
      }
      
      memset(this->data, '0', DATA_SIZE);
      data[0] = '#';
      std::cout << "[INTERMEDIARIO -> AUTENTICACION] " << data << std::endl;
      write(s, this->data, DATA_SIZE);
      if (n < 0) {
        std::cout << std::endl << "Error de lectura" << std::endl;
        this->logger->add_answer_log(ip_remote, "ERROR", "Error de lectura");

      }
    }
  }
  return result;
}

/**
 * @brief Sends and receives one or several message(s) to/from data server. Those
 * messages are inmediately sent back client.
 * 
 * @param ip_remote Ip to save in log
 */
void intermediary::send_and_receive_data_base(std::string ip_remote) {
  int s = 0, n = 1; // s:socket  n: contador
  struct sockaddr_in ip_data_server;

  if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    std::cout << "Error de creación de socket" << std::endl;
    this->logger->add_answer_log(ip_remote, "ERROR", "Error de creación de socket");
    
  } else {
    ip_data_server.sin_family = AF_INET;
    ip_data_server.sin_port = htons(this->data_base_port);
    ip_data_server.sin_addr.s_addr = inet_addr(this->data_base_ip.data());

    // Se intenta pegar al servidor
    if (connect(s, (struct sockaddr *)&ip_data_server, sizeof(ip_data_server)) < 0) {
      std::cout << std::endl << "Error de conexión por IP o puerto con la base de datos" << std::endl;
      this->logger->add_answer_log(ip_remote, "ERROR", "Error de conexión por IP o puerto con la base de datos");
      // Handle the error
      std::string answer = "DATA_SERVER_ERROR";
      write(this->connection, answer.data(), DATA_SIZE);
      memset(this->data, '\0', DATA_SIZE);
      this->data[0] = '&';
      write(this->connection, this->data, DATA_SIZE);
      read(this->connection, this->data, sizeof(this->data));
      std::cout << "[INTERMEDIARIO RECIBE DE CLIENTE] " << this->data << std::endl;
      read(this->connection, this->data, sizeof(this->data));
      std::cout << "[INTERMEDIARIO RECIBE DE CLIENTE] " << this->data << std::endl;
    } else {
      // receive everything from client
      while (this->connection != -1 && n > 0 && this->data[0] != '&') {
          std::cout << "[INTERMEDIARIO -> DATOS] " << this->data << std::endl;
          write(s, this->data, DATA_SIZE);
          this->logger->add_to_log(ip_remote, "TO_DATABASE", this->data);
          n = read(this->connection, this->data, sizeof(this->data));
          std::cout << "[INTERMEDIARIO RECIBE DE CLIENTE]" << this->data << std::endl;
          if (this->data[0] != '&') {
           this->logger->add_answer_log(ip_remote, "FROM_CLIENT", this->data);
          }
      }
      // send & to server
      write(s, this->data, DATA_SIZE);
      
      // receive everything from server
      this->data[0] = 'a';
      while (s != -1 && n > 0 && this->data[0] != '&') { 
        if ((n = read(s, this->data, DATA_SIZE)) > 0) {
          // connection es socket cliente
          std::cout << "[INTERMEDIARIO RECIBE DE DATOS] " << this->data << std::endl;
          write(this->connection, this->data, DATA_SIZE);
          if (this->data[0] != '&') {
            this->logger->add_answer_log(ip_remote, "FROM_DATABASE", this->data);
            this->logger->add_answer_log(ip_remote, "TO_CLIENT", this->data);
          }
        }
      }
      
      memset(this->data, '\0', DATA_SIZE);
      data[0] = '#';
      std::cout << "[INTERMEDIARIO -> DATOS] " << data << std::endl;
      write(s, this->data, DATA_SIZE);
      // No se logró leer
      if (n < 0) {
        std::cout << std::endl << "Error de lectura" << std::endl;
        this->logger->add_answer_log(ip_remote, "ERROR", "Error de lectura");
      }
    }
  }
}

/**
 * @brief Method to handle after the create user char was found
 * 
 * @param ip_remote Ip to handle log and answers
 */
void intermediary::manage_user_case(std::string ip_remote) {
  char temporal_data[DATA_SIZE];
  // Check the server to send the information
  if (data[1] == '1') {
    this->send_and_receive_data_base(ip_remote);
  } else {
    // Remove the &
    read(this->connection, temporal_data, DATA_SIZE);
    std::string answer = this->send_and_receive_login(ip_remote);
    write(this->connection, answer.data(), DATA_SIZE);
    memset(this->data, '\0', DATA_SIZE);
    this->data[0] = '&';
    write(this->connection, this->data, DATA_SIZE);
  }
}

void intermediary::modify_network_case(std::string ip_remote) {
  // Package is meant for this server
  if (this->data[1] == '1') {
    this->set_up_intermediary(ip_remote);
  } else {
    // Package is for FS
    if (this->data[1] == '2') {
      this->set_up_file_system(ip_remote);
    } else {
      this->set_up_data_base(ip_remote);
    }
  }
  
}

void intermediary::set_up_intermediary(std::string ip_remote) {
  char temporal_data[DATA_SIZE];
  // Remove the &
  read(this->connection, temporal_data, DATA_SIZE);

  std::ofstream config_file("intermediary.config", std::fstream::trunc);

  std::string current = "";
  for(int i = 2; i < DATA_SIZE; ++i) {
    if (this->data[i] != ':') {
      current += this->data[i];
    } else {
       current += "\n\0";
       config_file << current;
       current = "";
    }
  }
  // Answer with success
  current = "1";
  write(this->connection, current.data(), DATA_SIZE);
  memset(this->data, '\0', DATA_SIZE);
  this->data[0] = '&';
  write(this->connection, this->data, DATA_SIZE);
}

void intermediary::set_up_file_system(std::string ip_remote) {
  char temporal_data[DATA_SIZE];
  // Remove the &
  read(this->connection, temporal_data, DATA_SIZE);
  std::string answer = this->send_and_receive_login(ip_remote);
  write(this->connection, answer.data(), DATA_SIZE);
  memset(this->data, '\0', DATA_SIZE);
  this->data[0] = '&';
  write(this->connection, this->data, DATA_SIZE);
}

void intermediary::set_up_data_base(std::string ip_remote) {
  this->send_and_receive_data_base(ip_remote);
}

void intermediary::login_requests(std::string ip_remote) {
  std::string to_send_back = "\0";
  to_send_back = this->send_and_receive_login(ip_remote);
  // Reads the '&' that won't be used
  read(this->connection, this->data, DATA_SIZE);
  write(this->connection, to_send_back.data(), DATA_SIZE);
  this->logger->add_answer_log(ip_remote, "TO_CLIENT", to_send_back.data());
  to_send_back[0] = '&';
  write(this->connection, to_send_back.data(), DATA_SIZE);
}

/**
 * @brief This method extracts the first char of the received data
 * and checks which server must receive the information
 * 
 * @param ip_remote Ip to save into log
 */
void intermediary::send_to_server(std::string ip_remote) {
  switch(data[0]) {
    case LOGIN:
    case TOKEN:
    case CHANGE_PASSWORD:
    case CHANGE_TOKEN:
      this->login_requests(ip_remote);
      break;
    case CREATE_USER:
    case DELETE_USER:
      this->manage_user_case(ip_remote);
      break;
    case PAYMENT_PROOF:
      this->send_and_receive_data_base(ip_remote);
      break;
    case WORK_PROOF:
      this->send_and_receive_data_base(ip_remote);
      break;
    case SALARY_PROOF:
      this->send_and_receive_data_base(ip_remote);
      break;
    case SALARY_CONSULT:
      this->send_and_receive_data_base(ip_remote);
      break;
    case VACATION_REQUEST:
      this->send_and_receive_data_base(ip_remote);
      break;
    case CONSULT_VACATION:
      this->send_and_receive_data_base(ip_remote);
      break;
    case ANSWER_PAYMENT_PROOF: case ANSWER_WORK_PROOF: case ANSWER_SALARY_PROOF:
    case RECORD_CONSULT: case ADD_RECORD:
    case USER_OFFICE: case ALL_USERS_OFFICE: case ALL_USERS: case DATA_USER:
    case GET_ROLES:
    case CHANGE_PHONE: case CHANGE_EMAIL: case CHANGE_OFFICE_ID: case CHANGE_ROLES:
    case CHANGE_LABORAL_DATA: case CHANGE_VACATIONS: case CHANGE_SHIFT:
    case FIRE_EMPLOYEE:
    case SEE_PROCESS_REQUESTS: case PROCESS_REQUESTS:
    case SEE_CONSULT_REQUESTS: case CONSULT_REQUESTS:
    case ALL_OFFICES: case CREATE_OFFICE: case MODIFY_OFFICE_NAME: case DELETE_OFFICE:
      this->send_and_receive_data_base(ip_remote);
      break;
    case MODIFY_NETWORK:
        this->modify_network_case(ip_remote);
      break;
    default:
      std::cerr << "Error: codigo inexistente" << std::endl;
      this->logger->add_answer_log(ip_remote, "ERROR", "Código inexistente");
  }
}
