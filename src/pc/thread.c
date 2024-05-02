#include "thread.h"

// TODO: Cross-platform stuff

void pcthread_mutex_lock(pthread_mutex_t *mutex) {
    pthread_mutex_lock(mutex);
}

void pcthread_mutex_unlock(pthread_mutex_t *mutex) {
    pthread_mutex_unlock(mutex);
}
void pcthread_semaphore_init(sem_t *sem, int pshared, unsigned int value) {
    sem_init(sem, pshared, value);
}

void pcthread_semaphore_wait(sem_t *sem) {
    sem_wait(sem);
}

void pcthread_semaphore_post(sem_t *sem) {
    sem_post(sem);
}

void pcthread_semaphore_destroy(sem_t *sem) {
    sem_destroy(sem);
}