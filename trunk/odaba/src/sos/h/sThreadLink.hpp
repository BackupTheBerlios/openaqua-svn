/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    ThreadLink

\brief    


\date     $Date: 2006/03/12 19:20:19,95 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ThreadLink_HPP
#define   ThreadLink_HPP

class     ThreadLink;

class     vcls;
#include  <sEvent.hpp>
#include  <sThreadLink.hpp>
#include  <sflnk.hpp>
#pragma pack(8)

class  ThreadLink :public flnk
{
protected  :         Event                                        started ATTR_ALIGN(4);                                     
protected  :         Event                                        terminated;                                                
protected  :         ProcessInfo                                 *parent_info;                                               
protected  :         logical                                      wait;                                                      

public     :
                     Event                                       &get_started() { return(started); }
                     Event                                       &get_terminated() { return(terminated); }
                     ProcessInfo                                 *get_parent_info() { return(parent_info); }
                     logical                                      get_wait() { return(wait); }
public     :                                     void Start ( );
public     :                                     void Terminate ( );
public     :         SOS7ImpExp                  thread_t ThreadCall (logical wait_for_termination=NO );
public     :         SOS7ImpExp                                          ThreadLink (vcls *vclsptr, FCTP funcptr );
public     :         SOS7ImpExp                                          ThreadLink (vcls *vclsptr, ACTP actptri );
public     :         SOS7ImpExp                                          ThreadLink (ThreadLink &threadlnk_ref );
public     :         SOS7ImpExp                                          ThreadLink ( );
public     :         SOS7ImpExp                                          ~ThreadLink ( );
};

#pragma pack()
#endif
