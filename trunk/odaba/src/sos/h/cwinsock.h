//******************************************************************/
//* winsock
//*
//*               ODABA II - Class Declaration
//*                          from  L:/SOS6/sos4.dev
//*
//*  ODE Version 2.1                                   08.03.00
//******************************************************************/
#ifndef   winsock_H
#define   winsock_H
#ifdef __unix__
#define closesocket close
#define ioctlsocket ioctl
#define SOCKET int
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define LPSOCKADDR sockaddr*
#include <errno.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#ifdef __sun__
#include <sys/filio.h>
#define INADDR_NONE -1
#else
#include <filio.h>
#endif

#else
#include "winsock.h"
#endif

#endif

