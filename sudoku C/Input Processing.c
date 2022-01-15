#include "Input Processing.h"

int GetInt(char* message)
{

#define MAX_CHAR 12 // amount of chars in INT_MAX with end line char and EOF char

	//create and initialize an input buffer
	char* inputBuffer = malloc(sizeof(char) * MAX_CHAR);
	memset(inputBuffer, 0, MAX_CHAR);

	while (1)
	{

		printf(message); //print the message before getting input

		fgets(inputBuffer, MAX_CHAR, stdin); //get input


		//check if there are too many characters in input
		if (inputBuffer[strlen(inputBuffer) - 1] != '\n')
		{
			fprintf(stderr, "Too many digits were entered, max is 10\n");
			
			//clear inputBuffer by comparing each char with \n and EOF chars, using getchar() to clear the current char
			for (char c = 0; (c = getchar()) != '\n' && c != EOF; ); 

			continue;

		}

		errno = 0;
		char* nul = NULL; //string gotten from after numbers in inputBuffer 
		int returnInt = strtol(inputBuffer, &nul, 10); //convert inputBuffer to integer

		//check if inputBuffer is all numbers or if there is an error
		if (inputBuffer == nul || nul[0] != '\n' || errno != 0 )
		{
			fprintf(stderr, "Could not convert input to integer\n");
			continue;
		}
		
		return returnInt;

	}

}
