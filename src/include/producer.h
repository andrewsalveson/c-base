#ifndef _PRODUCER_H_
#define _PRODUCER_H_

#include <pthread.h>
#include <stdlib.h> // required for exit
#include <stdio.h>
#include <main.h>
#include <consumer.h>

extern int buffer[]; // shared buffer
extern int add;      // place to add next elem
extern int rem;      // place to remove next elem
extern int num;      // number elems in buffer

extern pthread_mutex_t m; // mutex lock for buffer
extern pthread_cond_t c_cons; // consumer waits on cv
extern pthread_cond_t c_prod; // producer waits on cv

void *producer (void *param);

#endif
