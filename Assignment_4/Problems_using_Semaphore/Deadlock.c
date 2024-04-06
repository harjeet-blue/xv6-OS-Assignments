#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"



void cat_thread(int i) {
    
   
    while(1){
        fprintf(1, "Cat %d is being chaotic\n",i);
        //wait for left fish
        //wait for right fish
        if(i==0){
            sem_wait((i+1)%5, 1);
            fprintf(1, "Cat %d got left fish %d \n",i,(i+1)%5);
            sem_wait((i-1)%5, 1);
            fprintf(1, "Cat %d got right fish %d \n",i,(i-1)%5);
        }
        else {
            sem_wait((i+1)%5, 1);
            fprintf(1, "Cat %d got left fish %d \n",i,(i+1)%5);
            sem_wait((i-1)%5, 1);
            fprintf(1, "Cat %d got right fish %d \n",i,(i-1)%5);
        }
        fprintf(1, "Cat %d is eating \n",i);
        sleep(1);
        sem_signal((i+1)%5, 1);
        fprintf(1, "Cat %d is finished with left fish %d\n",i,(i+1)%5);
        sem_signal((i-1)%5, 1);
        fprintf(1, "Cat %d is finished with right fish %d \n",i,(i-1)%5);        
    }

    // Simulate cat being happy or chaotic
   
    
       
}

int main() {
    
   
    int cat_ids;

    
    // Create cat threads
    for (int i = 0; i <5; i++) {
        cat_ids = i ;
        if (sem_init(cat_ids, 1) < 0)
        {
            fprintf(1, "main: error initializing semaphore %d\n", cat_ids);
            exit(-1);
        }
        int pid = fork();
		if (pid == 0)
			cat_thread(cat_ids);
        
    }
    int wt;
    // Join cat threads
    for (int i = 0; i <5; i++) {
        wait(&wt);
        sem_destroy(cat_ids) ;
    }

    return 0;
}
