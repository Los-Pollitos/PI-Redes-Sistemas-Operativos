/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
*/

#include "login_server.h"

int main() {
  login_server* server = new login_server();
  server->wait_for_request();
  delete server;
}