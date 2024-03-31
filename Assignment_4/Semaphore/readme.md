**Semaphore Implementation Test in xv6-riscv Operating System**

**Overview:**
This program is designed to test the correct implementation of a semaphore in the xv6-riscv operating system. A semaphore is a synchronization primitive used to control access to shared resources in a concurrent system. This test program spawns multiple child processes, each of which increments a shared counter while respecting mutual exclusion enforced by a semaphore.

**Files:**
1. `main.c`: The main program that initializes the semaphore, spawns child processes, waits for them to finish, and checks the final counter value.
2. `counter.h`: Header file defining functions to initialize, read, and set the shared counter.
3. `counter.c`: Implementation file containing functions to handle the shared counter.
4. `semaphore.h`: Header file defining functions to initialize, wait, and signal the semaphore.
5. `semaphore.c`: Implementation file containing functions to handle the semaphore.

**Functionality:**
- **`counter_init()`**: Initializes the shared counter by creating a file named "counter" and writing an initial value to it.
- **`counter_get()`**: Retrieves the current value of the shared counter by reading from the "counter" file.
- **`counter_set()`**: Sets the value of the shared counter by writing to the "counter" file.
- **`child()`**: Function executed by each child process. Increments the shared counter while respecting mutual exclusion using semaphores.
- **`main()`**: Initializes the semaphore, spawns child processes, waits for them to finish, checks the final counter value, and cleans up the semaphore.

**Usage:**
- Compile the program using `make`.
- Run the executable `main`.
- The program will output the final counter value and indicate whether the test passed or failed based on the expected value.

**Testing:**
- The program can be tested with different values of `NUM_CHILDREN` and `TARGET_COUNT_PER_CHILD` to evaluate the behavior of the semaphore under varying loads.
- Adjusting the sleep duration in the `child()` function can simulate different execution times of child processes.

**Note:**
- This test program assumes correct implementation of semaphores and does not verify the correctness of the semaphore implementation itself. It only tests if the semaphore functions as expected in coordinating access to shared resources.
- Care should be taken to ensure that the xv6-riscv operating system supports semaphores and provides correct implementations of system calls such as `sem_init()`, `sem_wait()`, and `sem_signal()`.