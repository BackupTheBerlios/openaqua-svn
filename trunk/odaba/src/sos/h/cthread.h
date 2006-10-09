#ifndef CTHREAD_H
#define CTHREAD_H

#ifdef __unix__

#include <sys/time.h>
#include <errno.h>

#include <signal.h>
#include <setjmp.h>

#define thread_t pthread_t
#define thrdfnctype void *
#define INFINITE -1
#define WAIT_OBJECT_0 0
#define WAIT_TIMEOUT  1

#include <pthread.h>
struct CRITICAL_SECTION
{
  pthread_mutex_t mutex;
  pthread_t       locker_id;
  int             lockcount;
};
typedef struct HANDLE
{
  pthread_cond_t  condition;
  pthread_mutex_t mutex;
  logical         set;
};

extern thread_t       nullthread;
extern pthread_once_t nullthread_control;

#else /* __unix__ */

typedef unsigned long thread_t;
#define thrdfnctype void __cdecl

#endif /* __unix__ */

#endif /*! CTHREAD_H */
