// UNIX Shell

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shell.h"

#define INPUT_LENGTH 100

int main(int argc, char * argv[])
{
	char* prompt = "> ";
	char input[INPUT_LENGTH];
	
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
		else if (strncmp(input, "cd", 2) == 0)
		{
			if (strlen(input) == 2)
			{
				chdir(getenv("HOME"));
			}
			else
			{
				char dir[strlen(input) - 3];
				strcpy(dir, input + 3);
				
				int status = chdir(dir);
				
				if (status == -1)
				{
					printf("Invalid directory\n");
				}
			}
		}
		else if (strcmp(input, "pwd") == 0)
		{
			char cwd[INPUT_LENGTH];
			if (getcwd(cwd, sizeof(cwd)) != NULL)
			{
				printf("%s\n", cwd);
			}
			else
			{
				printf("Could not find working directory\n");
			}
		}
		else
		{
			
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