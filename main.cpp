#include <iostream>
#include "bppc.h"

int main(int argc, char **argv) {
    BPPC * problem = new BPPC(string(argv[1]));
    return 0;
}
