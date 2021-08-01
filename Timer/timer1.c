#include <pthread.h>
#include <sys/signal.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <semaphore.h>

#define MILLION 1000000

void err_abort(int status, char* message)
{
  fprintf(stderr, "%s\n", message);
  exit(status);
}

void errno_abort(char* message)
{
  perror(message);
  exit(EXIT_FAILURE);
}

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int counter = 0;

/*
 * Thread start routine to notify the application when the
 * timer expires. This routine is run "as if" it were a new
 * thread, each time the timer expires.
 *
 * When the timer has expired 5 times, the main thread will
 * be awakened, and will terminate the program.
 */
void timer_thread(union sigval arg)
{
  int status;

  status = pthread_mutex_lock(&mutex);
  if (status != 0)
    err_abort(status, "Lock mutex");

  if (++counter >= 5) {
    status = pthread_cond_signal(&cond);
    if (status != 0)
      err_abort(status, "Signal condition");
  }

  status = pthread_mutex_unlock(&mutex);
  if (status != 0)
    err_abort(status, "Unlock mutex");

  printf("Timer %d\n", counter);
}

void create_timer(unsigned i)
{
  timer_t timer_id;
  int status;
  struct itimerspec ts;
  struct sigevent se;
  long long nanosecs = MILLION * 100 * i * i;

  /*
   * Set the sigevent structure to cause the signal to be
   * delivered by creating a new thread.
   */
  se.sigev_notify = SIGEV_THREAD;
  se.sigev_value.sival_ptr = &timer_id;
  se.sigev_notify_function = timer_thread;
  se.sigev_notify_attributes = NULL;

  ts.it_value.tv_sec = nanosecs / 1000000000;
  ts.it_value.tv_nsec = nanosecs % 1000000000;
  ts.it_interval.tv_sec = 0;
  ts.it_interval.tv_nsec = 0;

  status = timer_create(CLOCK_REALTIME, &se, &timer_id);
  if (status == -1)
    errno_abort("Create timer");

  // TODO maybe we'll need to have an array of itimerspec
  status = timer_settime(timer_id, 0, &ts, 0);
  if (status == -1)
    errno_abort("Set timer");
}

int main()
{
  int status;
  unsigned i = 1;

  for (; i < 6; i++)
    create_timer(i);

  status = pthread_mutex_lock(&mutex);
  if (status != 0)
    err_abort(status, "Lock mutex");

  while (counter < 5) {
    printf("\tBlocked!\n");
    status = pthread_cond_wait(&cond, &mutex);
    if (status != 0)
      err_abort(status, "Wait on condition");
    printf("\tUnblocked!\n");
  }
  status = pthread_mutex_unlock(&mutex);
  if (status != 0)
    err_abort(status, "Unlock mutex");

  return 0;
}
