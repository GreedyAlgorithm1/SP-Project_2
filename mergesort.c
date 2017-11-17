#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorter.h"

void mergesort(movie **array, int l, int r, char *word)
{

	//a(p) is left index, b(r) is right, m(q) is middle

	char *key = word;

	if(l<r)
	{
		int m = ((l+r)/2);
		//if((l-r) > 1)
			mergesort(array,l,m, key);
		//if((l-r) > 1)
			mergesort(array,m+1, r, key);
		merge(array, l, m, r, key);
	}
}




void print(movie **info, int numOfEntries, char fileName[], char* path){
	//printf("Here\n");
	//printf("Trying to create file %s%s\n", path, fileName);
    //char *outFile = malloc(strlen(path)+strlen(fileName)+10);
	char* outFile = path;
    //char* outFile = memcpy(outFile, path, strlen(path)+1);
    strcat(outFile, fileName);
    outFile[strlen(outFile)-4] = '\0';
    strcat(outFile, "-sorted-");
    strcat(outFile, c);
    strcat(outFile, ".csv");
    
    //printf("Created file %s\n", outFile);
    FILE* fp = fopen(outFile, "w");
    
    //free(outFile);
    
    
	int i;
	fprintf(fp, "color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes\n");
//NOTE: Need to input file to args in fprintf
	for(i =0; i< numOfEntries-1; i++)
	{	
		fprintf(fp,"%s,%s,",info[i]->color, info[i]->director_name);
		if(info[i]->num_critic_reviews != -888)
				fprintf(fp,"%ld,",info[i]->num_critic_reviews);
		else
				fprintf(fp,",");
		if(info[i]->duration != -888)
				fprintf(fp,"%ld,",info[i]->duration);
		else
				fprintf(fp,",");
		if(info[i]->director_facebook_likes != -888)
				fprintf(fp,"%ld,",info[i]->director_facebook_likes);
		else
				fprintf(fp,",");
		if(info[i]->actor_3_facebook_likes != -888)
				fprintf(fp,"%ld,",info[i]->actor_3_facebook_likes);
		else
				fprintf(fp,",");
		fprintf(fp,"%s,",info[i]->actor_2_name);
		if(info[i]->actor_1_facebook_likes != -888)
				fprintf(fp,"%ld,",info[i]->actor_1_facebook_likes);
		else
				fprintf(fp,",");
		if(info[i]->gross != -888)
				fprintf(fp,"%ld,",info[i]->gross);
		else
				fprintf(fp,",");
		fprintf(fp,"%s,%s,%s,",info[i]->genres, info[i]->actor_1_name, info[i]->movie_title);
		if(info[i]->num_voted_users != -888)
				fprintf(fp,"%ld,",info[i]->num_voted_users);
		else
				fprintf(fp,",");
		if(info[i]->cast_total_facebook_likes != -888)
				fprintf(fp,"%ld,",info[i]->cast_total_facebook_likes);
		else
				fprintf(fp,",");
		fprintf(fp,"%s,",info[i]->actor_3_name);
		if(info[i]->facenumber_in_poster != -888)
				fprintf(fp,"%ld,",info[i]->facenumber_in_poster);
		else
				fprintf(fp,",");
		fprintf(fp,"%s,%s,",info[i]->plot_keywords, info[i]->movie_imdb_link);
		if(info[i]->num_user_for_reviews != -888)
				fprintf(fp,"%ld,",info[i]->num_user_for_reviews);
		else
				fprintf(fp,",");
		fprintf(fp,"%s,%s,%s,",info[i]->language,info[i]->country, info[i]->content_rating);
		if(info[i]->budget != -888)
				fprintf(fp,"%ld,",info[i]->budget);
		else
				fprintf(fp,",");
		if(info[i]->title_year != -888)
				fprintf(fp,"%ld,",info[i]->title_year);
		else
				fprintf(fp,",");
		if(info[i]->actor_2_facebook_likes != -888)
				fprintf(fp,"%ld,",info[i]->actor_2_facebook_likes);
		else
				fprintf(fp,",");
		if((int)(info[i]->imdb_score)*10 >= 0)
				fprintf(fp,"%3.1f,", info[i]->imdb_score);
		else
				fprintf(fp,",");
		if((int)(info[i]->aspect_ratio)*10 >= 0){
				if(((int)(info[i]->aspect_ratio*100)%10) == 0)
					fprintf(fp,"%3.1f,",info[i]->aspect_ratio);
				else
					fprintf(fp,"%4.2f,",info[i]->aspect_ratio);
		}
		else
				fprintf(fp,",");
		fprintf(fp,"%ld\n",info[i]->movie_facebook_likes);
	}
}

//determines key for struct purposes
int getKey(char *key)
{

//printf("Key sorted by ----> %s.\n", key);
	char *var = key;
	if(strcmp(var, "color") == 0)
		return  1;
	if(strcmp(var, "director_name") == 0)
		return 2;
	if(strcmp(var, "num_critic_for_reviews") == 0)
		return 3;
	if(strcmp(var, "duration") == 0)
		return 4;
	if(strcmp(var, "director_facebook_likes") == 0)
		return 5;
	if(strcmp(var, "actor_3_facebook_likes") == 0)
		return 6;
	if(strcmp(var, "actor_2_name") == 0)
		return 7;
	if(strcmp(var, "actor_1_facebook_likes") == 0)
		return 8;
	if(strcmp(var, "gross") == 0)
		return 9;
	if(strcmp(var, "genres") == 0)
		return 10;
	if(strcmp(var, "actor_1_name")== 0)
		return 11;
	if(strcmp(var, "movie_title") == 0)
		return 12;
	if(strcmp(var, "num_voted_users") == 0)
		return 13;
	if(strcmp(var, "cast_total_facebook_likes") == 0)
		return 14;
	if(strcmp(var, "actor_3_name") == 0)
		return 15;
	if(strcmp(var, "facenumber_in_poster") == 0)
		return 16;
	if(strcmp(var, "plot_keywords") == 0)
		return 17;
	if(strcmp(var, "movie_imdb_link") == 0)
		return 18;
	if(strcmp(var, "num_user_for_reviews") == 0)
                return 19;
        if(strcmp(var, "language") == 0)
                return 20;
        if(strcmp(var, "country") == 0)
                return 21;
        if(strcmp(var, "content_rating") == 0)
                return 22;
        if(strcmp(var, "budget") == 0)
                return 23;
        if(strcmp(var, "title_year") == 0)
                return 24;
        if(strcmp(var, "actor_2_facebook_likes") == 0)
                return 25;
	if(strcmp(var, "imdb_score") == 0)
                return 26;
        if(strcmp(var, "aspect_ratio") == 0)
                return 27;
	if(strcmp(var, "movie_facebook_likes") == 0)
                return 28;
	else
	{
		return 30;
	}

}



void printArr(movie **array, int size)
{
	int i;
	for(i=0; i<size; i++)
	{
		printf("| %s |", array[i]->director_name); 
	}
	printf("\n");
}


void merge(movie **array, int l, int m, int r, char *word)
{
//p(l), q(m), r(r)



	int i,j,k;
	char *keyWord = word;
	int m1 = m-l+1, m2 = r-m;


	movie **left =    malloc(sizeof(movie)*m1);
	movie **right =   malloc(sizeof(movie)*m2);

	int key = getKey(keyWord);

	for(i=0; i<m1; i++)
	{
		left[i] = array[l+i];
	}

	//printf("Left Array: ");
	//printArr(left,m1);

	for(j=0; j<m2;j++)
	{
		//printf("q: %d......j: %d.......m2: %d \n", q,j,m2);
		/*if(j > 0){
			if(array[m+j+1] != right[j-1]){
				right[j] = array[m+j+1];
			}
		}else*/
				right[j] = array[m+j+1];

	}
	//printf("Right Array: ");
	//printArr(right,m2);
	
	i=0;
	j=0;
	k=l;

//printf("%d %d %d\n", i,j,k); 





	//mergeString
	if(key == 1 || key == 2 || key == 7 || key == 10 || key == 11
	   || key == 12 || key == 15 || key == 17 || key == 18 || key == 20 || 
		 key == 21 || key == 22)
	{
		//mergeString(left, right, key, i,j,k, m1,m2);
		char *temp1;
		char *temp2;
		


		while(i<m1 && j<m2)
		{

			temp1 =  *getString(left,i,key);
			temp2 =  *getString(right,j,key);
		
			if(temp1[0] == '"') temp1 = temp1+1;
					
			if(temp2[0] == '"') temp2 = temp2 +1;

	
//printf("temp1-----> %s      temp2-----> %s\n", temp1,temp2);
			if(strcmp(temp1, temp2) <= 0 )
			{
				array[k] = left[i];
				i++;
			}
			else
			{
				array[k] = right[j];
				j++;
			}
			k++;
		}  	
		while(i<m1)
		{
			array[k] = left[i];
			i++;
			k++;
		}	
		while(j<m2)
		{
			array[k] = right[j];
			j++;
			k++;
		}	
		//printf("\n");
		//free(tokenA);
		//free(tokenB);
	}


//printf("Going into Int sorter\n");
	//mergeInt
	if(key == 3 || key == 4 || key == 5 || key == 6 || key == 8 
			|| key == 9 || key == 13 || key == 14 || key == 16 || key == 19 ||
		      key == 23 || key == 24 || key == 25 || key == 28 )
	{

		
		//mergeString(left,right,key,i,j,k,m1,m2);
		long temp1;// = malloc(20*sizeof(char));
               	long temp2;// = malloc(20*sizeof(char));
                

		while(i<m1 && j<m2)
                {

                        temp1 = *getInt(left,i, key);
                        temp2 = *getInt(right, j, key);

//printf("temp1-----> %ld     temp2-----> %ld\n",temp1 , temp2);


		/*	if(temp1[0] == '"') temp1 = temp1+1;
			if(temp2[0] == '"') temp2 = temp2+1;    */
                        if(temp1 <= temp2)
                        {	
                               array[k] = left[i];
                               i++;
                        }
                        else
                        {
                               array[k] = right[j];
                                j++;
                        }
/*printf("temp1-----> %ld     temp2-----> %ld\n",temp1 , temp2);
			printf("Left ");
			printArr(left, m1);
			printf("Right");
			printArr(right,m2);
			printf("\n");*/
                        k++;
                }       



                while(i<m1)
                {

                        array[k] = left[i];
                        i++;
                        k++;
                }


                while(j<m2)
                {
			array[k] = right[j];
                        j++;
                        k++;
                }
                 
             //   free(temp1);
             //   free(temp2);

	}




	//mergeFloat		
	if(key == 26 || key == 27)
	{

//printf("Sorting Float. Keyword----> %s.\n", keyWord);
		//mergeFloat(array,left,right,key,i,j,k,m1,m2);
		float temp1;// = malloc(20*sizeof(char));
                float temp2;// = malloc(20*sizeof(char));
                while(i<m1 && j<m2)
                {
                        temp1 = *getFloat(left,i,key);
                        temp2 = *getFloat(right,j,key);
                        if(temp1 <= temp2)
                        {
                               array[k] = left[i];
                                i++;
                        }
                        else
                        {
			        array[k] = right[j];
                                j++;
                        }
                        k++;
                }

                while(i<m1)
                {
                        array[k] = left[i];
                        i++;
                        k++;
                }
                while(j<m2)
                {

			array[k] = right[j];
                        j++;
                        k++;
                }

              //  free(temp1);
              //  free(temp2);

	}
	

free(left);
free(right);
}
