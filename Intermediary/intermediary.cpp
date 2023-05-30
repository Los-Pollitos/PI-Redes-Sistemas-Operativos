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
  this->login_s = new login_server();
}

// TODO(us): documentar
intermediary::~intermediary() {
  delete this->login_s;
}

/*
 * @brief The intermediary waits for a request from a client to answer it.
 */
void intermediary::wait_for_request() {
  int socketServidor = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in ip;

  memset(&ip, '0', sizeof(ip));
  memset(this->data, '0', sizeof(this->data));
  ip.sin_family = AF_INET;
  ip.sin_addr.s_addr = htonl(INADDR_ANY);
  ip.sin_port = htons(1337);

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
    std::cout << "Recibi: " << this->data << std::endl;
    if (this->data[0] == '#') {
      close(this->connection);
    } else {
      // TODO(us): mandar connection

    }
  }
}

void intermediary::send_to_server() {
  switch(std::stoi(&data[0])) {
    case LOGIN:
      // TODO(us): hacer
      break;
    case TOKEN:
      // TODO(us): hacer
      break;
    case CHANGE_PASSWORD:
      // TODO(us): hacer
      break;
    case CREATE_USER:
      // TODO(us): hacer
      break;
    case DELETE_USER:
      // TODO(us): hacer
      break;
    case PAYMENT_PROOF:
      // TODO(us): hacer
      break;
    case WORK_PROOF:
      // TODO(us): hacer
      break;
    case SALARY_PROOF:
      // TODO(us): hacer
      break;
    case SALARY_CONSULT:
      // TODO(us): hacer
      break;
    case RECORD_CONSULT:
      // TODO(us): hacer
      break;
    case CONSULT_REQUESTS:
      // TODO(us): hacer
      break;
    case VACATION_REQUEST:
      // TODO(us): hacer
      break;
    case CONSULT_VACATION:
      // TODO(us): hacer
      break;
    case CONSULT_USER_DATA:
      // TODO(us): hacer
      break;
    case CHANGE_USER_DATA:
      // TODO(us): hacer
      break;
    case ANSWER_PAYMENT_PROOF:
      // TODO(us): hacer
      break;
    case ANSWER_WORK_PROOF:
      // TODO(us): hacer
      break;
    case ANSWER_SALARY_PROOF:
      // TODO(us): hacer
      break;
    case ANSWER_VACATION_REQUEST:
      // TODO(us): hacer
      break;
  }
}
