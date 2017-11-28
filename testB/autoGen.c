#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv)
{

	unsigned int i, lineNum;
	int fileNum = atoi(argv[1]);
	FILE *fp;
	char command[248];
	char *pt1, *pt2,*pt3;
	pt1 = "sed -n 1, ";
	pt2 = "p movie_metadata.csv > movie_metadata";
	pt3 = ".csv";
	strcpy(command, pt1);
	
	for(i = 0; i< fileNum; i++)
	{
		lineNum = rand();
		char fileName[20];
		sprintf(fileName, "movie_metadata%d.csv", lineNum);
		strcat(command,  (char*)lineNum);
		strcat(command, pt2);
		strcat(command,  (char*) lineNum);
		strcat(command, pt3);
		fp = fopen(fileName, "w");
		system(command);

	}
	
	return 0;
}
