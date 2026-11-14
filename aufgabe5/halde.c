#include "halde.h"
#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdckdint.h>
#include <sys/mman.h>

/// Magic value for occupied memory chunks, must NOT be modified.
#define MAGIC ((void*)0xbaadf00d)

/// Size of the heap (in bytes), must NOT be modified.
#define SIZE (1024*1024*1)

/// Memory-chunk structure, must NOT be modified.
struct mblock {
	struct mblock *next;
	size_t size;
	alignas(max_align_t) char memory[];
};

/// Heap-memory area.
/// IMPORTANT: In order for our tests to work, you must use this variable in your implementation.
//             Do NOT modify its name or type.
static char *memory;

/// Pointer to the first element of the free-memory list.
static struct mblock *head;

/// Aligns a value to work safely with all fundamental (scalar) types
/// Unaligned memory accesses are not allowed by the C standard (see 6.2.8, "Alignment of objects")
static size_t round_to_alignment(size_t value) {
	// https://en.cppreference.com/w/c/types/max_align_t.html
	const size_t max_align = alignof(max_align_t);

	// Prevent overflow
	if (value > (SIZE_MAX - (max_align - 1))) {
		return SIZE_MAX;
	}

	// Round up value to the next multiple of max_align
	return ((value + (max_align - 1)) / max_align) * max_align;
}

/// Helper function to visualize the current state of the free-memory list.
void printList(void) {
	struct mblock *lauf = head;

	// Empty list
	if (head == NULL) {
		char empty[] = "(empty)\n";
		write(STDERR_FILENO, empty, strlen(empty));
		return;
	}

	// Print each element in the list
	const char fmt_init[] = "(off: %7td, size:: %7zu)";
	const char fmt_next[] = " --> (off: %7td, size:: %7zu)";
	const char * fmt = fmt_init;
	char buffer[sizeof(fmt_next) + 2 * 7];

	while (lauf) {
		size_t n = snprintf(buffer, sizeof(buffer), fmt
			, (char *) lauf - memory, lauf->size);
		if (n) {
			write(STDERR_FILENO, buffer, n);
		}

		lauf = lauf->next;
		fmt = fmt_next;
	}
	write(STDERR_FILENO, "\n", 1);
}

void *sp_malloc (size_t size) {
	size = round_to_alignment(size);
	// TODO: implement me!
	return NULL;
}

void sp_free (void *ptr) {
	// TODO: implement me!
}

void *sp_realloc (void *ptr, size_t size) {
	// TODO: implement me!
	return NULL;
}

void *sp_calloc (size_t nmemb, size_t size) {
	// TODO: implement me!
	return NULL;
}
