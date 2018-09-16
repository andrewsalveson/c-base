#ifndef _MAIN_H_
#define _MAIN_H_

#include <pthread.h>

#define BUF_SIZE 3    // size of shared buffer

int buffer[BUF_SIZE]; // shared buffer
int add; // place to add next elem
int rem; // place to remove next elem
int num; // number elems in buffer

pthread_mutex_t m; // mutex lock for buffer
pthread_cond_t c_cons; // consumer waits on cv
pthread_cond_t c_prod; // producer waits on cv

#endif
