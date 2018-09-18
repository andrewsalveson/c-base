#ifndef _CONSUMER_H_
#define _CONSUMER_H_

#include <stdio.h>
#include <stdlib.h>
#include <main.h>
#include <pthread.h>

extern int buffer[]; // shared buffer
extern int results[];// local storage
extern int add;      // place to add next elem
extern int rem;      // place to remove next elem
extern int num;      // number elems in buffer

extern pthread_mutex_t m; // mutex lock for buffer
extern pthread_cond_t c_cons; // consumer waits on cv
extern pthread_cond_t c_prod; // producer waits on cv

void *consumer (void *param);

#endif
