/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    flnk

\brief    Function link
          The  class defines dynamic function links to any class that is derived
          from  the virtual base class vcls.  This allows calling functions from
          classes that are known at run-time, only. 
          "

\date     $Date: 2006/06/03 13:05:33,35 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "flnk"

#include  <pdefault.h>
#include  <cactp.h>
#include  <cfctp.h>
#include  <fileacc.h>
#include  <iThreadCall.h>
#include  <sUCA_Action.hpp>
#include  <svcls.hpp>
#include  <sflnk.hpp>


/******************************************************************************/
/**
\brief  ActionCall - 


\return term - Success
-------------------------------------------------------------------------------
\brief  FLNKCALA - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActionCall"

logical flnk :: ActionCall ( )
{

  return ( flnkinst ? (flnkinst->*((ACTP)flnkfct))() : YES );


}

/******************************************************************************/
/**
\brief  FLNKCALAI - 


\param  objptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActionCall"

logical flnk :: ActionCall (void *objptr )
{

  return ( objptr ? (((vcls *)objptr)->*((ACTP)flnkfct))() : YES );

}

/******************************************************************************/
/**
\brief  Call - 


\return retval - 
-------------------------------------------------------------------------------
\brief  FLNKCALL - 


\param  parm - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Call"

int32 flnk :: Call (void *parm )
{

  return(flnkinst ? (flnkinst->*flnkfct)(parm) : UNDEF);


}

/******************************************************************************/
/**
\brief  FLNKCALLI - 


\param  objptr - 
\param  parm - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Call"

int32 flnk :: Call (void *objptr, void *parm )
{

  return ( objptr ? (((vcls *)objptr)->*flnkfct)(parm) : UNDEF);

}

/******************************************************************************/
/**
\brief  IsSet - 


\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSet"

logical flnk :: IsSet ( ) const
{

  return ( flnkinst && flnkfct ? YES : NO );


}

/******************************************************************************/
/**
\brief  SetInstance - 



\param  vclsptr - Virtual class pointer
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInstance"

void flnk :: SetInstance (vcls *vclsptr )
{

  flnkinst = vclsptr;


}

/******************************************************************************/
/**
\brief  ThreadCall - Call action function in a separate thread
        The  function  calls  an  action  function  in  a  separate  thread. The
        function can be called for action links (ALINK), only.

\return thread_id - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ThreadCall"

thread_t flnk :: ThreadCall ( )
{
thread_t thread_id;
BEGINSEQ
  if ( !flnkinst )                                   SOSERR(99)
#ifdef __unix__
  pthread_attr_t attr;
  pthread_attr_init (&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  switch ( pthread_create(&thread_id, &attr, ExecuteThread, this) )
  {
    case 0      : pthread_attr_destroy(&attr);
                  break;
    case EAGAIN : pthread_attr_destroy(&attr);
                  SOSERR(900+EAGAIN)
    default     : pthread_attr_destroy(&attr);
                  SOSERR(99);
  }
#else
  if ( (thread_id = _beginthread(ExecuteThread,8000,this)) == -1)
    switch ( errno )
    {
      case  EAGAIN : ERROR 
      default      : SOSERR(99);
    }
#endif
RECOVER
  SOSERR(99); //daGnuwwel:hier muss noch was anderes hin...
ENDSEQ
  return(thread_id);

}

/******************************************************************************/
/**
\brief  ThreadCallS - 


\return thread_id - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ThreadCallS"

thread_t flnk :: ThreadCallS ( )
{
thread_t thread_id;
BEGINSEQ
  if ( !flnkinst )                                   SOSERR(99)
#ifdef __unix__
  pthread_attr_t attr;
  pthread_attr_init (&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  switch ( pthread_create(&thread_id, &attr, ExecuteThread, this) )
  {
    case 0      : pthread_attr_destroy(&attr);
                  break;
    case EAGAIN : pthread_attr_destroy(&attr);
                  SOSERR(900+EAGAIN)
    default     : pthread_attr_destroy(&attr);
                  SOSERR(99);
  }
#else
  if ( (thread_id = _beginthread(ExecuteThreadS,8000,this)) == -1)
    switch ( errno )
    {
      case  EAGAIN : ERROR 
      default      : SOSERR(99);
    }
#endif
RECOVER
  SOSERR(99); //daGnuwwel:hier muss noch was anderes hin...
ENDSEQ
  return(thread_id);

}

/******************************************************************************/
/**
\brief  VoidCall - 


\return retval - 

\param  parm - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "VoidCall"

int32 flnk :: VoidCall (void *parm )
{

  if ( !flnkfct )
    return(0);

#if defined (WIN32) || defined (__unix__)
  return ( (vcls().*flnkfct)(parm) );
#else  
  return ( (vcls()->*flnkfct)(parm) );
#endif  


}

/******************************************************************************/
/**
\brief  flnk - 


-------------------------------------------------------------------------------
\brief  FLNK_ - 


\param  vclsptr - Virtual class pointer
\param  funcptr - Function pointer
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "flnk"

     flnk :: flnk (vcls *vclsptr, FCTP funcptr )
                     : flnkinst(vclsptr),
  flnkfct(funcptr)
{



}

/******************************************************************************/
/**
\brief  FLNK_A - 


\param  vclsptr - Virtual class pointer
\param  actptri - Action pointer
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "flnk"

     flnk :: flnk (vcls *vclsptr, ACTP actptri )
                     : flnkinst(vclsptr),
  flnkfct((FCTP)actptri)
{



}

/******************************************************************************/
/**
\brief  FLNK_C - 


\param  flnk_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "flnk"

     flnk :: flnk (const flnk &flnk_ref )
                     : flnkinst(flnk_ref.flnkinst),
  flnkfct(flnk_ref.flnkfct)
{



}

/******************************************************************************/
/**
\brief  FLNK_DUM - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "flnk"

     flnk :: flnk ( )
                     : flnkinst(NULL),
   flnkfct((FCTP)NULL)
{



}

/******************************************************************************/
/**
\brief  operator! - 


\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator!"

logical flnk :: operator! ( ) const
{

  return ( !flnkinst || !flnkfct ? YES : NO );

}

/******************************************************************************/
/**
\brief  operator!= - Compare function links
        Two  function links  are considered  as equal  when the instance and the
        function pointer are the same.

\return cond - Return value

\param  flnk_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator!="

logical flnk :: operator!= (const flnk &flnk_ref ) const
{
  logical                 cond;
  return ( (flnkinst != flnk_ref.flnkinst) ||
           (flnkfct  != flnk_ref.flnkfct )    ? YES : NO );

  return(cond);
}

/******************************************************************************/
/**
\brief  operator= - Assignment operator
        The  operator  allows  copying  instance  and  function pointer from the
        right function link to the left one.

\return flnk_ref - 

\param  flnk_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

flnk &flnk :: operator= (const flnk &flnk_ref )
{

  flnkinst = flnk_ref.flnkinst;
  flnkfct  = flnk_ref.flnkfct;

  return(*this);
}

/******************************************************************************/
/**
\brief  operator== - Compare function links
        Two  function links  are considered  as equal  when the instance and the
        function pointer are the same.

\return term - Success

\param  flnk_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical flnk :: operator== (const flnk &flnk_ref ) const
{

  return ( (flnkinst == flnk_ref.flnkinst) &&
           (flnkfct  == flnk_ref.flnkfct )    ? YES : NO );


}


