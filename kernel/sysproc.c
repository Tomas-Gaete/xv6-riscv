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

struct proc* findproc(int pid) {
  struct proc *p;
  // Iterate over the process table
  for(p = proc; p < &proc[NPROC]; p++) {
    if(p->pid == pid) {
      return p;  // Return the process if the PID matches
    }
  }
  
  return 0;  // Return 0 if no process with the given PID is found
}

uint64
sys_setpriority(void) {
    int pid, priority;
    int cur_pid = sys_getpid();
    // Fetch the arguments using argint() 
    argint(0, &pid);       // Fetch PID
    argint(1, &priority);  // Fetch priority
    // Check if the PID and priority are valid
    if (pid < 0 || priority < 0) { // You may want to define valid ranges for priority
        return -1;  // Return -1 if either value is invalid
    }

    struct proc *p = findproc(cur_pid);  // Find the process
    if (p) {
        p->priority = priority;  // Set the priority
        return 0;  // Return 0 on success, as a uint64
    }
    return -1;  // Return -1 if the process was not found
}
uint64
sys_getpriority(void) {
    int pid;
    int cur_pid = sys_getpid();
    argint(0, &pid);  // Call argint() to fetch the PID
    if (pid < 0) {  // You can check if PID is valid
        return -1;  // Return -1 if the PID is invalid
    }
    // Find the process with the specified PID
    struct proc *p = findproc(cur_pid);
    if (p) {
        return p->priority;  // Return the priority, as a uint64
    }

    return -1;  // Return -1 if the process is not found
}
uint64
sys_setboost(void){
   int pid;
   int cur_pid = sys_getpid();
    argint(0, &pid);  // Call argint() to fetch the PID
    if (pid < 0) {  // You can check if PID is valid
        return -1;  // Return -1 if the PID is invalid
    }
    // Find the process with the specified PID
    struct proc *p = findproc(cur_pid);
    if (p) {
        return p->boost;  // Return the priority, as a uint64
    }

    return -1;  // Return -1 if the process is not found
}
uint64
sys_getboost(void){
  int pid;
  int cur_pid = sys_getpid();
    argint(0, &pid);  // Call argint() to fetch the PID
    if (pid < 0) {  // You can check if PID is valid
        return -1;  // Return -1 if the PID is invalid
    }
    // Find the process with the specified PID
    struct proc *p = findproc(cur_pid);
    if (p) {
        return p->boost;  // Return the priority, as a uint64
    }

    return -1;  // Return -1 if the process is not found
}