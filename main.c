#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "ls2.h"

/**
 * Main function
 * Usage: ls2 <path> [exact-match-pattern]
 */
int main(int argc, char* argv[]) {
	// stack stores the lines to print out
	
	stack_t *s = initstack();
	mode1(argv[1], s, 0);
	

	// print stack
	printstack(s);

	// free up stack
	freestack(s);
	return 0;
}
