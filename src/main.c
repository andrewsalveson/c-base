#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <main.h>
#include <producer.h>
#include <consumer.h>

int buffer[BUF_SIZE]; // size of shared buffer
int add = 0; // place to add next elem
int rem = 0; // place to remove next elem
int num = 0; // number elems in buffer

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER; // mutex lock for buffer
pthread_cond_t c_cons = PTHREAD_COND_INITIALIZER; // consumer waits on cv
pthread_cond_t c_prod = PTHREAD_COND_INITIALIZER; // producer waits on cv

int main(int argc, char *argv[]) {
  pthread_t tid1, tid2; // thread identifiers
  int i;
  if (pthread_create(&tid1, NULL, producer, NULL) != 0) {
    fprintf(stderr, "Unable to create producer thread\n");
    exit (1);
  }
  if (pthread_create(&tid2, NULL, consumer, NULL) != 0) {
    fprintf(stderr, "Unable to create consumer thread\n");
    exit (1);
  }
  pthread_join(tid1, NULL); // wait for producer to exit
  pthread_join(tid2, NULL); // wait for consumer to exit
  printf("Parent quitting\n");
}
