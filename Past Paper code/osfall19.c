#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> 
#include<sys/wait.h>
#define BUFFER_SIZE 25

int main() {
    char msg[BUFFER_SIZE] = "Welcome";
    pid_t pid = fork();

    if (pid > 0) {
        // Parent process
        strcpy(msg, "Welcome to OS course");
        printf("Parent process waiting for child termination\n");
        wait(NULL);
        printf("Parent Terminating\n");
    } else {
        // Child process
        printf("Message: %s\n", msg);
        pid_t pid1 = fork();
        strcpy(msg, "OS course");
        pid_t pid2 = fork();

        if (pid2 == 0) {
            // Child process created by pid2
            strcpy(msg, "Adv OS course");
            printf("Child Process called\n");
        } else {
            // Parent process created by pid1
            //printf("Message: %s\n", msg);
            //wait(NULL);
            printf("Message: %s\n", msg);
        }

        if (pid1 > 0) {
            // Parent process created by pid1
            wait(NULL);
        }
    }

    return 0;
}

