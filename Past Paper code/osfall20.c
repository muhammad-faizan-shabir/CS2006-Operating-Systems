#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main() {
    int N = 10;
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int key, i;
    
    printf("Enter a number: ");
    scanf("%d", &key);
    
    int pd[2];
    
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        printf("Error\n");
        return 0;
    }

    if (pid == 0) {
        // child 1
        
        for (int l = 0; l < N/2 ; l++) {
            if (key == a[l]) {
                
                return(l);
            }
        }
        return -1;
    }

    // parent
    pid_t pid1 = fork();

    if (pid1 < 0) {
        printf("Error\n");
        return 0;
    }

    if (pid1 == 0) {
        // child 2
        for (int l = N / 2; l < N; l++) {
            if (key == a[l]) {
                return l;
            }
        }
        return -1;
    }

    // parent
    int x;
    int y;
    pid_t testPid=wait(&x);
    printf("%d",x);
    i= WEXITSTATUS(x);
    if (i == 255) {
        wait(&y);
        i=WEXITSTATUS(y);
        //i = y;
    }
    //i =WEXITSTATUS(x);
    printf("The number found at index: %d\n", i);
    return 0;
}

