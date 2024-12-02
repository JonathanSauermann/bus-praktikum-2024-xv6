#include "user.h"

int main() {
    malloc(1024 * 1024); // Allocate 1 MiB.
    while (1) sleep(100); // Infinite loop.
    exit(0);
}
