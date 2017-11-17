#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <dirent.h>
#include <unistd.h>
//#include <sys/stat.h>
//#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include "sorter.h"
#include <errno.h>

int entry;
char *c, o[1024], *d;
//pid_t PIDs[1024];
char stream[1024];
movie** info;
int *totalProcesses;
pid_t root;
//int status[256];

DIR *dir;
struct dirent *ep;

int csvHandler(FILE* fp, char* d, char fileName[]);

void allocate(int rows){
	int r;
	info = malloc(rows * sizeof(movie*));
	for(r = 0; r < rows; r++){
		info[r] = (movie*)malloc(sizeof(movie));
		info[r]->color = (char*)malloc(sizeof(char));
		info[r]->director_name = (char*)malloc(sizeof(char));
		info[r]->actor_2_name = (char*)malloc(sizeof(char));
		info[r]->genres = (char*)malloc(sizeof(char));
		info[r]->actor_1_name = (char*)malloc(sizeof(char));
		info[r]->movie_title = (char*)malloc(sizeof(char));
		info[r]->actor_3_name = (char*)malloc(sizeof(char));
		info[r]->plot_keywords = (char*)malloc(sizeof(char));
		info[r]->movie_imdb_link = (char*)malloc(sizeof(char));
		info[r]->language = (char*)malloc(sizeof(char));
		info[r]->country = (char*)malloc(sizeof(char));
		info[r]->content_rating = (char*)malloc(sizeof(char));
	}
}

void deallocate(int rows){
	int r;
	for(r = 0; r < rows; r++){
		free(info[r]->color);
		free(info[r]->director_name);
		free(info[r]->actor_2_name);
		free(info[r]->genres);
		free(info[r]->actor_1_name);
		free(info[r]->movie_title);
		free(info[r]->actor_3_name);
		free(info[r]->plot_keywords);
		free(info[r]->movie_imdb_link);
		free(info[r]->language);
		free(info[r]->country);
		free(info[r]->content_rating);
		free(info[r]);
	}
	free(info);
}

//Returns a char pointer to the requested element in the struct
char** getString(movie** info,int entry, int element){
	switch(element){
		case 1:
			return &info[entry]->color;
		case 2:
			return &info[entry]->director_name;
		case 7:
			return &info[entry]->actor_2_name;
		case 10:
			return &info[entry]->genres;
		case 11:
			return &info[entry]->actor_1_name;
		case 12:
			return &info[entry]->movie_title;
		case 15:
			return &info[entry]->actor_3_name;
		case 17:
			return &info[entry]->plot_keywords;
		case 18:
			return &info[entry]->movie_imdb_link;
		case 20:
			return &info[entry]->language;
		case 21:
			return &info[entry]->country;
		case 22:
			return &info[entry]->content_rating;
	}
	return NULL;
}

long* getInt(movie** info,int entry, int element){
//printf("Getting int entry--> %d....element--> %d\n",entry, element);
	switch(element){
		case 3:
			return &info[entry]->num_critic_reviews;
		case 4:
			return &info[entry]->duration;
		case 5:
			return &info[entry]->director_facebook_likes;
		case 6:
			return &info[entry]->actor_3_facebook_likes;
		case 8:
			return &info[entry]->actor_1_facebook_likes;
		case 9:
			return &info[entry]->gross;
		case 13:
			return &info[entry]->num_voted_users;
		case 14:
			return &info[entry]->cast_total_facebook_likes;
		case 16:
			return &info[entry]->facenumber_in_poster;
		case 19:
			return &info[entry]->num_user_for_reviews;
		case 23:
			return &info[entry]->budget;
		case 24:
			return &info[entry]->title_year;
		case 25:
			return &info[entry]->actor_2_facebook_likes;
		case 28:
			return &info[entry]->movie_facebook_likes;
	}
	return NULL;
}

float* getFloat(movie** info,int entry, int element){
	switch(element){
		case 26:
			return &info[entry]->imdb_score;
		case 27:
			return &info[entry]->aspect_ratio;
	}
	return NULL;
}

//Tokenize elements and insert them into "info" structure

void insert(char* line){
	int k, element = 0;
	for(k = 0; k < strlen(line); k++)
	{
		element++;
		if(line[k] == ' ')
				k++;
		//String type handling
		if(element==1||element==2||element==7||element==10||element==11||element==12||element==15||element==17||element==18||element==20||element==21||element==22){
			char** val = getString(info,entry,element);
			int position = 0, par = 0, space = 0;// print;
			while(line[k] != ',' || par == 1){
				if(line[k] == '"'){
				//Quotations Detected
					if(par == 0)
						par = 1;
					else
						par = 0;
				}
				if(line[k] == ' ' || isprint(line[k]) == 0 || line[k]== '"')
						space++;
				else{
						*val = (char *)realloc(*val,position+2);
						strncat(*val, &line[k-space], 1+space);
						space = 0;
				}
				if(line[k] == '"' && par == 0){
						position++;
						*val = (char *)realloc(*val,position+2);
						char quote = '"';
						strncat(*val, &quote, 1);
				}
				position++;
				k++;
			}
	}


		//Int type handling
		if(element==3||element==4||element==5||element==6||element==8||element==9||element==13||element==14||element==16||element==19||element==23||element==24||element==25||element==28){
			long* val = getInt(info,entry,element);
			char* temp = malloc(sizeof(char)*128);
			int position = 0;
			while(line[k] != ',' && line[k] != '\n' && line[k] != '\0'){
				strncpy(&temp[position],&line[k], 1);
				position++;
				k++;
			}
			if(temp[0] != '\0')
				*val = atol(temp);
			else
				*val = -888;
			temp = NULL;
			free(temp);
		}


		//Float type handling
		if(element==26||element==27){
			float* val = getFloat(info,entry,element);
			char* temp = malloc(sizeof(char)*128);
			int position = 0;
			while(line[k] != ','){
				temp[position] = line[k];
				position++;
				k++;
			}
			if(temp[0] != '\0')
				*val = atof(temp);
			else
				*val = -888;
			temp = NULL;
			free(temp);
		}
	}
}	

void traverse(char d[]){

	if(d[0] != '\0'){
	    dir = opendir(d);
	    if(ENOENT == errno){
	        printf("\nERROR10: No such directory exists. Exiting program.\n");
	        exit(0);
	    }
	}
	else{
            dir = opendir("./");
            d[0]='.';d[1]='/';d[2]='\0';
        }
        if(o[0] != '\0' && *(o+strlen(o)-1) != '/')
            strcat(o, "/");
	if(*(d+(strlen(d)-1)) != '/')
            strcat(d, "/");
	int status = 1;
    while((ep = readdir(dir))){
        if(strcmp(&ep->d_name[strlen(ep->d_name)-4], ".csv") == 0){ //Found csv file
			char *trv, foundSorted = '0';
			for(trv = ep->d_name; *trv!='\0'; trv++){
				if(strncmp(trv, "-sorted-", 8) == 0){
						foundSorted = '1';
						//printf("%s already contains -sorted-!\n", ep->d_name);
				}
			}
			if(foundSorted == '1')
					continue;

            //printf("Found csv file: %s%s\n", d, ep->d_name);
			mlock(totalProcesses, sizeof *totalProcesses);
			(*totalProcesses)++;
			munlock(totalProcesses, sizeof *totalProcesses);
            pid_t pid;
            pid = fork();

            if(pid == 0){
                //printf("Forking for csv file %s\n",ep->d_name);
				//(*totalProcesses)++;
				//if(*totalProcesses > 1){
				//		printf(",");
				//		fflush(stdout);
				//}
				printf("%d,", getpid());
				fflush(stdout);
                char temp[1024];
                strcpy(temp, d);
                FILE *fp = fopen(strcat(temp, ep->d_name), "r");
                if(o[0] == '\0')
                    csvHandler(fp, d, ep->d_name);
                else{
					//printf("Custom o parameter: %s\n", o);
                    csvHandler(fp, o, ep->d_name);
				}
				//printf("CSV File: Returning %d\n", (*totalProcesses)+1);
				return;
            }
			//ep = readdir(dir);
        }
	 
        else if(ep->d_type == '\004' && ep->d_name[0] != '.'){ //Found directory
            //printf("Found directory %s\n", ep->d_name);
			mlock(totalProcesses, sizeof *totalProcesses);
			(*totalProcesses)++;
			munlock(totalProcesses, sizeof *totalProcesses);

			//if(root != getpid())
					//printf(",");
            pid_t pid;
			pid = fork();
			
            if(pid == 0){
				//(*totalProcesses)++;
				//if(*totalProcesses > 1){
				//		printf(",");
				//		fflush(stdout);
				//}
				//printf("Forking for directory %s\n", ep->d_name);
				printf("%d,", getpid());
				fflush(stdout);

				strcat(d, ep->d_name);strcat(d, "/");
                dir = opendir(d);
				continue;
            }//printf("PID: %d\n", pid);
        }
	}
	closedir(dir);
	wait(&status);
	//printf("Returning %d\n", (*totalProcesses));
	//printf("Exit status: %d\n", WEXITSTATUS(status));
	//*totalProcesses += WEXITSTATUS(status);
	//printf("Process finished at %s\n", d);
	return;
	
}

int csvHandler(FILE* fp, char* d, char fileName[]){
    /*		STEP 1
	 *Note: 'info' will be the array the file will be written into.
	 *Also the file pointer and opener will be innitalized here too. 
	 */
	entry = -1;
	   
	 /*		STEP 2.1
	  *Count number of entries and columns
	  */
	int numOfEntries = 0, numOfColumns = 1;
	int buff;
	//NOTE: Found out why its freezing
	while(!feof(fp))
	{
		buff = (char)fgetc(fp);
		if(numOfEntries == 0){
			if(buff == ',')
				numOfColumns++;
		}
		if(buff == '\n')
			numOfEntries++;
	}

	rewind(fp);


        if(fp == NULL)
        {
                //printf("ERROR02: Empty input. Exiting Program.\n");
                //exit(0);
				return 0;
        }
        else if(getKey(c) == 30)
        {
                //printf("ERROR03: Invalid key word. Exiting Program.\n");
                //exit(0);
				return 0;
        }


	/*		STEP 2.2
	 *Write file into array
	 
	 *Since we have 28 feilds, we can use a counter to determine which feild we are currently on
	 *That way with testcases that don't have certain feilds in them we can increment the counter to
	 *go to the next element in the array
	**/
	allocate(numOfEntries);
	numOfEntries--;
	int k = 0;
	while(!feof(fp))
	{	
		fgets(stream,sizeof(stream),fp);
		if(k != 0)
			insert(stream);
		else{
				if(strncmp(stream, "color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes", 417) != 0){
					//printf("Found directory: %s\n", d);
					//printf("ERROR04: Invalid column names. Exiting\n");
					deallocate(numOfEntries);
					//wait(NULL);
					return 0;
					//exit(0);
			}
			k = 1;
		}
		entry++;
	}

	mergesort(info, 0, numOfEntries-2,c);
	print(info, numOfEntries, fileName, d);
	deallocate(numOfEntries);
	//wait(NULL);
	fclose(fp);
        return 0;
		//exit(0);
}

int main(int argc, char* argv[])
{
	root = getpid();
	totalProcesses = mmap(NULL, sizeof *totalProcesses, PROT_READ | PROT_WRITE,MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	//totalProcesses = malloc(sizeof(int));
	*totalProcesses = 1;
    //char d[2048];
	//d[8] = '\0';
	d = malloc(sizeof(char)*1024);
	c = malloc(sizeof(char)*1024);
	d[0] = '\0';
	o[0] = '\0';
	if(argc < 3)
	{
		printf("ERROR00: Invalid number of inputs. Exiting\n");
		return 0;
	}
	int i,t_params = 0;
	for(i = 1; i < argc; i++){
            if(argv[i][0] == '-'){
					t_params++;
		if(i+1 >= argc){
			printf("ERROR09: Invalid parameters. Exiting\n");
			return 0;
		}
		switch(argv[i][1]){
            case 'c':
				c = argv[i+1];
				break;
			case 'd':
				//d = argv[i+1];
				memcpy(d, argv[i+1], strlen(argv[i+1]));
                        	break;
			case 'o':
				//o = argv[i+1];
                                memcpy(o, argv[i+1], strlen(argv[i+1]));
				break;
			default:
				printf("ERROR08: Invalid parameter. Exiting\n");
				exit(0);
			}
		}
	}

	if(t_params*2 < (argc-1)){
		printf("ERROR12: Invalid Arguments. Exiting\n");
		exit(0);
	}
	
	if(o[0] != '\0'  && access(o, F_OK) == -1)
	{
		printf("ERROR11: No such output directory exists. Exiting program.\n");
		exit(0);
	}

	if(getKey(c) == 30){
		printf("Invalid column name. Exiting\n");
		exit(0);
	}	

	printf("Initial PID: %d\n", getpid());
	printf("PIDs of all child processes: ");
	fflush(stdout);
	traverse(d);
	fflush(stdout);
	wait(NULL);
	fflush(stdout);
	if(getpid() == root){
	    wait(NULL);
		printf("\nTotal Number of processes: %d\n",*totalProcesses);
	}
	
	//free(totalProcesses);
	free(d);
	//free(o);
	return 0;
}
