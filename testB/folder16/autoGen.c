#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{

	int i, num = 50;
	int *lineNum = &num;
	char fileNum = atoi(argv[1]);
	//FILE *fp[fileNum];
	char *command = malloc(sizeof(char)*200);

	char pt3[4], *linenum;

	//strcpy(command, "sed -n 1,300p movie_metadata.csv > moovie_metadata");

	strcpy(pt3, ".csv");

	for(i=0;i<fileNum;i++)
	{
		command = (char*)calloc(sizeof(command), sizeof(char));
		strcpy(command, "sed -n 1,300p movie_metadata.csv > movie_metadata");
		//char fileName[30];
		//sprintf(fileName, "movie_metadata%d.csv", num);
		linenum = (char*) lineNum;
		strcat(command, linenum);
		strcat(command, pt3);
		system(command);
		num+=50;
		
	}

//free(command);
return 0;
}
