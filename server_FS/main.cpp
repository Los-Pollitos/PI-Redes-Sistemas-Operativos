/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
*/

#include <csignal>

#include "login_server.h"

void stop_server(int signal_type);

int main() {
  std::signal(SIGTERM, stop_server);
  std::signal(SIGINT, stop_server);
  login_server::get_instance().start();
}

void stop_server(int signal_type) {
  (void) signal_type;

  // TODO(us): borrar
  std::cout << "\nvoy a detener servidor____________________________\n";

  login_server::get_instance().stop();
}
