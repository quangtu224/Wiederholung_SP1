/* 
 * !!    DIESE DATEI DARF NICHT VERÄNDERT WERDEN    !!
 * !!   Änderungen führen zu fehlschlagenden Tests  !!
 *
 *
 * Öffentliche Beispiel-Implementierung des "sem" Moduls, indem diese auf POSIX
 * Semaphoren reduziert werden. Dies erlaubt die Nutzung von helgrind:
 * https://valgrind.org/docs/manual/hg-manual.html
 *
 * Das hier ist keine gültige Implementierung für den in SP2 zu
 * implementierenden Semaphor. */

#include <assert.h>
#include <errno.h>
#include <semaphore.h>
#include <stdlib.h>

#include "sem.h"

struct SEM {
	sem_t sem;
};

SEM *semCreate(unsigned initVal) {
	SEM *sem = malloc(sizeof(*sem));
	if (NULL == sem) {
		return NULL;
	}

	if (-1 == sem_init(&sem->sem, 0, initVal)) {
		int save = errno;
		free(sem);
		errno = save;
		return NULL;
	}

	return sem;
}

void semDestroy(SEM *sem) {
	if (sem == NULL) {
		return;
	}

	int err = sem_destroy(&sem->sem);
	assert(!err);
	free(sem);
}

void down(SEM *sem) {
	/*
	 * Signal handlers should be configured to restart syscalls. Thus not
	 * putting an EINTR loop in here.
	 */
	int err = sem_wait(&sem->sem);
	assert(!err);
}

void up(SEM *sem) {
	int err = sem_post(&sem->sem);
	assert(!err);
}
