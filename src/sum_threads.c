 /*

This program will read array of 1000 element from external file "input.txt" 
Then split the array into 4 portions and give each 
portion to one thread. So, each tread will have 250 elements
each tread will sum its elements.
Then add up their sums to get the final total sum of all 1000 elements

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 1000
#define MAX_THREAD 4


int array[1000];
int sum[4] = { 0 };
int arraypart = 0;

void* sum_array(void* arg)
{
      int thread_part = arraypart++;
  
    for (int i = thread_part * (MAX / 4); i < (thread_part + 1) * (MAX / 4); i++)
    {
        sum[thread_part] += array[i];
    }
}

void testSum()
{
   pthread_t threads[MAX_THREAD];

    for (int i = 0; i < MAX_THREAD; i++)
    {
        pthread_create(&threads[i], NULL, sum_array, (void*)NULL);
    }
  
    // joining threads
    for (int i = 0; i < MAX_THREAD; i++)
    {
        pthread_join(threads[i], NULL);
    }
  
      // print each thread
    for (int i = 0; i < MAX_THREAD; i++)
    {
        printf("Thread %d Sum is : %d \n",i, sum[i]);
    }

    // adding the 4 parts
    int total_sum = 0;
    for (int i = 0; i < MAX_THREAD; i++)
    {
        total_sum += sum[i];
    }
       printf("\nTotal Sum is : %d \n",total_sum);   

}


void readfile(char* file_name)
{

   char ch;
   
   FILE *fp;
    
    
   fp = fopen(file_name,"r"); // read mode
 
   if( fp == NULL )
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
   
 
    char line [5]; /* line size */ 

    int i=0;
 
    printf("Reading file: ");    
    fputs(file_name,stdout);
    printf("\n");

    
    while ( fgets ( line, sizeof line, fp) != NULL ) /* read a line */
    {
       if (i < 1000)
       {
         array[i]=atoi(line);  
       }

      i++;
    }

 
   fclose(fp);

    printf("Reading file Complete, integers stored in array.\n\n");    

}

 
int main(int argc, char* argv[])
{
   
   if (argc != 2) {
	fprintf(stderr,"usage: a.out <file name>\n");
	/*exit(1);*/
	return -1;
    }

   readfile(argv[1]);


   //Debug code for testing only
   testSum();

   return 0;
}
