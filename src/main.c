#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// setting up global scope

#define BUF_SIZE 3    // size of shared buffer

int buffer[BUF_SIZE]; // shared buffer
int add = 0;          // place to add next elem
int rem = 0;          // place to remove next elem
int num = 0;          // number elems in buffer

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER; // mutex lock for buffer
pthread_cond_t c_cons = PTHREAD_COND_INITIALIZER; // consumer waits on cv
pthread_cond_t c_prod = PTHREAD_COND_INITIALIZER; // producer waits on cv

void *producer (void *param);
void *consumer (void *param);

// main portion of code

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

void *producer (void *param) {
  int i;
  for (i = 1; 1 < 20; i++) {
    pthread_mutex_lock(&m);
      if (num > BUF_SIZE) { // buffer overflow
        exit(1);
      }
      while (num == BUF_SIZE) {
        pthread_cond_wait(&c_prod, &m);
      }
      buffer[add] = i; // buffer not full, add element
      add = (add+1) % BUF_SIZE;
      num++;
    pthread_mutex_unlock(&m);

    pthread_cond_signal(&c_cons); // inserted only 1 element
    printf("producer: inserted %d\n", i); fflush(stdout);
  }

  printf("producer quitting\n"); fflush(stdout);
  return 0;
}

void *consumer (void *param) {
  int i;
  while(1) {
    pthread_mutex_lock(&m);
      if(num < 0) { // underflow
        exit(1);
      }
      while(num == 0) {
        pthread_cond_wait(&c_cons, &m);
      }
      i = buffer[rem]; // buffer not empty, remove elem
      rem = (rem + 1) % BUF_SIZE; // buffer wraps
      num--;
    pthread_mutex_unlock(&m);

    // use signal OUTSIDE of locked code to avoid
    // spurious wakeups
    pthread_cond_signal(&c_prod); // we only consumed 1
    printf("Consumer value %d\n", i); fflush(stdout);
  }
}
