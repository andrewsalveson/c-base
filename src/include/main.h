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


