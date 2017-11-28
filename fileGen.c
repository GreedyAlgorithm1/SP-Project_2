#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
//#include <pthread.h>

char * root = "testdir";
char * info[6000];
int seed = 0;
int lableNum=0;
/*
pthread_mutex_t lock;
pthread_t tids[256];
int counter=0; 
*/
typedef struct dir_meta{
	int depth;
	char * currdir;
}dirinfo;

dirinfo * dir_info_create(char * rootpath, int depth);
dirinfo * dir_info_destroy(dirinfo * info);
void dirgen(char * rootpath, int depth);
void * dirgen_stub(void * currdir);


void rnum(int * arr,int low,int hi){
	int len = hi-low+1;
	if(len<=0) {
		printf("arr not generated!\n");
		return;
	}
	
	//fill array with numbers inorder
	int i=0, temp = low,r;
	while(i<len){
		arr[i] = temp;
		
		i++;
		temp++;
	}
	/*
	for(i=0;i<len;i++)
		printf("%d\n",arr[i]);
	*/
	
	int tempseed;
	//lock
	//pthread_mutex_lock(&lock);
	tempseed = seed;
	seed++;	
	//pthread_mutex_unlock(&lock);
	//lock
	
	srand(time(NULL)+tempseed);

	
	//Fisher-Yates shuffle algorithm
	for(i = len-1; i>0;i--){
		r = rand()%i;
		
		temp = arr[i];
		arr[i] = arr[r];
		arr[r] = temp;
	}

}

void fileScrumber(char * filename,int len){
	int arr[len];
	arr[0] = 0;
	
	rnum(&arr[1],1,len-1);
	
	//printf("filename is :%s\n",filename);
	FILE * out = fopen(filename,"w+");
	if(!out){
		printf("file did not created\n");
		exit(0);
	}
	
	int k =0;
	while(k<101){
		fprintf(out,"%s",info[arr[k]]);
		k++;
	}
	fclose(out);
}

dirinfo * dir_info_create(char * rootpath, int depth){
	dirinfo * newdir = (dirinfo*) malloc(sizeof(dirinfo));
	newdir->depth = depth;
	newdir->currdir = (char*)malloc(strlen(rootpath)+1);
	strcpy(newdir->currdir,rootpath);
	return newdir;
}

dirinfo * dir_info_destroy(dirinfo * info){ //struct=dir_info_destroy(struct);
	free(info->currdir);
	free(info);
	return NULL;
}
void dirgen(char * rootpath, int depth){
	if(depth==0) return;
	printf("attemp to make dir%s\n",rootpath);
	mkdir(rootpath,S_IRWXU);
	dirinfo * newdir = dir_info_create(rootpath,depth-1);
	
	dirgen_stub(newdir);
	
	/*
	pthread_mutex_lock(&lock);
	pthread_create(&tids[counter],NULL,dirgen_stub,newdir);
	counter++;
	pthread_mutex_unlock(&lock);
	*/
	newdir = dir_info_destroy(newdir);
}
void * dirgen_stub(void * currdir){

	dirinfo * currinfo=(dirinfo*)currdir;
	
	
	char * subdir1 = (char*) malloc(strlen(currinfo->currdir) +17);
	char * subdir2 = (char*) malloc(strlen(currinfo->currdir) +17);
	
	sprintf(subdir1,"%s/%s1_level%d",currinfo->currdir,"testdir",currinfo->depth);
	sprintf(subdir2,"%s/%s2_level%d",currinfo->currdir,"testdir",currinfo->depth);
	
	
	dirgen(subdir1,currinfo->depth);
	dirgen(subdir2,currinfo->depth);
	
	
	char * filename = (char*) malloc(strlen(currinfo->currdir)+15);
	int k=0;
	while(k<200){
		sprintf(filename,"%s/%s%d.csv",currinfo->currdir,"test",k);

		fileScrumber(filename,lableNum);
		k++;
	}
	
	free(filename);
	free(subdir1);
	free(subdir2);
	return NULL;
}


int main(int argc, char ** argv){
//args: src_file, depth, numfile in each level

	FILE * f = fopen(argv[1],"r");
	if(!f) {printf("file not found\n");exit(1);}
	int depth = atoi(argv[2]);
	
	
	int i=0;
	
	char line[2000];
	while(!feof(f)){
		
		fgets(line,2000,f);
		
		info[i] = (char *) malloc(strlen(line)+1);
		
		sprintf(info[i],"%s",line);
		
		i++;
	}
	fclose(f);
	lableNum = i-1;
	
	char * rootpath = (char *)malloc(32);
	sprintf(rootpath,"./%s_level_%d",root,depth);
	
	
	dirgen(rootpath,depth);	
	
	free(rootpath);
	/*
	int t = 0;
	while(t < counter){
		pthread_join(tids[t],NULL);
		t++;
	}
	*/
	int k=0;
	while(k<i){
		free(info[k]);
		k++;
	}
	return 0;	
}



