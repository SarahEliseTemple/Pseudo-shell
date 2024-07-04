/*
 * string_parser.c
 *
 *  Created on: Nov 25, 2020
 *      Author: gguan, Monil
 *      Added to: Sarah Temple
 *  Edited April 8, 2024
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_parser.h"

#define _GUN_SOURCE

int count_token (char* buf, const char* delim)
{
	//TODO：
	/*
	*	#1.	Check for NULL string
	*	#2.	iterate through string counting tokens
	*		Cases to watchout for
	*			a.	string start with delimeter
	*			b. 	string end with delimeter
	*			c.	account NULL for the last token
	*	#3. return the number of token (note not number of delimeter)
	*/
	if (buf == NULL) {
		return 0; //no things :(
	}
	
	char *saveptr; //doesnt do anythingi
	int count = 0;
	char *token = strtok_r(buf, delim, &saveptr); // token == ls
	while(token) {
		count++;
		token = strtok_r(NULL, delim, &saveptr); 
		// goes through each one. 
 	}
	return count;
}

command_line str_filler (char* buf, const char* delim)
{
	//TODO：
	/*
	*	#1.	create command_line variable to be filled and returned
	*	#2.	count the number of tokens with count_token function, set num_token. 
    *           one can use strtok_r to remove the \n at the end of the line.
	*	#3. malloc memory for token array inside command_line variable
	*			based on the number of tokens.
	*	#4.	use function strtok_r to find out the tokens 
    *   #5. malloc each index of the array with the length of tokens,
	*			fill command_list array with tokens, and fill last spot with NULL.
	*	#6. return the variable.
	*/
	command_line return_me;
	char* fake_id = (char*)malloc((strlen(buf)+1)*sizeof(char));
	strcpy(fake_id, buf);
	fake_id[strlen(buf)] ='\0';
	return_me.num_token = count_token(fake_id, delim);
	free(fake_id); //no more going to bars :(
	return_me.command_list = (char**)malloc(sizeof(char*)*(return_me.num_token+1));
	char *no_newline;
	char *without_newline = strtok_r(buf, "\n", &no_newline);
	char *saveptr1;
	char *token = strtok_r(without_newline, delim, &saveptr1); 
	int count = 0;
	while(token) {
		return_me.command_list[count] = (char*)malloc((strlen(token)+1)*sizeof(char));
		//fprintf(stderr, "%s\n", token);
		strcpy(return_me.command_list[count], token); //strcpy may not be allowed. have to check
		count++;
		token = strtok_r(NULL, delim, &saveptr1); 
	}
	return_me.command_list[count] = NULL;

	return return_me;




}


void free_command_line(command_line* command)
{
	//TODO：
	/*
	*	#1.	free the array base num_token
	*/
	for(int i = 0; i < command->num_token; i++) {
		free(command->command_list[i]);
	}
	free(command->command_list);
}

/*
 * char *mySTr = "diff expected.txt out.txt"
 * char buf[] = "ls -a -l -p"
 * 		//["ls", "-a", "-1", "..."]
 * char *saveptr; //doesnt do anything
 *
 * char *token = strtok_r(buf, " ", &saveptr); // token == ls
 * while(token) {
 * 	token = strtok_r(NULL, " ", &saveptr); // goes through each one. 
 * }
 * You know you are done when token returns null. 
 */
