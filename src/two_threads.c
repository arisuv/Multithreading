/*

This program will create two threads that read this array.
-The 1st thread will compute the sum of the array elements.
-The 2nd Thread will compute the Product of the array elements.


*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX 40
 
int array[] = {1,2,2,1,1,2,2,1,1,1,2,2,1,2,1,1,1,2,2,2,2,1,1,2,1,1,1,2,2,1,1,1,2,1,1,1,1,2,1,1};
int sum;
int product = 1;


void* sum_array(void* arg)
{  
    for (int i = 0; i < MAX; i++)
    {
        sum += array[i];
    }
}

void* product_array(void *args)
{  
    for (int i = 0; i < MAX; i++)
    {
    product=product*array[i];    }
}

void main()
{
    pthread_t t1_id;
    pthread_t t2_id;

    pthread_create(&t1_id, NULL, sum_array, (void *) NULL);
    pthread_create(&t2_id, NULL, product_array, (void *) NULL);
    
    pthread_join(t1_id,NULL);
    pthread_join(t2_id,NULL);

    printf("Array Sum is : %d \n", sum);
    printf("Array Product is : %d  \n", product);   

}