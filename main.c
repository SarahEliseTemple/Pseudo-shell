/*Sarah Temple
 * April 16 main.c 
 *TODO
 free and malloc func
 check if file or user input
 Write Open file or accept user input
 Make that a variable and accept that through the rest of the file
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "string_parser.h"
#include "command.h"
#define _GNU_SOURCE




int run_function(command_line small_token_buffer) {
	char* function = small_token_buffer.command_list[0];
	if (strcmp(function, "ls")== 0) {
		if(small_token_buffer.command_list[1] != NULL) {
			write(1, "Error, not correct usage of ls\n", 32);
			return 1;
		}
		listDir();
		//RUN ls
	}
	else if(strcmp(function, "exit")==0) {
		write(1, "exit\n", 5);
		return 0;

	}
	else if(strcmp(function, "pwd")==0){
		if(small_token_buffer.command_list[1] != NULL) {
			write(1, "Error, not correct usage of pwd\n", 32);
			return 1;
		}
		//RUN 
		showCurrentDir(); /*for the pwd command*/
	}
	else if(strcmp(function, "mkdir")==0){
		if(small_token_buffer.command_list[2] != NULL) {
			write(1, "Error, not correct usage of mkdir\n", 32);
			return 1;
		}
		makeDir(small_token_buffer.command_list[1]); /*for the mkdir command*/
	}
	else if(strcmp(function, "cd")==0){
		if(small_token_buffer.command_list[2] != NULL) {
			write(1, "Error, not correct usage of cd\n", 32);
			return 1;
		}
		changeDir(small_token_buffer.command_list[1]); /*for the cd command*/
	}
	else if(strcmp(function, "cp")==0){
		if(small_token_buffer.command_list[3] != NULL) {
			write(1, "Error, not correct usage of cp\n", 32);
			return 1;
		}
		copyFile(small_token_buffer.command_list[1], small_token_buffer.command_list[2]);
	       	/*for the cp command*/
	}
	else if(strcmp(function, "mv")==0){
		if(small_token_buffer.command_list[3] != NULL) {
			write(1, "Error, not correct usage of mv\n", 32);
			return 1;
		}
		moveFile(small_token_buffer.command_list[1], small_token_buffer.command_list[2]);
	       	/*for the mv command*/
	}
	else if(strcmp(function, "rm")==0){
		if(small_token_buffer.command_list[2] != NULL) {
			write(1, "Error, not correct usage of rm\n", 32);
			return 1;
		}
		deleteFile(small_token_buffer.command_list[1]); /*for the rm command*/
	}
	else if(strcmp(function, "cat")==0){
		if(small_token_buffer.command_list[2] != NULL) {
			write(1, "Error, not correct usage of cat\n", 32);
			return 1;
		}
		displayFile(small_token_buffer.command_list[1]); /*for the cat command*/
	}
	else {
		write(1, "Error Command not found. Probably too complex for me :(\n", 56);
	}
	write(1, ">>> ", 4);
	return 1;
}
int process_line(char* line) {
	command_line large_token_buffer;
	command_line small_token_buffer;
	//tokenize line buffer
	//large token is seperate`d by ";"
	large_token_buffer = str_filler (line, ";");
	//iterate through each large token
	int noExit = 1;
	for (int i = 0; large_token_buffer.command_list[i] != NULL && noExit == 1; i++)
	{
	
		//tokenize large buffer
		//smaller token is seperated by " "(space bar)
		small_token_buffer = str_filler (large_token_buffer.command_list[i], " ");
		noExit = run_function(small_token_buffer);	
		//free smaller tokens and reset variable
		
		free_command_line(&small_token_buffer);
		memset (&small_token_buffer, 0, 0);
	}

	//free smaller tokens and reset variable
	free_command_line (&large_token_buffer);
	memset (&large_token_buffer, 0, 0);
	
	return noExit;
}
int main(int argc, char const *argv[])
{
	//make a file descriptor that we will write to. 
	
	int noExit = 1; //dont exit until 0
	if(argc > 2) {
		FILE *check = freopen("output.txt", "a+", stdout);
		if (check == NULL) {
			write(2, "Error in Opening Output\n", 25);
			exit(1);
			//CHECK THIS FOR ERRORS
		}
		//opening file to read
		FILE *inFPtr;
		inFPtr = fopen (argv[2], "r");
		if (inFPtr == NULL) {
			write(2, "Error in Opening file\n", 23);
			exit(1);
			//CHECK THIS FOR ERRORS
		}
		//declear line_buffer
		size_t len = 4096;
		char* line_buf = malloc (len*sizeof(char));
		
		int line_num = 0;

		//loop until the file is over
		while (getline (&line_buf, &len, inFPtr) != -1 && noExit==1)
		{
			noExit = process_line(line_buf);
		}
	fclose(inFPtr);
	}
	else { //interactive mode
		write(1, ">>> ", 4);
		while(noExit == 1) {//main loop
			//looked up useing getline on dev-notes.eu
			ssize_t strlen = 0;
			size_t len = 4096;
			char* line = malloc(len);
			strlen = getline(&line, &len, stdin);
		
			noExit = process_line(line);
			free(line);
		}
	}
}
