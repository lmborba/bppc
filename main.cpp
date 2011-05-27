#include <iostream>
#include "bppc.h"

int main(int argc, char **argv) {
  BPPC * problem = new BPPC(string(argv[1]));
  cout << problem->lower_bound_cp() << endl;
  return 0;
}
