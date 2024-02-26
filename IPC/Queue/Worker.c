#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_MSG_SIZE 50

struct my_msgbuf {
    char description[MAX_MSG_SIZE];
    int priority;
    int deadline;
    int id;  // Added an identifier for the task
};

struct second {
    int index;
};

int main() {
    printf("Process worker called\n");

    // Sending message with queue
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

    // Simulating multiple tasks
    for (int loop = 0; loop < 5; loop++) {
        int i = loop;
        // Set task details
        snprintf(buf.description, sizeof(buf.description), "Task %d", i + 1);
        buf.priority = rand() % 10 + 1;  // Random priority between 1 and 10
        buf.deadline = rand() % 5 + 1;   // Random deadline between 1 and 5
        buf.id = i + 1;  // Assign a unique identifier for the task

        // Send task details to Process Worker through the message queue
        if (msgsnd(sendid, &buf, sizeof(buf), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
       
        printf("Task %d sent to Process Worker\n", i + 1);
       
        // Wait for Process Worker to acknowledge task completion
        if (msgrcv(getid, &buf2, sizeof(buf2), 0, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
       
        loop = i;
        printf("Acknowledgment received for Task %d from Process Worker\n", buf2.index);
        
        
    }
    printf("End time");
    // Send termination message to Process Worker
    snprintf(buf.description, sizeof(buf.description), "end");
    if (msgsnd(sendid, &buf, sizeof(buf), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }

    // Remove message queues
    if (msgctl(getid, IPC_RMID, NULL) == -1 || msgctl(sendid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    return 0;
}
