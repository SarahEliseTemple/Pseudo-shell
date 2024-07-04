/*Command.C 
 * Sarah Temple
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h> //added to make stat work
#include <sys/types.h> //added to make mkdir work
#include <fcntl.h> //added to make open() work.
#include <libgen.h> //added for basename()
#include "command.h"


void listDir(){ /*for the ls command*/
	//Got an example of what the function should look like from Protfolio courses youtube.
	DIR *directory;
	struct dirent *current;

	directory = opendir(".");
	
	//check for realness
	if (directory == NULL) {
		//not real
		write(2, "could not open directory in ls function.\n",42); 
		return;
	}

	//ls command
	while((current = readdir(directory)) != NULL) {
		const char* str_current = current->d_name;
		write(1, str_current, strlen(str_current));
		write(1, " ", 1);
	}
	write(1, "\n", 1);	
	if (closedir(directory)==-1){
		write(2, "error in closing directory.\n", 29);
	}
}
void showCurrentDir(){	/*for the pwd command*/
	char buffer[4098];//NEED TO FIX!
	if (getcwd(buffer, sizeof(buffer)) == NULL) {
		write(2, "getcwd() error\n", 15);
	}
	else {
		write(1, buffer, strlen(buffer));
		write(1, "\n", 1);
	}	
}

void makeDir(char *dirName){ /*for the mkdir command*/
	struct stat st = {};
	if(stat(dirName, &st) ==-1) {
		if(mkdir(dirName, 0777)== -1) {
			write(2, "error with mkdir()\n", 20);
		}
	}
	else{
		write(2, "directory already here!\n", 25);
	}
}

void changeDir(char *dirName){
	if(chdir(dirName) == -1) {
		write(2, "error changing directory.\n", 27);
	}
}	/*for the cd command*/

void copyFile(char *sourcePath, char *destinationPath){
	//create a new file only if new file doesnt exist
	struct stat statdbuff;
	if(stat(destinationPath, &statdbuff) == -1) {
		write(2, "Error in statdbuff\n", 20);
		return;
	}
	if(S_ISDIR(statdbuff.st_mode)) {
		//it is a dir, we want it to write to basename of sourcepath in dir
		char* name = basename(sourcePath);
		strcat(destinationPath, name);
	}
	
	//if destinationpath == directory use basename() of sourcepath
	int dest = creat(destinationPath, 0777);
	if (dest == -1) {
		write(2, "Error in Opening destination\n", 25);
		return;
	}
	int text = open(sourcePath, O_RDONLY);
	if (text == -1) {
		write(2, "Error in Opening Output\n", 25);
		return;
	}
	else{
		//opening file to read
		//declear line_buffer
		size_t len = 4096;
		char* line_buf = malloc (len*sizeof(char));
		ssize_t actchar;
		//loop until the file is over
		while ((actchar = read(text, line_buf, len)) > 0)
		{
			write(dest, line_buf, actchar);
		}
	}
	if (close(text) == -1){
		write(2, "error in closing file read.\n",27);
	}
	if (close(dest) == -1) {
		write(2, "error in closing file printed.\n",30);
	}
}	/*for the cp command*/

void moveFile(char *sourcePath, char *destinationPath){
	//create a new file only if new file doesnt exist
	struct stat statdbuff;
	if(stat(destinationPath, &statdbuff) == -1) {
		write(2, "Error in statdbuff\n", 20);
		return;
	}
	if(S_ISDIR(statdbuff.st_mode)) {
		//it is a dir, we want it to write to basename of sourcepath in dir
		char* name = basename(sourcePath);
		strcat(destinationPath, name);
	}
	//if destinationpath == directory use basename() of sourcepath
	int dest = creat(destinationPath, 0777);
	if (dest == -1) {
		write(2, "Error in Opening destination\n", 25);
		return;
	}
	int text = open(sourcePath, O_RDONLY);
	if (text == -1) {
		write(2, "Error in Opening Output\n", 25);
		return;
	}
	else{
		//opening file to read
		//declear line_buffer
		size_t len = 4096;
		char* line_buf = malloc (len*sizeof(char));
		ssize_t actchar;
		//loop until the file is over
		while ((actchar = read(text, line_buf, len)) > 0)
		{
			write(dest, line_buf, actchar);
		}
	}
	
	if(close(dest) ==-1) {
		write(2, "error in closing file printed.\n",30);
	}
	if (close(text) ==-1){
		write(2, "error in closing file printed.\n",30);
	}
	deleteFile(sourcePath);
}	/*for the mv command*/

void deleteFile(char *filename){
	if(remove(filename)==-1) {
		write(2, "error in deleting file\n", 24);
	}
}	/*for the rm command*/

void displayFile(char *filename){
	int text = open(filename, O_RDONLY);
	if (text == -1) {
		write(2, "Error in Opening Output\n", 25);
		return;
	}
	//opening file to read
	//declear line_buffer
	size_t len = 4096;
	char* line_buf = malloc (len*sizeof(char));
	ssize_t actchar;
	//loop until the file is over
	while ((actchar = read(text, line_buf, len)) > 0)
	{
		write(1, line_buf, actchar);
	}
	if (close(text) ==-1){
		write(2, "error in closing file printed.\n",30);
	}
}	/*for the cat command*/
