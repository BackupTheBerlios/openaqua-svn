/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/07|16:46:42,89}|(REF)
\class    EB_Header

\brief    


\date     $Date: 2006/04/13 16:42:01,07 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EB_Header"

#include  <fileacc.h>
#include  <popa7.h>
#include  <iNetConversion.h>
#include  <seb_DataArea.hpp>
#include  <sEB_Header.hpp>


/******************************************************************************/
/**
\brief  EB_Header - 



\param  len - 
\param  netopt - Multi-user access
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EB_Header"

                        EB_Header :: EB_Header (uint16 len, logical netopt )
                     : EB_extRBHeader(len),
RessourceLock (YES),
bsts(), 
  file_handle(0),
  net_opt(netopt)
{

  memcpy(eb_ident,"EB  ",4);

}

/******************************************************************************/
/**
\brief  Lock - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical EB_Header :: Lock ( )
{
  logical     term = NO;
BEGINSEQ
  if ( stsclck() )                                   ERROR
  switch ( net_opt )
  {
    case NO  : break;
    case 2   : ILock();  // shared rootbase
               break;
    case YES :
#ifndef __unix__
               if ( file_handle && net_opt ) 
               { 
                 if ( lseek(file_handle,0,SEEK_SET) == -1L ) 
                                                     SDBERR(99)
                 if ( _locking(file_handle,_LK_LOCK,get_header_length()) )   
                                                     ERROR
               }
#endif
               break;
  }
  stsslck();
  if ( Read() )                                      ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LockInternal - 


\return term - Termination code

\param  position64 - 
\param  length - 
\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockInternal"

logical EB_Header :: LockInternal (uint64 position64, int32 length, logical wait )
{
  logical     term = NO;
  int         lockret;
BEGINSEQ
#ifndef __unix__
  if ( file_handle && net_opt) 
  { 
#ifdef WIN32
    if ( _lseeki64(file_handle,position64,SEEK_SET) == -1L) 
#else    
    if ( lseek(file_handle,position64,SEEK_SET) == -1L) 
#endif
    {
      if ( position64 != 0x7f00000000000001 )
        SDBERR(99)
      else
        ERROR  
    }
    if ( (lockret = _locking(file_handle,wait ? _LK_LOCK : _LK_NBLCK,length)) == -1 )        
      switch ( errno )
      {
        case  EACCES    : ERROR
        case  EBADF     : SDBERR(902)
        case  EDEADLOCK : ERROR
        case  EINVAL    : SDBERR(903)
        default         : ERROR
      }
  }
#endif

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Read - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

logical EB_Header :: Read ( )
{
  uint16   modcount   = get_mod_count();
  logical  term       = NO;
BEGINSEQ
  if ( !file_handle )                                 ERROR
  
  if ( lseek(file_handle,6,SEEK_SET) < 0 )            SDBERR(99)
  if ( eb_DataArea::ReadCheck(file_handle,2,&modcount) )
                                                     SDBERR(29)
  if ( get_mod_count() == PIFToShort(modcount,platform_indep) )
                                                     LEAVESEQ

  if ( lseek(file_handle,2,SEEK_SET) < 0 )            SDBERR(99)
  if ( eb_DataArea::ReadCheck(file_handle,get_header_length()-2,eb_ident) )
                                                     SDBERR(29)
  if ( memcmp(eb_ident,"EB",2) )                     SDBERR(29)

//  FromPIF();
  ConvertTo3();             // upgrade6, dann wieder FromPIF
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Reset - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical EB_Header :: Reset ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  Unlock - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical EB_Header :: Unlock ( )
{
 logical     term = NO;
BEGINSEQ
  switch ( net_opt )
  {
    case NO  : break;
    case 2   : IUnlock();  // shared rootbase
               break;
    case YES :
#ifndef __unix__
               if ( net_opt )
               { 
                 Write();
                 if ( file_handle && stsclck() ) 
                 { 
                   if ( lseek(file_handle,0,SEEK_SET) == -1L )
                                                     SDBERR(99)
                   if ( _locking(file_handle,_LK_UNLCK,get_header_length()) )
                                                     ERROR
                 }
               }
#endif
               break;
  }
  stsrlck();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  UnlockInternal - 


\return term - Termination code

\param  position64 - 
\param  length - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockInternal"

logical EB_Header :: UnlockInternal (uint64 position64, int32 length )
{
  logical     term = NO;
BEGINSEQ
#ifndef __unix__
  if ( file_handle && net_opt ) 
  { 
#ifdef WIN32
    if ( _lseeki64(file_handle,position64,SEEK_SET) == -1L) SDBERR(99)
#else    
    if ( lseek(file_handle,position64,SEEK_SET) == -1L) SDBERR(99)
#endif
    
    if ( _locking(file_handle,_LK_UNLCK,length) )     ERROR
  }
#endif

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Write - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Write"

logical EB_Header :: Write ( )
{
  int      len  = get_header_length();
  logical  term = NO;
BEGINSEQ
  if ( stscmod() && file_handle )
  {
    set_mod_count(get_mod_count()+1);
    
    ToPIF();
    if ( lseek(file_handle,0,SEEK_SET) < 0 )          SDBERR(99)
    if ( write(file_handle,eb_ident-2,len) != len )   SDBERR(34)
    FromPIF();
  }
RECOVER
  FromPIF();
  term = YES;
ENDSEQ
  stsrmod();
  return(term);
}


