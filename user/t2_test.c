#include "kernel/types.h"
#include "user.h"
#include "syscall.h"

#define MAX_PROCESSES 20   // Number of processes to create

// Process structure, maintaining only the zombie state in the test code
struct process {
    int pid;  // Process ID
    int state;  // 0 = running, 1 = zombie (dummy state for this example)
};

struct process processes[MAX_PROCESSES];
int process_count = 0;

// Function to update priorities of all non-zombie processes using system calls
void update_priorities() {
    for (int i = 0; i < process_count; i++) {
        if (processes[i].state != 1) {  // If process is not a zombie
            int current_priority = getpriority();  // Get current priority
            int boost = getboost();                // Get current boost
            if (current_priority <= 9) {
                current_priority += boost;
                setpriority(current_priority);
            } 
            if (current_priority > 9){
                    boost = -1;
                    setboost(boost);  
                    current_priority += boost;
                    if (current_priority < 0) current_priority = 0;   // Ensure priority doesn't go below 0
                    setboost(boost);                // Set new boost value
                    setpriority(current_priority);       // Set new priority
            }
            if (current_priority <=0){
                boost = 1;
                setboost(boost);
                current_priority += boost;
                setpriority(current_priority);
            } 
            setpriority(current_priority);       // Set new priority
            printf("Process with PID %d now has priority %d\n", processes[i].pid, current_priority);
        }
    }
}


// Function to create a new process and manage priorities
void create_process() {
    int pid = fork();  // Create a new process
    int time = 5;
    if (pid < 0) {
        // Error in creating the process
        printf("Error creating process");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("NEW CREATED PROCESS ID:%d AND priority %d\n", getpid(), getpriority());
        sleep(2);  // Simulate work by sleeping for 2 seconds
        exit(0);   // Exit the child process
    } else {
        // Parent process
        processes[process_count].pid = pid;     // Store the new process's PID
        processes[process_count].state = 0;     // Mark the process as running
        process_count++;

        // Update priorities of all existing processes
        
        wait(&time);  // Wait for the child process to finish
        update_priorities();
    }
}

int main() {
    // Loop to create the defined number of processes
    for (int i = 0; i < MAX_PROCESSES; i++) {
        create_process();
        // Create each process and apply priority logic
    }
    return 0;
}