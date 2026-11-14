/* 
 * !!    DIESE DATEI DARF NICHT VERÄNDERT WERDEN    !!
 * !!   Änderungen führen zu fehlschlagenden Tests  !!
 *
 */

/**
 * @file  sem.h
 * @brief Semaphore implementation for the synchronization of POSIX threads.
 *
 * This module implements counting semaphores suitable for the
 * synchronization of POSIX threads. POSIX mutexes and condition variables are
 * utilized to implement the semaphor operations.
 */

#ifndef SEM_H
#define SEM_H


/** Opaque type of a semaphore. */
typedef struct SEM SEM;

/**
 * @brief Creates a new semaphore.
 *
 * This function creates a new semaphore. If an error occurs during the
 * initialization, the implementation frees all resources already allocated by
 * then and sets @c errno to an appropriate value.
 *
 * @param initVal The initial value of the semaphore.
 * @return Handle for the created semaphore, or @c NULL if an error occurred.
 */
SEM *semCreate(unsigned initVal);

/**
 * @brief Destroys a semaphore and frees all associated resources.
 * @param sem Handle of the semaphore to destroy. If a @c NULL pointer is
 *            passed, the implementation does nothing.
 */
void semDestroy(SEM *sem);

/**
 * @brief Acquire the semaphore.
 *
 * Attempts to decrement the semaphore value by 1. If the semaphore value is 0,
 * the operation blocks until a up() call increments the value.
 *
 * @param sem Handle of the semaphore to decrement.
 */
void down(SEM *sem);

/**
 * @brief Release the semaphore.
 *
 * Increments the semaphore value by 1 and notifies threads that are
 * blocked on the semaphore of the change.
 *
 * @param sem Handle of the semaphore to increment.
 */
void up(SEM *sem);


#endif /* SEM_H */
