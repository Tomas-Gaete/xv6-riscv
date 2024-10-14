#include <stdio.h>
#include <unistd.h>   // For fork(), getpid(), sleep()
#include <sys/wait.h> // For wait()
#include <stdlib.h>   // For exit()

#define MAX_PROCESSES 20   // Number of processes to create
#define BOOST 1            // Boost value to add to the priority

// Struct to hold process information
struct process {
    pid_t pid;      // Process ID
    int priority;
    int boost;   // Priority of the process
    int state;      // 0 = running, 1 = zombie (dummy state for this example)
};

struct process processes[MAX_PROCESSES];
int process_count = 0;

// Function to update priorities of all non-zombie processes
void update_priorities() {
    for (int i = 0; i < process_count; i++) {
        if (processes[i].state != 1) {  // If process is not a zombie
            if (processes[i].priority < 9){
            processes[i].priority += processes[i].boost ;  // Increase priority by BOOST
            printf("Process with PID %d now has priority %d\n", processes[i].pid, processes[i].priority);
            }
            if(processes[i].priority >=9){
                processes[i].boost = -1;
                processes[i].priority += processes[i].boost ;  // Boost decreases priority
            }
        }
    }
}

// Function to create a new process and manage priorities
void create_process() {
    pid_t pid = fork();  // Create a new process

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
        processes[process_count].priority = 0;  // Set initial priority to 0
        processes[process_count].boost = 1;     //initial boost    
        processes[process_count].state = 0;     // Mark the process as running
        process_count++;

        // Update priorities of all existing processes
        update_priorities();
        
        wait(NULL);  // Wait for the child process to finish
    }
}

int main() {
    // Loop to create the defined number of processes
    for (int i = 0; i < MAX_PROCESSES; i++) {
        create_process();  // Create each process and apply priority logic
    }

    return 0;
}
