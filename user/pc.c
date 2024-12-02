#include "user.h"
#include "proc_info.h"

int main() {
    struct proc_info info[NPROC];
    int count = psinfo(info);
    printf("PID\tSTATE\tFILES\tMEM\tCMD\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t%d\t%dK\t%s\n",
               info[i].pid,
               info[i].state,
               info[i].open_files,
               info[i].memory / 1024,
               info[i].name);
    }
    exit(0);
}
