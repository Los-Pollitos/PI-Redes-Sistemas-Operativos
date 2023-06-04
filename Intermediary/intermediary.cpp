/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
 */

#include "intermediary.h"

// TODO(us): documentar
intermediary::intermediary() {

}

// TODO(us): documentar
intermediary::~intermediary() {
  
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
  ip.sin_port = htons(PORT_C);

  bind(socketServidor, (struct sockaddr*)& ip, sizeof(ip));
  listen(socketServidor, 20);

  sleep(1);
  socklen_t l = sizeof(this->ipRemoto);
  char strIpRemoto[INET6_ADDRSTRLEN];
  int port;
  std::cout << std::endl << "[INTERMEDIARIO ESCUCHANDO]" << std::endl;
  while (this->message_count < 5000) {
    // Search for a connection
    this->connection = accept(socketServidor, (struct sockaddr *)&ipRemoto, &l);

    // Found a connection
    if (this->connection != -1) {
      answer_request();
    }
    sleep(1);
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
         (n = read(this->connection, this->data, sizeof(this->data))) > 0) {
    // connection es socket cliente
    std::cout << "Recibi: " << this->data << " de cliente" << std::endl;
    if (this->data[0] == '#') {
      close(this->connection);
    } else {
      // TODO(us): mandar connection
      this->send_to_server();
    }
  }
}

std::string intermediary::send_and_receive_login() {
  std::string result = "\0";
  int s = 0, n = 0; // s:socket  n: contador
  struct sockaddr_in ipServidorLogin;

  if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    std::cout << "Error de creación de socket" << std::endl;
  } else {
    ipServidorLogin.sin_family = AF_INET;
    ipServidorLogin.sin_port = htons(PORT_FS);
    ipServidorLogin.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Se intenta pegar al servidor
    if (connect(s, (struct sockaddr *)&ipServidorLogin, sizeof(ipServidorLogin)) < 0) {
      std::cout << std::endl << "Error de conexión por IP o puerto con login" << std::endl;
    } else {
      std::cout << "Voy a mandar: " << this->data  << " a autenticacion"<< std::endl;
      write(s, this->data, DATA_SIZE);
      read(this->connection, this->data, DATA_SIZE);  // reads the '&' that won't be used
      if ((n = read(s, this->data, DATA_SIZE)) > 0) {
        // connection es socket cliente
        std::cout << "Recibi: " << this->data << " de autenticacion" << std::endl;
        result =  this->data;
      }
      
      memset(this->data, '0', DATA_SIZE);
      data[0] = '#';
      std::cout << "Voy a mandar: " << data  << " a autenticacion "<< std::endl;
      write(s, this->data, DATA_SIZE);
      // No se logró leer
      if (n < 0) {
        std::cout << std::endl << "Error de lectura" << std::endl;
      }
    }
  }
  return result;
}

void intermediary::send_and_receive_data_base() {
  int s = 0, n = 1; // s:socket  n: contador
  struct sockaddr_in ipServidorLogin;

  if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    std::cout << "Error de creación de socket" << std::endl;
  } else {
    ipServidorLogin.sin_family = AF_INET;
    ipServidorLogin.sin_port = htons(PORT_DB);
    ipServidorLogin.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Se intenta pegar al servidor
    if (connect(s, (struct sockaddr *)&ipServidorLogin, sizeof(ipServidorLogin)) < 0) {
      std::cout << std::endl << "Error de conexión por IP o puerto" << std::endl;
    } else {
      // receive everything from client
      while (this->connection != -1 && n > 0 && this->data[0] != '&') {
          std::cout << "Voy a mandar: " << this->data  << " a data base"<< std::endl;
          write(s, this->data, DATA_SIZE);
          n = read(this->connection, this->data, sizeof(this->data));
      }
      // send & to server
      write(s, this->data, DATA_SIZE);

      // receive everything from server
      this->data[0] = 'a';
      while (s != -1 && n > 0 && this->data[0] != '&') { 
        if ((n = read(s, this->data, DATA_SIZE)) > 0) {
          // connection es socket cliente
          std::cout << "Recibi: " << this->data << "de data base" << std::endl;
          write(this->connection, this->data, DATA_SIZE);
        }
      }
      
      memset(this->data, '\0', DATA_SIZE);
      data[0] = '#';
      std::cout << "Voy a mandar: " << data  << " a autenticacion "<< std::endl;
      write(s, this->data, DATA_SIZE);
      // No se logró leer
      if (n < 0) {
        std::cout << std::endl << "Error de lectura" << std::endl;
      }
    }
  }
}

void intermediary::send_to_server() {
  std::string to_send_back = "\0";
  char temp_data[DATA_SIZE];
  switch(data[0]) {
    case LOGIN:
    case TOKEN:
    case CHANGE_PASSWORD:
      to_send_back = this->send_and_receive_login();
      write(this->connection, to_send_back.data(), DATA_SIZE);
      to_send_back[0] = '&';
      write(this->connection, to_send_back.data(), DATA_SIZE);
      // TODO (nosotros): mandar a la bitácora
      break;
    case CREATE_USER:
    case DELETE_USER:
      for (int i = 0; i < DATA_SIZE; ++i) {
          temp_data[i] = data[i];
        }
      to_send_back = this->send_and_receive_login();
      std::cout << "volvi de fs y tengo: " << to_send_back << std::endl;
      if (to_send_back[0] != '0') {
        for (int i = 0; i < DATA_SIZE; ++i) {
          data[i] = temp_data[i];
        }
        // TODO (nosotros): bases de datos 
        std::cout << "voy con data_base\n";
        this->send_and_receive_data_base();
      }
      // TODO (nosotros): mandar a la bitácora

      break;
    case PAYMENT_PROOF:
    case WORK_PROOF:
    case SALARY_PROOF:
    case SALARY_CONSULT:
    case RECORD_CONSULT:
    case CONSULT_REQUESTS:
    case VACATION_REQUEST:
    case CONSULT_VACATION:
    case CONSULT_USER_DATA:
    case CHANGE_USER_DATA:
    case ANSWER_PAYMENT_PROOF:
    case ANSWER_WORK_PROOF:
    case ANSWER_SALARY_PROOF:
    case ANSWER_VACATION_REQUEST:
      // TODO(us): hacer
      break;
    default:
      std::cerr << "Error: codigo inexistente" << std::endl;
  }
}