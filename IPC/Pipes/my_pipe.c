#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/syscall.h"
#include "kernel/fs.h"

int main(int argc, char *argv[]) {
    int fd[2];
    int fd2[2];
    char buffer[512];
    int pid;

    // Pipe
    if (pipe(fd) < 0 || pipe(fd2)<0) {
        fprintf(2, "pipe failed\n");
        exit(1);
    }

    // Fork
    pid = fork();

    if (pid < 0) {
        fprintf(2, "fork failed\n");
        exit(1);
    }

    if (pid == 0) {
        // Child
        close(fd[0]);
        close(fd2[1]);
        for (int i = 0; i < 5; ++i) {
            // Write to the pipe
            char *message = "message\n";
            write(fd[1], message, strlen(message));
        }

        // Close the write end of the pipe
        close(fd[1]);

        // Wait for the child to exit and receive acknowledgment
        char ackBuffer[512];
        int bytesRead = read(fd2[0], ackBuffer, sizeof(ackBuffer));
        if (bytesRead > 0) {
            fprintf(2, "writer process received acknowledgment: %s\n", ackBuffer);
        }
        
        close(fd2[0]);
        close(fd[1]);
    } else {
        // Parent
        close(fd[1]);
        close(fd2[0]);
        for (int i = 0; i < 5; ++i) {
            // Read from the pipe
            int bytesRead = read(fd[0], buffer, sizeof(buffer));
            if (bytesRead > 0) {
                fprintf(1, "printer process received: %s\n", buffer);
            }
        }

        // Acknowledge to the parent
        const char *ack = "Got it!";
        write(fd2[1], ack, strlen(ack));

        // Close the read end of the pipe
        close(fd[0]);
        // Close the write end of the pipe
        close(fd2[1]);
        

        int status;
        wait(&status);
    }

    exit(0);
}
