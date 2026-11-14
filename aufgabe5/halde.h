#ifndef HALDE_H
#define HALDE_H

#include <sys/types.h>

/*
   sp_malloc() allocates size bytes and returns a pointer to the
   allocated memory. The memory is not cleared.

   RETURN VALUE: The value returned is a pointer
   to the allocated memory or NULL if the request fails. The
   errno will be set to indicate the error.
*/
void *sp_malloc(size_t size);

/*
   sp_free() frees the memory space pointed to by ptr, which
   must have been returned by a previous call to sp_malloc(),
   sp_calloc() or sp_realloc(). Otherwise, or if sp_free(ptr) has
   already been called before the program is aborted.
   If ptr is NULL, no operation is performed.

   RETURN VALUE: no value
*/
void sp_free(void *ptr);

/*
   sp_realloc()  changes the size of the memory block pointed to
   by ptr to size bytes.  The contents will be  unchanged  to
   the minimum of the old and new sizes; newly allocated mem-
   ory will be uninitialized.  If ptr is NULL,  the  call  is
   equivalent  to sp_malloc(size). Unless ptr is  NULL,  it must
   have  been  returned by an earlier call to sp_malloc(),
   sp_calloc() or sp_realloc().

   RETURN VALUE: The value returned is a pointer
   to the allocated memory or NULL if the request fails. The
   errno will be set to indicate the error.
*/
void *sp_realloc(void *ptr, size_t size);

/*
   sp_calloc() allocates memory for an array of nmemb elements
   of size bytes each and returns a pointer to the allocated
   memory. The memory is set to zero.

   RETURN VALUE: The value returned is a pointer
   to the allocated memory or NULL if the request fails. The
   errno will be set to indicate the error.
*/
void *sp_calloc(size_t nmemb, size_t size);

/*
 * printList is a non-standard function which prints the internal state of the
 * free list.
 *
 * This function can be used to debug the implementation and compare the
 * behavior with other implementations.
 */
void printList(void);

#endif
