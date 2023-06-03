/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
 */

#include "intermediary.h"

int main () {
  intermediary *  inter = new intermediary();

  inter -> wait_for_request();

  delete inter;
  return 0;
}