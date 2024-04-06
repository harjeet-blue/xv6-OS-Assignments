#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "kernel/spinlock.h"

int main() {
 
 int pid = fork(); //fork the first child
 if(pid < 0) {
 fprintf(1, "Error forking first child.\n");
 } else if (pid == 0) {
 sleep(5);
 fprintf(1, "Child 1 Executing\n");
 
 cv_signal(1);
 
 } else {
 pid = fork(); //fork the second
 if(pid < 0) {
 fprintf(1, "Error forking second child.\n");
 } else if(pid == 0) {
 
 cv_wait(1);
 
 fprintf(1, "Child 2 Executing\n");
 } else {
 fprintf(1, "Parent Waiting\n");
 int i;
 int wt;
 for(i=0; i< 2; i++)
 wait(&wt);
 fprintf(1, "Children completed\n");
 fprintf(1, "Parent Executing\n");
 fprintf(1, "Parent exiting.\n");
 }
 }
 exit(1);
}

