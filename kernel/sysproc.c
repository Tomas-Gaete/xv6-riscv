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
uint64
sys_getppid(void)
{
    struct proc *curproc = myproc();   // Get the current process
    if (curproc->parent) {
        return curproc->parent->pid;   // Return the parent's PID
    }
    return 0;  // Return 0 if no parent (e.g., for the init process)
}
uint64
sys_getancestor(void)
{
  int n;
  argint(0, &n);
  struct proc *p = myproc();
   if (n == 0) {
        return p->pid;
    }
  for (int i = 0; i < n; i++) {
        if (p->parent == 0) {
            return -1; // Return -1 if there is no nth ancestor
        }
        p = p->parent; // Move to the parent process
    }

    return p->pid;
}


uint64
sys_setpriority(void) {
    int priority;
    argint(0, &priority);    // Fetch priority

    struct proc *p = myproc();  // Use the passed PID, not current PID
   
    acquire(&p->lock);
    p->priority = priority;  // Set priority
    release(&p->lock);
    return p->priority;                // Success
}

uint64
sys_getpriority(void) {
    struct proc *p = myproc();  
    return p->priority;      
}

uint64
sys_setboost(void) {
    int boost;
    argint(0, &boost);       // Fetch boost value


    struct proc *p = myproc();
    acquire(&p->lock);
    p->boost = boost;        // Set boost
    release(&p->lock);
    return p->boost;                // Success
}

uint64
sys_getboost(void) {
    struct proc *p = myproc();//built in function to grab current process
    return p->boost;//returns the boost parameter of the process  
}