#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main(int argc, char **argv)
{
	
	int i;
	//char *dir = argv[1];
	FILE *files[10];
	//DIR dir;
	//char command[100];
	//strcpy(command, "./sorter -c duration -d ");
	//strcat(command, dir);

	for(i=0; i<2; i++)
	{
		char fileName[20];
		sprintf(fileName, "test%d", i);
		files[i] = fopen(fileName, "w");
		system("sed -n 1,20p movie_metadata.csv > movie_metadata20.csv");
		

	} 


}
