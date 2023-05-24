
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main (int c, char *argv[]) {
	char	*str;
	str = malloc(100000);
	while (1)
	{
		read(0, str, 1);
	}
    return EXIT_SUCCESS;
}
