#ifndef _SORTER_H_
#define _SORTER_H_
#include <stdio.h>

char *c;

typedef struct movie_
{
	char *color;
	char *director_name;
	long num_critic_reviews;
	long duration;
	long director_facebook_likes;
	long actor_3_facebook_likes;
	char *actor_2_name;
	long actor_1_facebook_likes;
	long gross;
	char *genres;
	char *actor_1_name;
	char *movie_title;
	long num_voted_users;
	long cast_total_facebook_likes;
	char *actor_3_name;
	long facenumber_in_poster;
	char *plot_keywords;
	char *movie_imdb_link;
	long num_user_for_reviews;
	char *language;
	char *country;
	char *content_rating;
	long budget;
	long title_year;
	long actor_2_facebook_likes;
	float imdb_score;	//when printing %3.1f
	float aspect_ratio;	//when printing %4.2f
	long movie_facebook_likes;
	struct movie_* next;
}movie;

typedef struct fileParams_
{
	char* fileName;
	FILE* fp;
	char* d;
}fileParams;

char** getString(movie** info,int entry,int element);
long* getInt(movie** info,int entry,int element);
float* getFloat(movie** info,int entry,int element);
void insert(char* line);
void merge(movie **array, int p, int q, int r, char * word);
int getKey(char *word);
void mergesort(movie **array, int a, int b, char *word);
void print(movie **info, int numOfEntries, char* fileName, char* path);
void* traverse(void* d);

#endif
/*****
*
*	Define structures and function prototypes for your sorter
*
*
*
******/

//Suggestion: define a struct that mirrors a record (row) of the data set


//Suggestion: prototype a mergesort function
