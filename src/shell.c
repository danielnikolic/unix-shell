// UNIX Shell

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

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
		
		if (strlen(input) == 0)
		{
			printf("\n");
			continue;
		}
		
		if (strcmp(input, "exit") == 0)
		{
			printf("Goodbye for now!\n");
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
		else // check to see if user entered a Linux program command
		{
			int argumentCount = getArgumentCount(input);
			
			char * argumentList[argumentCount];
	
			char * token = strtok(input, " ");
			int i = 0;
			while (token != NULL) 
			{
				argumentList[i] = token;
				token = strtok(NULL, " ");
				i++;
			}
	
			argumentList[argumentCount] = (char*) NULL;
	
			int child;
			int status = 0;
	
			child = fork();
			if (child == 0)
			{
				execvp(argumentList[0], argumentList);
				perror("\0");
				return 0;
			}
			else
			{
				usleep(1000);
				status = -1;
				waitpid(child, &status, 0);
			}
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
	
	removeExtraSpace(input);
}

int getArgumentCount(char input[])
{
	int argumentCount = 1;
	
	for (int i = 0; i < strlen(input); i++)
	{
		if (input[i] == ' ')
		{
			argumentCount++;
		}
	}
	
	return argumentCount;
}

void removeExtraSpace(char input[])
{
	int n = strlen(input);
	
	int space = 0;
	int k = 0;

	for (int i = 0; i < n; i++)
	{
		while (k == 0 && i < n && input[i] == ' ') 
		{
			i++;
		}

		if (input[i] == ' ')
		{
			if (!space)
			{
				input[k++] = input[i];
				space = 1;
			}
		}
		else 
		{
			input[k++] = input[i];
			space = 0;
		}
	}
	
	if (input[n - 1] == ' ')
	{
		input[k - 1] = '\0';
	}
	else
	{
		input[k] = '\0';
	}
}
