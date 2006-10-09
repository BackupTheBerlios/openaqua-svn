/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    eb_Buffer

\brief    


\date     $Date: 2006/03/12 19:18:38,40 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "eb_Buffer"

#include  <popa7.h>
#include  <sEB_Number.hpp>
#include  <seb_BufferEntry.hpp>
#include  <ssrt.hpp>
#include  <seb_Buffer.hpp>


/******************************************************************************/
/**
\brief  Add - 


\return term - Termination code

\param  odblen -
\param  entnr -
\param  area -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

logical eb_Buffer :: Add (int32 odblen, EB_Number entnr, void *area )
{
  eb_BufferEntry   bufentry;
  eb_BufferEntry  *bufptr;
  int16            indx;
  logical   term = NO;

BEGINSEQ
  bufentry.SetLength(0);
  bufentry.SetPosition(entnr);
  bufentry.SetAreaPointer(area ? area : (char *)buffer_area+next_position);

  if ( !(indx = entry_table->srtkad(&bufentry)) )     SDBERR(95)
  if ( bufptr = GetTableEntry((int16)(indx+1)) )
    GetTableEntry(indx)->SetAreaPointer(bufptr->get_buffer_pointer());
     
  if ( !ChangeEntrySize(odblen,entnr) )                         
  {
    entry_table->srtidl(indx);                        ERROR
  }
  
  GetTableEntry(indx)->SetIndex(NO);
  stssfil();

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  ChangeEntrySize - 


\return area -

\param  newsize -
\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeEntrySize"

void *eb_Buffer :: ChangeEntrySize (int32 newsize, EB_Number entnr )
{
  eb_BufferEntry  *bufenty;  
  eb_BufferEntry  *bufptr;  
  void            *curpos;
  char            *pos;
  int16            indx = 0;
  uint16           len;
  uint32           size;
  char            *start;
  int32         dif;
  logical          term = NO;
BEGINSEQ

  if ( !(bufenty = GetTableEntry(entnr)) )             ERROR
  curpos = bufenty->get_buffer_pointer();

  if ( dif = newsize - bufenty->get_length() )
  {
    bufenty->SetIndex(YES);
    if ( dif > buffer_size - current_position )
    {
      size  = current_position + dif+8;
      size += MAX(256,MIN(1000,size/10));
      if ( msmcs(&buffer_area,size) < size )   SDBERR(95)
      buffer_size = size-8;
      pos = (char *)buffer_area;
      while ( bufptr = (eb_BufferEntry *)entry_table->srtigt(++indx) )
      {
        bufptr->SetAreaPointer(pos);
        pos += bufptr->get_length();
      }
      curpos = bufenty->get_buffer_pointer();
    }

    if ( (char *)curpos - (char *)buffer_area != next_position )
    {
      start = (char *)curpos + newsize;
      len   = (int16)(next_position - ((char *)curpos - (char *)buffer_area) 
                                                      - bufenty->get_length());
      if ( dif < 0 )
        memcpy(start,(char *)curpos+bufenty->get_length(),len);
      else
        memmove(start,(char *)curpos+bufenty->get_length(),len);
  
      indx = 0;
      while ( bufptr = GetTableEntry(++indx) )
//      if ( bufptr->get_buffer_pointer() > curpos )
        if ( bufptr > bufenty )
          bufptr->SetAreaPointer((char *)bufptr->get_buffer_pointer() + dif);
    }
      
    bufenty->SetLength(newsize);
    next_position    += dif;
    current_position += dif;
  }   

RECOVER
  curpos = NULL;
ENDSEQ
  return(curpos);

}

/******************************************************************************/
/**
\brief  Clear - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

logical eb_Buffer :: Clear ( )
{

  entry_table->srtres();
  current_position = 0;
  next_position    = 0;


  return(NO);

}

/******************************************************************************/
/**
\brief  Compress - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Compress"

logical eb_Buffer :: Compress ( )
{
  int16             indx = 0;
  eb_BufferEntry   *bufptr;
  char             *curbuf = (char *)buffer_area;

//  while ( bufptr = GetTableEntry(++indx) )
//    bufptr->SetIndex(indx);

  entry_table->srtsor(BUFKEY_POS,BUFKEY_LEN,BUFKEY_TYP);  

  next_position = 0;
  indx = 0;
  while ( bufptr = GetTableEntry(++indx) )
  {
    memcpy(curbuf,bufptr->get_buffer_pointer(),(int)bufptr->get_length());
    bufptr->SetAreaPointer(curbuf);
    curbuf        += bufptr->get_length();
    next_position += bufptr->get_length();
  }   

//  entry_table->srtsor(TEMPKEY_POS,TEMPKEY_LEN,TEMPKEY_TYP);  
  entry_table->srtsor(EBKEY_POS,EBKEY_LEN,EBKEY_TYP);
  return(NO);

}

/******************************************************************************/
/**
\brief  Delete - 


\return term - Termination code

\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical eb_Buffer :: Delete (EB_Number entnr )
{
  int16          indx = entry_table->srtcnt()+1;
  logical        term = NO;
BEGINSEQ
  while ( --indx )
    if ( entnr == GetTableEntry(indx)->get_eb_position() )
      break;

  if ( !indx )                                             ERROR

  current_position -= GetTableEntry(indx)->get_length();
  entry_table->srtidl(indx);


RECOVER
  term = YES;

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Get - 


\return area -

\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *eb_Buffer :: Get (EB_Number entnr )
{
  eb_BufferEntry  *bufenty = GetTableEntry(entnr);


  return ( bufenty ? bufenty->get_buffer_pointer() : NULL );

}

/******************************************************************************/
/**
\brief  GetEntryCount - 


\return ecnt -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntryCount"

int16 eb_Buffer :: GetEntryCount ( )
{


  return ( entry_table->srtcnt() );

}

/******************************************************************************/
/**
\brief  GetTableEntry - 


\return bufentry -
-------------------------------------------------------------------------------
\brief OBUFBGET


\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTableEntry"

eb_BufferEntry *eb_Buffer :: GetTableEntry (EB_Number entnr )
{
  eb_BufferEntry  *bufentry = NULL;
  int16            indx     = entry_table->srtcnt()+1;

BEGINSEQ
  if ( !(indx = entry_table->srtssr((char *)&entnr)) )  ERROR
  bufentry = GetTableEntry(indx);

RECOVER

ENDSEQ
  return(bufentry);

}

/******************************************************************************/
/**
\brief  Initialize - 


\return area -

\param  odblen -
\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void *eb_Buffer :: Initialize (int32 odblen, EB_Number entnr )
{
  char             *area   = NULL;
  eb_BufferEntry   *bufptr;
  int32          maxsize = 1024L*63;

BEGINSEQ
  while( odblen > buffer_size - current_position &&  
         !LowPriorityDel() ) ; 

  if ( odblen > buffer_size )
  {
    msmfs(&buffer_area);
    if ( odblen > maxsize || 
         !(buffer_area = msmgs(buffer_size = MIN(maxsize,2*odblen))) )
                                                      SDBERR(95)
  }

  if ( !entry_table->srtfgt() )
    LowPriorityDel();

  if ( odblen > buffer_size - next_position )
    Compress();

  bufptr  = (eb_BufferEntry *)entry_table->srtfad();
  area    = (char *)buffer_area + next_position;
  memset(area,0,(uint16)odblen);

  bufptr->SetLength(odblen);
  bufptr->SetAreaPointer(area);
  bufptr->SetPosition(entnr);
  
  next_position    += odblen;
  current_position += odblen;
  
  stssfil();
RECOVER
  buffer_size = 0;
ENDSEQ
  return(area);

}

/******************************************************************************/
/**
\brief  Locate - 


\return area -

\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

void *eb_Buffer :: Locate (EB_Number entnr )
{
  eb_BufferEntry   bufenty;
  int16            indx = entry_table->srtcnt()+1;
  void            *area = NULL;
BEGINSEQ
  while ( --indx )
    if ( entnr == GetTableEntry(indx)->get_eb_position() )
      break;

  if ( !indx )                                             ERROR
    
  bufenty = *GetTableEntry(indx);
  entry_table->srtidl(indx);
  entry_table->srtiad(entry_table->srtcnt()+1,&bufenty);

  area = bufenty.get_buffer_pointer();

RECOVER

ENDSEQ
  return(area);

}

/******************************************************************************/
/**
\brief  LowPriorityDel - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LowPriorityDel"

logical eb_Buffer :: LowPriorityDel ( )
{
  eb_BufferEntry   *bufptr;
  logical           term = NO;
BEGINSEQ
  if ( !(bufptr = GetTableEntry((int16)1)) )	   SDBERR(43)
  
  current_position -= bufptr->get_length();
  entry_table->srtidl(1);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Remove - 



\param  area -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

void eb_Buffer :: Remove (void *area )
{
  int16             indx = 0;
  eb_BufferEntry   *bufptr;


BEGINSEQ
  if ( !area )                                          LEAVESEQ

  while ( bufptr = GetTableEntry(++indx) )
    if ( bufptr->get_buffer_pointer() == area )
      break;

  if ( bufptr )
  {
    current_position -= bufptr->get_length();
    entry_table->srtidl(indx);
  }  

ENDSEQ

}

/******************************************************************************/
/**
\brief  Update - 


\return term - Termination code

\param  odblen -
\param  entnr -
\param  area -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Update"

logical eb_Buffer :: Update (int32 odblen, EB_Number entnr, void *area )
{
  void     *entryarea;
  logical   term = NO;

BEGINSEQ

  if ( !(entryarea = ChangeEntrySize(odblen,entnr)) )     ERROR
  memcpy(entryarea,area,(int)odblen);

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  eb_Buffer - 



\param  maxbuf -
\param  expand -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "eb_Buffer"

                        eb_Buffer :: eb_Buffer (int32 maxbuf, logical expand )
                     : sts(),
 ms_pool(NULL), buffer_area(NULL), 
 entry_table(NULL), buffer_size(MAX(256,maxbuf)), 
 current_position(0), next_position(0)

{

BEGINSEQ
  if ( !(buffer_area = msmgs(buffer_size+8)) )        SDBERR(95)

  entry_table = new srt(OBUF_MAX,sizeof(eb_BufferEntry),
                        EBKEY_LEN,EBKEY_POS,EBKEY_TYP,expand);

  if ( entry_table->stscerr() )                       ERROR
  
  stssini();
  SDBRESET

RECOVER
  stsserr();  

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~eb_Buffer - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~eb_Buffer"

                        eb_Buffer :: ~eb_Buffer ( )
{

BEGINSEQ
  delete entry_table;
  msmfs(&buffer_area);
  if ( msmcl(&ms_pool) )                              SDBERR(96)


RECOVER

ENDSEQ

}


