#ifndef CRessourceLock_H
#define CRessourceLock_H
#ifdef __unix__
thread_t       nullthread;
pthread_once_t nullthread_control = PTHREAD_ONCE_INIT;
void*          nullthr_func (void*){return NULL;}

void nullthread_create()
{
  pthread_attr_t attr;
  pthread_attr_init (&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  pthread_create(&nullthread, &attr, nullthr_func, NULL);
};
#endif
#endif
