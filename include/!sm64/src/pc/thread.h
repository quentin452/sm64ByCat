#ifndef _PC_THREAD_H
#define _PC_THREAD_H

#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

void pcthread_mutex_lock(pthread_mutex_t *mutex);
void pcthread_mutex_unlock(pthread_mutex_t *mutex);
void pcthread_semaphore_init(sem_t *sem, int pshared, unsigned int value);
void pcthread_semaphore_wait(sem_t *sem);
void pcthread_semaphore_post(sem_t *sem);
void pcthread_semaphore_destroy(sem_t *sem);

#endif // _PC_THREAD_H