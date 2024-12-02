#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

#define MAXSTRING 8

uint64
sys_strace(void)
{
  struct proc* p = myproc();
  char cmd[8];

  int f = argstr(0, cmd, MAXSTRING);
  if (f == -1)
    return -1;

  if (strncmp(cmd, "enable", MAXSTRING) == 0) {
    set_enable_tracing(1);
  } else  if (strncmp(cmd, "disable", MAXSTRING) == 0) {
    set_enable_tracing(0);
  } else {
    set_enable_tracing(0);
    acquire(&p->lock);
    p->strace = 1;
    release(&p->lock);
  }
  return 0;
}

uint64 sys_psinfo(void) {
    uint64 addr;
    struct proc_info info[NPROC];

    if (fetchaddr(0, &addr) < 0) return -1;
    int count = psinfo(info);
    if (copyout(myproc()->pagetable, addr, (char*)info, count * sizeof(struct proc_info)) < 0)
        return -1;
    return count;
}
