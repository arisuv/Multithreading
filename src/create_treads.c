
// This porgram will create three threads. Each thread will start in a separate function
// Also, the program will print the cpu number of each thread and finally the total number of used cpus 



#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>

#define MAX_NUM_THREADS 3 

static void set_thread_affinity(pthread_t t, int cpu)
{
      cpu_set_t cpuset;

      CPU_ZERO(&cpuset);
      CPU_SET(cpu, &cpuset);
      pthread_setaffinity_np(t, sizeof(cpu_set_t), &cpuset);
}

static void print_thread_affinity(pthread_t t, int ID)
{
      cpu_set_t cpuset;
      int i;

      pthread_getaffinity_np(t, sizeof(cpu_set_t), &cpuset);

      for (i = 0; i < CPU_SETSIZE; i++) {
            if (CPU_ISSET(i, &cpuset))
                  printf("Thread %2d bound to CPU %d\n", ID, i);
      }
}

static void *thread_func(void *args)
{
      int ID = *(int *)args;

      print_thread_affinity(pthread_self(), ID);

      return NULL;
}

int main(void)
{
      int num_threads, num_cpus;
      int IDs[MAX_NUM_THREADS], i;
      pthread_t threads[MAX_NUM_THREADS];
      cpu_set_t cpuset;

      int sched_getcpu();

      num_threads = 3;
      printf("Creating %d threads \n", num_threads);


      IDs[0] = 0;
      pthread_getaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
      num_cpus = sched_getcpu();
      printf("Number of CPUs: %d\n", sched_getcpu());

      set_thread_affinity(pthread_self(), 0);

      for (i = 1; i < num_threads; i++) {
            IDs[i] = i;
            pthread_create(&threads[i], NULL, thread_func, &IDs[i]);
            set_thread_affinity(threads[i], i % num_cpus);
            sleep(2);
      }

      thread_func(&IDs[0]);

      for (i = 1; i < num_threads; i++) {
            pthread_join(threads[i], NULL);
      }

      return 0;
}