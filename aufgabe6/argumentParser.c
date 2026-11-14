#include "argumentParser.h"

#include <string.h>
#include <errno.h>

static char** argumentsBegin;
static char** argumentsEnd;
static char** optionsBegin;
static char** optionsEnd;
static char* command;


static int isOption(char* opt) {
	if ( opt[0] != '-' ) {
		return 0;
	}
	if ( strchr(opt, '=') == NULL ) {
		return 0;
	}

	return 1;
}

static int isArgument(char* arg) {
	return ! isOption(arg);
}

int initArgumentParser(int argc, char* argv[]) {
	command = argv[0];

	if ( argc == 1 ) {
		argumentsBegin = NULL;
		argumentsEnd = NULL;
		optionsBegin = NULL;
		optionsEnd = NULL;
		return 0;
	}

	for ( int i = 1; i < argc ; i++ ) {
		if ( argumentsBegin == NULL ) {
			argumentsBegin = argv+i;
		}

		if ( isOption(argv[i]) && argumentsEnd == NULL ) {
			argumentsEnd = argv+i;
			optionsBegin = argv+i;
		}

		if ( isArgument(argv[i]) && argumentsEnd != NULL ) {
			errno = EINVAL;
			return -1;
		}
	}

	optionsEnd = argv+argc; // Point to NULL pointer

	if ( argumentsEnd == NULL ) {
		argumentsEnd = optionsEnd;
		optionsBegin = optionsEnd;
	}

	return 0;
}

char* getCommand(void) {
	return command;
}

int getNumberOfArguments(void) {
	return argumentsEnd - argumentsBegin;
}

char* getArgument(int index) {
	if ( index < 0 || index >= getNumberOfArguments() ) {
		return NULL;
	}
	return argumentsBegin[index];
}

char* getValueForOption(const char* keyName) {
	for ( char** lauf = optionsBegin; lauf != optionsEnd; lauf++ ) {
		if ( ! isOption(*lauf) ) {
			continue;
		}
		if ( strncmp((*lauf)+1, keyName, strlen(keyName)) ) {
			continue;
		}
		if ( (*lauf)[strlen(keyName)+1] != '=' ) {
			continue;
		}
		return (*lauf)+strlen(keyName)+2;
	}
	return NULL;
}
