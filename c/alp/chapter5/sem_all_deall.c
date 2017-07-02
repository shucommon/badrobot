#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

// we must define union semun ourselves
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
    struct seninfo *__buf;
};

// obtain a binary semaphore's ID, allocating if necessary
int binary_semaphore_allocation(key_t key, int sem_flags)
{
    return semget(key, 1, sem_flags);
}

// deallocate a binary semaphore. ALl users must have finished their use. return -1 on failure
int binary_semaphore_deallocate(int semid)
{
    union semun ignored_argument;
    return semctl(semid, 1, IPC_RMID, ignored_argument);
}
