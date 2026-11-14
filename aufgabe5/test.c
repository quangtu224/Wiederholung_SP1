#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "halde.h"

int main(int argc, char *argv[]) {
	printList();

	char *m1 = sp_malloc(200*1024);
	printList();

	sp_free(m1);
	printList();

	exit(EXIT_SUCCESS);
}
