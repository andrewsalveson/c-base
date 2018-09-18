#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <main.h>
#include <producer.h>
#include <consumer.h>

int results[NUM_JOBS]; // storage for job results
int buffer[BUF_SIZE]; // size of shared buffer
int add = 0; // place to add next elem
int rem = 0; // place to remove next elem
int num = 0; // number elems in buffer

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t c_cons = PTHREAD_COND_INITIALIZER;
pthread_cond_t c_prod = PTHREAD_COND_INITIALIZER;

int main(int argc, char *argv[]) {
  // array of thread identifiers
  pthread_t tid[NUM_THREADS];
  int i;
  // first thread is producer
  if (pthread_create(&tid[0], NULL, producer, NULL) != 0) {
    fprintf(stderr, "Unable to create producer thread\n");
    exit (1);
  }
  // the rest are all consumers
  for(int t = 1; t < NUM_THREADS; t++){
    if (pthread_create(&tid[t], NULL, consumer, NULL) != 0) {
      fprintf(stderr, "Unable to create consumer thread\n");
      exit (1);
    }
  }
  // join all threads
  for(int t = 0; t < NUM_THREADS; t++){
    pthread_join(tid[t], NULL);
  }
  printf("Parent quitting\n");

  exit(0);
  return 0;
}
