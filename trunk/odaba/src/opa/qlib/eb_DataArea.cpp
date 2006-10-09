/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    eb_DataArea

\brief    


\date     $Date: 2006/08/22 11:52:02,84 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "eb_DataArea"

#include  <fileacc.h>
#include  <popa7.h>
#include  <sEBDataArea.hpp>
#include  <sEB_DAHeader.hpp>
#include  <sEB_Header.hpp>
#include  <sInitArea.hpp>
#include  <ssvel.hpp>
#include  <stim.hpp>
#include  <seb_DataArea.hpp>


/******************************************************************************/
/**
\brief  Append - 


\return position64 - 

\param  instlen - 
\param  length - 
\param  area - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Append"

int64 eb_DataArea :: Append (int32 instlen, int32 length, void *area )
{
  logical     extlock = da_header->stsclck();
  int64       position64;
BEGINSEQ
  if ( net_opt && !extlock )
  {
    if ( da_header->Lock() )                         SDBERR(6)
    if ( da_header->Read() )                         ERROR
  }

  if ( instlen > length || instlen < 0 )             SDBERR(99)
    
  position64 = da_header->get_next_position();
  if ( da_header->IncreasePosition(length) )         ERROR
  if ( instlen > 0 )
    if ( Write(position64,instlen,area) )            ERROR
  if ( length > instlen )
    if ( WriteNull(position64+instlen,length-instlen) )
                                                     ERROR

  if ( net_opt && !extlock )
    if ( da_header->Write() )                        ERROR

RECOVER
  position64 = 0;
ENDSEQ
  if ( !extlock )
    da_header->Unlock();
  return(position64);
}

/******************************************************************************/
/**
\brief  Check - 


\return term - Termination code

\param  position64 - 
\param  length - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical eb_DataArea :: Check (uint64 position64, int32 length )
{
  logical     extlock = da_header->stsclck();
  logical     lock = NO;
  logical     term    = NO;
BEGINSEQ
  if ( !position64 )                                 SDBERR(362)
  if ( position64 < (int64)da_header->get_header_length() ) 
                                                      SDBERR(41)
  if ( position64+length > da_header->get_next_position() )
  {  
    if ( !net_opt )                                   SDBERR(41)
    if ( !extlock )
    {
      da_header->Lock();
      lock = YES;
    }
    da_header->Read();
    if ( position64+length > da_header->get_next_position() )
                                                      SDBERR(41)
  }
RECOVER
  term = YES;
ENDSEQ
  if ( lock )
    da_header->Unlock();
  return(term);
}

/******************************************************************************/
/**
\brief  Close - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical eb_DataArea :: Close ( )
{
  logical       term = NO;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
  if ( da_number && da_header )
    da_header->Write();

  if ( da_header && da_header->temp_file )
  {
    fclose(da_header->temp_file);
    da_header->temp_file = NULL;
    file_handle = 0;
  }
  else if ( file_handle > 0 )
  {
    if ( access_opt && da_header )
      if ( _lseeki64(file_handle,da_header->get_next_position(),SEEK_SET) < 0 )          
                                                       SDBERR(4)
// wenn das unter unix ggf.zum abschneiden fuehrt, muss max von folelength und lseek genommen werden
    close(file_handle);
    file_handle = 0;
  }
  
  if ( da_number > 0 )
    delete da_header;
  da_header = NULL;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Exist - Database Area


\return cond - 

\param  path - 
\param  netopt - Multi-user access
\param  chkopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Exist"

logical __cdecl eb_DataArea :: Exist (char *path, logical netopt, char chkopt )
{
  char     cpath[513];
  svel    *svelptr = NULL;
  char     ident[6];
  int      filehandle = 0;
  int      flags      = O_RDONLY;
  logical  cond       = YES;
BEGINSEQ
#ifndef __unix__  
  flags |= O_BINARY;
#endif

  strcpy(cpath,path);
  ReplaceSysVariable(cpath,sizeof(cpath)-1);
    
  if ( !IsFile(cpath) )                               ERROR

  if ( netopt )
  {
#ifdef __unix__  
    if ( (filehandle = open(cpath,flags, S_IREAD | S_IWRITE)) < 0 )
#else
    if ( (filehandle = sopen(cpath,flags,SH_DENYNO, S_IREAD | S_IWRITE)) < 0 )
#endif
                                                      SDBERR(37)
  }
  else
    if ( (filehandle = open(cpath,flags,S_IREAD | S_IWRITE)) < 0 ) 
                                                      SDBERR(37)
  
  if ( read(filehandle,ident,6) != 6 )                ERROR

  if ( memcmp(ident+2,"EB",2) ) 
  {
    if ( chkopt )                                     SDBERR(54)
    ERROR
  }
  if ( memcmp(ident+4,"RB",2) )     
  {
    if ( chkopt )                                     SDBERR(56)
    ERROR
  }

RECOVER
  cond = NO;
ENDSEQ
  if ( filehandle > 0 )
    close(filehandle);
  return(cond);
}

/******************************************************************************/
/**
\brief  Flush - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Flush"

logical eb_DataArea :: Flush ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !access_opt )                                 SDBERR(40)
#ifndef __unix__  
  if ( _commit(file_handle) == -1 )                  SDBERR(99)
#endif

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitFile - 


\return term - Termination code

\param  pheader - 
\param  defentry - 
\param  len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitFile"

logical __cdecl eb_DataArea :: InitFile (EB_Header *pheader, EBDataArea *defentry, uint16 len )
{
  eb_DataArea   dataarea;
  logical       term = NO;
BEGINSEQ
  if ( dataarea.Open((EB_DAHeader *)pheader,defentry->get_file_name(),YES,NO) )  
                                                       ERROR
  dataarea.get_da_header()->set_next_position(dataarea.get_da_header()->get_header_length());
  if ( len )
    if ( !dataarea.Append(len,len,defentry) )          ERROR

  if ( pheader->Write() )                              ERROR

RECOVER
  term = YES;
ENDSEQ
  dataarea.Close();
  return(term);
}

/******************************************************************************/
/**
\brief  Lock - 


\return term - Termination code

\param  position64 - 
\param  length - 
\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical eb_DataArea :: Lock (uint64 position64, int32 length, logical wait )
{
  logical       term = NO;
BEGINSEQ
#ifndef __unix__
  if ( net_opt ) 
  { 
    if ( _lseeki64(file_handle,position64,SEEK_SET) < 0 ) 
                                                     SDBERR(1)
    if ( _locking(file_handle,wait ? _LK_LOCK : _LK_NBLCK,length) )
                                                       ERROR
  }
#endif 

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Open - 


\return term - Termination code

\param  pdaheader - 
\param  path - 
\param  outopt - 
\param  netopt - Multi-user access
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical eb_DataArea :: Open (EB_DAHeader *pdaheader, char *path, logical outopt, logical netopt )
{
  int64   oldpos;
  svel   *svelptr = NULL;
  char   *old_cwd = NULL;
  char   *new_cwd = NULL;
  char    buffer[512];
  logical term    = NO;
BEGINSEQ
//  outopt = NO;                // for SampleDemo, only
  access_opt = outopt;
  net_opt    = netopt;

  if ( pdaheader )
    da_header = pdaheader;
  else
    da_header = new EB_DAHeader(sizeof(EB_extDAHeader),netopt);
  ReplaceSysVariable(path,255);  // das muss life passieren, da es sonst nicht im LDBHandle steht
  
  if (path && *path > ' ') {
      SDBEV1( path ,UNDEF)
  } else {
      SDBEV1( "[NULL]",UNDEF)
  }
  
  if ( strcmp(path,"*_temp") )
  {
    if ( term = !IsFile(path) )
      if ( !access_opt )                              SDBERR(36) 
  
#ifdef __unix__
      if ( (file_handle = open(path,
                               (access_opt ? O_RDWR | O_CREAT : O_RDONLY),
                               S_IREAD | S_IWRITE)) < 0 )
                                                     SDBERR(37)
#else    
    if ( netopt == 1 )
    {
      if ( (file_handle = sopen(path,
                                (access_opt ? O_RDWR | O_CREAT | O_BINARY :
                                              O_RDONLY | O_BINARY         ),
                                 SH_DENYNO, S_IREAD | S_IWRITE)) < 0 )
                                                     SDBERR(37)
    }
    else // shared rootbase (2) or exclusive (0)
      if ( (file_handle = sopen(path,
                                (access_opt ? O_RDWR | O_CREAT | O_BINARY :
                                              O_RDONLY | O_BINARY         ),
                                 SH_DENYWR, S_IREAD | S_IWRITE)) < 0 )
                                                     SDBERR(37)
#endif
  }
  else
  {
    term = YES;
    SDBEV1("Temporary system file",UNDEF)
    if ( !(new_cwd = GetSectionVariable("TMP","SYSTEM")) )
      new_cwd = GetSysVariable("TMP");
    if ( new_cwd && (old_cwd = getcwd(buffer,sizeof(buffer))) )    
      chdir(new_cwd);
    if ( da_header->temp_file = tmpfile() )
      file_handle = _fileno(da_header->temp_file);
    if ( old_cwd  )    
      chdir(old_cwd);
    if ( !da_header->temp_file )                     SDBERR(37)
  }

  da_header->SetFileHandle(file_handle);
  if ( term )
  {
    da_header->stssmod();
    if ( da_header->get_da_size() )
    {
      oldpos = da_header->get_next_position();
      da_header->set_next_position(da_header->get_da_size());
      Write(da_header->get_da_size()-1,1,"");
      da_header->set_next_position(oldpos);
    }

    if ( da_header->get_da_number() )
      if ( da_header->Write() )                       ERROR  
  }
  else  
  {
    if ( da_header->Read() )                          SDBERR(29)
    da_header->UpdatePosition(access_opt); 
    da_header->stssold();
  }
  da_header->stssfil();

  da_number    = da_header->get_da_number();
  term = NO;
RECOVER
  int saverr = SDBERROR;
  Close();
  SDBISET(saverr);
  SDBEV1(path,0)
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Read - 


\return term - Termination code

\param  position64 - 
\param  length - 
\param  area - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

logical eb_DataArea :: Read (uint64 position64, int32 length, void *area )
{
  logical       term = NO;
BEGINSEQ
  if ( Check(position64,length) )                      ERROR

  if ( _lseeki64(file_handle,position64,SEEK_SET) < 0 ) SDBERR(99)
  
  if ( ReadCheck(file_handle,length,area) )          ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReadCheck - 


\return term - Termination code

\param  filehandle - 
\param  length - 
\param  area - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadCheck"

logical __cdecl eb_DataArea :: ReadCheck (int16 filehandle, int32 length, void *area )
{
  register int  i = 50;
  uint32        rlen;
  logical       term = NO;
BEGINSEQ
  if (area)
    while ( i-- )
    {
      if ( !(rlen = (unsigned int)read(filehandle,area,(unsigned int)length)) )
                                                      SDBERR(2)
      if ( rlen == (unsigned int)length )             LEAVESEQ
         
      switch ( errno )
      {
        case EBADF   :
        case EACCES  : tim::timestp(2);
                       break;
        default      : SDBERR(900+errno)
      }               
    }

  SDBERR(6)

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ResetSize - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetSize"

logical eb_DataArea :: ResetSize ( )
{
  logical       term = NO;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
  
  if ( file_handle > 0 && access_opt && da_header &&
       da_header->get_next_position() < _filelengthi64(file_handle) )
  {
#ifdef __unix__
// hier fehlt ev. nich was
      if ( _lseeki64(file_handle,da_header->get_next_position(),SEEK_SET) < 0 )
#else          
      if ( _chsize(file_handle,da_header->get_next_position()) < 0 )
#endif
                                                       SDBERR(4)
  }
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetDynamic - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDynamic"

void eb_DataArea :: SetDynamic ( )
{

  da_header->SetSize(0);

}

/******************************************************************************/
/**
\brief  SetNetOpt - 


\return term - Termination code

\param  netopt - Multi-user access
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetNetOpt"

logical eb_DataArea :: SetNetOpt (logical netopt )
{
  logical                 term = NO;
  net_opt = netopt;
  return(term);
}

/******************************************************************************/
/**
\brief  TraceLock - 


\return term - Termination code

\param  position64 - 
\param  lock_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TraceLock"

logical eb_DataArea :: TraceLock (uint64 position64, logical lock_opt )
{
  static int              count;
  char                    string[255];
  char                    cnum[12];
  logical                 term = NO;
  strcpy(string,lock_opt ? "LOCK  : " :
                           "UNLOCK : "   );
  gvtxltp(strcpy(cnum,"9999999999"),(int32)position64,10);
  strcat(string,cnum);
  
  strcat(string,"   count : ");
  count += lock_opt ? -1 : 1;
  gvtxitp(strcpy(cnum,"999"),count,3);
  strcat(string,cnum);
  SDBError().TraceMessage(string);
  return(term);
}

/******************************************************************************/
/**
\brief  Unlock - 


\return term - Termination code

\param  position64 - 
\param  length - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical eb_DataArea :: Unlock (uint64 position64, int32 length )
{
  logical    term = NO;
BEGINSEQ
#ifndef __unix__
  if ( net_opt )
  {
    if ( _lseeki64(file_handle,position64,SEEK_SET) < 0 )
                                                       SDBERR(1)
    if ( _locking(file_handle,_LK_UNLCK,length) )                   ERROR
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

\param  position64 - 
\param  length - 
\param  area - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Write"

logical eb_DataArea :: Write (uint64 position64, int32 length, void *area )
{
  logical      term = NO;
BEGINSEQ
  if ( position64+length > da_header->get_next_position() )
                                                      SDBERR(39)
  if ( _lseeki64(file_handle,position64,SEEK_SET) < 0 ) SDBERR(99)
    
  if (area)
    if ( (unsigned int)write(file_handle,area,(unsigned int)length) != (unsigned int)length )
      switch ( errno )
      {
        case  EACCES : SDBERR(6)
        default      : SDBERR(1)
      }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  WriteNull - 


\return term - Termination code

\param  position64 - 
\param  length - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WriteNull"

logical eb_DataArea :: WriteNull (uint64 position64, int32 length )
{
  InitArea               *ina = INITArea();
  unsigned int            len;
  logical                 term = NO;
BEGINSEQ
  if ( length < 0 )                                  LEAVESEQ
    
  if ( position64+length > da_header->get_next_position() )
                                                      SDBERR(39)
  if ( _lseeki64(file_handle,position64,SEEK_SET) < 0 ) SDBERR(99)
    
  if ( ! ina->GetArea() )                            SDBERR(99)
    
  while ( length )
  {
    len = MIN(length,ina->GetSize());
    if ( (unsigned int)write(file_handle,ina->GetArea(),len) != len )
      switch ( errno )
      {
        case  EACCES : SDBERR(6)
        default      : SDBERR(1)
      }
    length -= len;
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  eb_DataArea - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "eb_DataArea"

     eb_DataArea :: eb_DataArea ( )
                     :   da_header(NULL), file_handle(0), da_number(0),
  access_opt(NO), net_opt(NO)
{



}

/******************************************************************************/
/**
\brief  ~eb_DataArea - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~eb_DataArea"

     eb_DataArea :: ~eb_DataArea ( )
{



}


