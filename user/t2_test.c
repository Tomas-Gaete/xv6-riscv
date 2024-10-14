
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
            int current_priority = getpriority(processes[i].pid); // Get current priority
            int boost = getboost(processes[i].pid);               // Get current boost

            if (current_priority < 9) {
                current_priority += boost;  // Increase priority by boost
            } else if (current_priority >= 9) {
                boost = -1;
                current_priority += boost;  // Boost decreases priority value
                setboost(processes[i].pid, boost); // Set new boost value
            } else if (current_priority == 0) {
                boost = 1;
                current_priority += boost;  // Boost increases priority value
                setboost(processes[i].pid, boost); // Set new boost value
            }

            setpriority(processes[i].pid, current_priority); // Set new priority
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
        printf("Running child process with PID %d\n", getpid());
        sleep(2);  // Simulate work by sleeping for 2 seconds
        exit(0);   // Exit the child process
    } else {
        // Parent process
        processes[process_count].pid = pid;     // Store the new process's PID
        setpriority(pid, 0);                // Set initial priority to 0
        setboost(pid, 1);                   // Set initial boost to 1
        processes[process_count].state = 0;     // Mark the process as running
        process_count++;

        // Update priorities of all existing processes
        update_priorities();
        
        wait(&time);  // Wait for the child process to finish
    }
}

int main() {
    // Loop to create the defined number of processes
    for (int i = 0; i < MAX_PROCESSES; i++) {
        create_process();  // Create each process and apply priority logic
    }

    return 0;
}