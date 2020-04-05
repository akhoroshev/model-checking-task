#include <assert.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdlib.h>

/*
 * Test-And-Set spinlock
 */
typedef atomic_flag spinlock_t;

void spinlock_lock(spinlock_t *spinlock) {
  while (atomic_flag_test_and_set_explicit(spinlock, memory_order_acquire)) {
  }
}

void spinlock_unlock(spinlock_t *spinlock) {
  atomic_flag_clear_explicit(spinlock, memory_order_release);
}

spinlock_t spinlock = ATOMIC_FLAG_INIT;
int s_data_1;
int s_data_2;

void *thread_1(void *unused) {
  spinlock_lock(&spinlock);
  s_data_1 = 1;
  s_data_2 = -1;
  spinlock_unlock(&spinlock);
  return NULL;
}

void *thread_2(void *unused) {
  spinlock_lock(&spinlock);
  assert(s_data_2 + s_data_1 == 0);
  spinlock_unlock(&spinlock);
  return NULL;
}

int main() {
  pthread_t t1, t2;

  if (pthread_create(&t1, NULL, thread_1, NULL))
    abort();
  if (pthread_create(&t2, NULL, thread_2, NULL))
    abort();

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  return 0;
}