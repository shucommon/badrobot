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

// initialize a binary semaphore with a value of 1
int binary_semaphore_initialize(int semid)
{
    union semun argument;
    unsigned short values[1];
    values[0] = 1;
    argument.array = values;
    return semctl(semid, 0, SETALL, argument);
}
