#include <consumer.h>
#include <unistd.h>

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

    for(int r = 0; r < rand(); r++){
      usleep(1);
    }

    // use signal OUTSIDE of locked code to avoid
    // spurious wakeups
    pthread_cond_signal(&c_prod); // we only consumed 1
    results[i] = 1;
    for(int j = 0; j < NUM_JOBS; j++){
      printf("%d ", results[j]);
    }
    printf("\n");
    //printf("Consumer value %d\n", i); fflush(stdout);
  }
}
