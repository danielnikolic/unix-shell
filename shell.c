// UNIX Shell

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shell.h"

int main(int argc, char * argv[])
{
	char* prompt = "> ";
	char input[100];
	
	while (1)
	{
		printf(prompt);
		fgets(input, sizeof(input), stdin);
		
		validateInput(input);
		
		if (strcmp(input, "exit") == 0)
		{
			return 0;
		}
		else if (strcmp(input, "pid") == 0)
		{
			printf("Process ID: %d\n", getpid());
		}
		else if (strcmp(input, "ppid") == 0)
		{
			printf("Parent Process ID: %d\n", getppid());
		}
		
		printf("\n");
	}
}

void validateInput(char input[])
{
	// terminates the input
	if ((strlen(input) > 0) && (input[strlen(input) - 1] == '\n'))
	{
		input[strlen(input) - 1] = '\0';
	}
}