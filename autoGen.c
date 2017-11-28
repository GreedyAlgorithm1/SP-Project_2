#include <stdio.h>
#include <stdlib.h>
#include <unistd.lib>
#include <string.h>


int main(int argc, char **argv)
{
	
/*****
	printf("Starting\n");
	int i, lineNum;
	int fileNum = atoi(argv[1]);
	FILE *fp[fileNum];
	char command[100];
	char *pt1, *pt2,*pt3;
	pt1 = "sed -n 1, ";
	pt2 = "p movie_metadata.csv > movie_metadata";
	pt3 = ".csv";
	strcpy(command, pt1);
	printf("%s\n", command);
	
	for(i = 0; i< fileNum; i++)
	{
		lineNum = rand();
		char fileName[20];
		sprintf(fileName, "movie_metadata%d.csv", lineNum);
		strcat(command,  (char*)lineNum);
		strcat(command, pt2);
		strcat(command,  (char*) lineNum);
		strcat(command, pt3);
		printf("%s\n", command);
		fp[i] = fopen(fileName, "w");
		system(command);

	}
*****/
	int i;
	FILE *files[4];
	for(i=0; i< 4; i++)
	{
		char filename[20];
		sprintf(filename, "%d.csv", i);
		files[i] = fopen(filename, "w");

	}


	return 0;
}
