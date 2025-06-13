#include <readline/readline.h>
#include <stdio.h>

int main(void)
{
	char *line;

	line = readline(NULL);
	printf("READ :%s\n",line);
	return (1);
}