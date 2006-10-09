#include <time.h>
#include <errno.h>
#include <stdio.h>

#ifdef __unix__
#include <unistd.h>
#include <dirent.h>
#include <pthread.h>
#define _MAX_FNAME 256
#else
#include <io.h>
#include <dos.h>
#include <direct.h>
#include <share.h>
#include <process.h> 
#include <sys/locking.h>
#endif

#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h> 

