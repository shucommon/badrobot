#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

// wait on a binary semaphore, block until the semaphore value is positive, then decrement it by 1
int binary_semaphore_wait(int semid)
{
    struct sembuf operations[1];
    // use the first (and only) semaphore
    operations[0].sem_num = 0;
    // decrement by 1
    operations[0].sem_op = -1;
    // premit undo'ing
    operations[0].sem_flag = SEM_UNDO;

    return semop(semid, operations, 1);
}

int binary_semaphore_post(int semid)
{
    struct sembuf operations[1];
    // use the first (and only) semaphore
    operations[0].sem_num = 0;
    // increment by 1
    operations[0].sem_op = 1;
    // premit undo'ing
    operations[0].sem_flag = SEM_UNDO;

    return semop(semid, operations, 1);
}
