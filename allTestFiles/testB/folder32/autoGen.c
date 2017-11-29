#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *command;


int main(int argc, char **argv)
{

	int i, num = 10;
	int *lineNum = &num;
	char fileNum = atoi(argv[1]);
	//FILE *fp[fileNum];
	//command = malloc(sizeof(char)*200);

	char pt3[4], *linenum, fileExt[8];

	//strcpy(command, "sed -n 1,300p movie_metadata.csv > moovie_metadata");

	strcpy(pt3, ".csv");

	for(i=0;i<fileNum;i++)
	{
		command = (char*)calloc(sizeof(command), sizeof(char));
		strcpy(command, "sed -n 1,300p movie_metadata.csv > Movie_Metadata");
		//char fileName[30]m
		//sprintf(fileName, "movie_metadata%d.csv", num);
		linenum = (char*) lineNum;
		strcat(fileExt, linenum);
		strcat(fileExt, pt3);
		strcat(command, fileExt);
		system(command);
		num+=13;
		
	}

//free(command);
return 0;
}
