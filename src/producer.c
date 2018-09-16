#include <producer.h>

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

