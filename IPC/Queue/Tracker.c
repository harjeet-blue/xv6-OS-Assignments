#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

#define MAX_MSG_SIZE 50

struct my_msgbuf {
    char description[MAX_MSG_SIZE];
    int priority;
    int deadline;
    int id;
};

struct second {
    int index;
};

int main() {
    printf("Process Tracker called\n");

    struct my_msgbuf buf;
    struct second buf2;

    int sendid, getid;
    key_t sendkey, getkey;

    if ((sendkey = ftok("Tracker.c", 'B')) == -1 || (getkey = ftok("Worker.c", 'C')) == -1) {
        perror("ftok");
        exit(1);
    }

     if ((sendid = msgget(sendkey, 0644 | IPC_CREAT)) == -1 || (getid = msgget(getkey, 0644 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }


    while (1) {
        // Receive task details from Process Tracker
        if (msgrcv(sendid, &buf, sizeof(buf), 0, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        // Check for termination message
        if (strcmp(buf.description, "end") == 0) {
            printf("The end");
            break;
        }

        printf("Received task from Process Tracker:\n");
        printf("Task ID: %d\n", buf.id);
        printf("Description: %s\n", buf.description);
        printf("Priority: %d\n", buf.priority);
        printf("Deadline: %d\n", buf.deadline);

        // Simulate task execution
        printf("Task %d execution started...\n", buf.id);
        sleep(buf.deadline);  // Simulating task execution time
        printf("Task %d execution completed!\n", buf.id);

        // Send acknowledgment to Process Tracker
        buf2.index = buf.id;
        if (msgsnd(getid, &buf2, sizeof(buf2), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
    }

    return 0;
}
