#include "kernel/types.h"
#include "kernel/uproc.h"
#include "user.h"

#define max_procs 64

char *states[] = {
[2] "SLEEPING",
[3] "RUNNABLE",
[4] "RUNNING ",
[5] "ZOMBIE  "
};

void print_procinfo(struct uproc *up) {
  if (up == 0) {
    printf("PID\tPPID\tSTATE\t\tMEM\tNAME\n");
    return;
  }
  printf("%d\t%d\t%s\t%d\t%s\n", up->pid, up->cpid, states[up->pstate], up->msize, up->pname);
}

int main(int argc, char *argv[]) {
  struct uproc up[max_procs];
  int result = procinfo(up, max_procs);
  
  if (argc != 1) {
    printf("Wrong commands given.\n");
    exit(1);
  }

  if (result == -1) {
    printf("Error in procinfo.\n");
    exit(1);
  }

  print_procinfo(0);
  for (int i = 0; i < result; i++) {
    print_procinfo(&up[i]);
  }
  
  return 0;
}
