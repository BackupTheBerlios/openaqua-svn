#ifndef __afxunix__
#define __afxunix__
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
//#include <pthread.h>

struct  __POSITION {};
typedef __POSITION *POSITION;

#define SOSTRY                                                    \
  jmp_buf *jb = (jmp_buf *)GetProcessVariable(PVN_SOSLONG_JUMP);  \
  if ( !setjmp(*jb) )

#define SOSCATCH                                                  \
  else
  
#endif

