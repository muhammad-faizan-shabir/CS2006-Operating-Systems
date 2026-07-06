#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

int main() {
    char input[MAX_COMMAND_LENGTH];

    while (1) {
        // Step 1: Get user input
        printf("Enter a command (or 'exit' to quit): ");
        fgets(input, sizeof(input), stdin);

        // Remove trailing newline character
        input[strcspn(input, "\n")] = 0;

        // Step 2: Tokenization
        char* token;
        char* arguments[MAX_ARGUMENTS + 1];  // Additional element for NULL pointer
        int argCount = 0;

        // Tokenize the input command
        token = strtok(input, " ");
        while (token != NULL && argCount < MAX_ARGUMENTS) {
            arguments[argCount++] = token;
            token = strtok(NULL, " ");
        }
        arguments[argCount] = NULL;  // NULL-terminate the array of arguments

        // Step 3: Create a child process
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Step 4: Execute the command in the child process
            execvp(arguments[0], arguments);

            // If execvp fails, print an error message
            perror("Execvp failed");
            exit(EXIT_FAILURE);
        } else {
            // Step 5: Wait for the child process to finish
            wait(NULL);
        }

        // Step 6: Check for 'exit' command to terminate the shell
        if (strcmp(arguments[0], "exit") == 0) {
            printf("Exiting the shell.\n");
            break;
        }
    }

    return 0;
}

