#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

int
main(int argc, char* argv[])
{
    if (argc < 2)
        exit(1);

    char* arg = argv[1];

    if (strcmp(arg, "enable") == 0 || strcmp(arg, "disable") == 0) {
        strace(arg);
    } else {
        argv++;
        strace(arg);
        exec(arg, argv);
    }
    exit(0);
}
