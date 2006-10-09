/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    InstBuffer

\brief    


\date     $Date: 2006/03/12 19:17:36,64 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "InstBuffer"

#include  <popa7.h>
#include  <sbnode.hpp>
#include  <sinti.hpp>
#include  <snode.hpp>
#include  <sInstBuffer.hpp>


/******************************************************************************/
/**
\brief  Cancel - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cancel"

logical InstBuffer :: Cancel ( )
{
  logical                 term = NO;
  while ( count > 0 )
  {
    count--;
    inti_array[count]->Cancel();
    inti_array[count]->set_inst_index(AUTO);
  }
  count    = AUTO;
  startpos = AUTO;
  lastpos  = AUTO;
  curpos   = AUTO;
  backward = NO;
  return(term);
}

/******************************************************************************/
/**
\brief  Fill - Fill buffer instance from current inti


\return term - Termination code

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

logical InstBuffer :: Fill (int32 indx0 )
{
  logical                 term = NO;
BEGINSEQ
  if ( indx0 >= buf_count )                          ERROR
    
  inti_array[indx0]->CopyBufferInstance(node_ref->get_nodeinst());
  
  if ( indx0 == 0 ) // first instance
    startpos = node_ref->get_nodeinst()->get_inst_index();
  lastpos  = node_ref->get_nodeinst()->get_inst_index();
  count = indx0+1;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Get - 


\return instptr -
-------------------------------------------------------------------------------
\brief i00


\param  lindx0 -
\param  direction -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *InstBuffer :: Get (int32 lindx0, int16 direction )
{
  int32                   bufindex = 0;
  void                   *instptr  = NULL;
BEGINSEQ
  if ( count == AUTO                                          ||
       (!backward && (lindx0 < startpos || lindx0 > lastpos)) ||
       ( backward && (lindx0 > startpos || lindx0 < lastpos))    )
  {
    bufindex = AUTO;
    if ( node_ref->ReadBuffer(lindx0,direction) < 0 ) 
                                                     ERROR
    if ( direction || startpos == lindx0 )
      bufindex = 0;
  }
  else
  {    
    bufindex = backward ? GetBackward(lindx0,direction) 
                        : GetForeward(lindx0,direction);
    if ( bufindex == AUTO )                          ERROR
    
    if ( bufindex >= count && count < buf_count )    ERROR // end of collection;
    if ( bufindex >= count || bufindex < 0 )
    {
      bufindex = AUTO;
      if ( node_ref->ReadBuffer(lindx0,direction) == AUTO )
                                                     ERROR
      if ( direction || startpos == lindx0 )
        bufindex = 0;
    }
  }
  
  if ( count == AUTO || bufindex == AUTO )           ERROR
  
  node_ref->get_nodeinst()->CopyBufferInstance(inti_array[bufindex]);
  instptr = node_ref->get_nodeinst()->get_iselarea();

RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief i01


\param  skey -
\param  direction -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *InstBuffer :: Get (char *skey, int16 direction )
{
  int                     bufindex = 0;
  char                    keyarea[MAX_KEYLEN];
  int                     lk;
  int                     fk;
  logical                 read    = NO;
  char                    wskey[MAX_KEYLEN];
  void                   *instptr = NULL;
BEGINSEQ
  if ( !node_ref->GetSortKeySMCB() )                 SDBERR(71)
  node_ref->SaveKey(wskey,skey);
  
  if ( count <= 0 )
    read = YES;
  else
  { 
    lk = node_ref->CompareSortKey(node_ref->ExtractSortKey(keyarea,inti_array[count-1]->get_iselarea(),NO),wskey,NO);
    fk = node_ref->CompareSortKey(node_ref->ExtractSortKey(keyarea,inti_array[0]->get_iselarea(),NO),wskey,NO);
// für absteigende indizes geht das nocht nicht!! 
    if ( ( !backward && ( fk >= 0 || lk < 0  )) ||
         (  backward && ( fk >  0 || lk <= 0 ))    )
      read = YES;
  }
  
  if ( read )
  {
    bufindex = AUTO;
    if ( node_ref->LocateKey(skey,YES) )             ERROR
    instptr = Get(node_ref->GetCurrentIndex(),direction);
  }
  else
  {  
    while ( bufindex < count )
    {
      switch ( node_ref->CompareSortKey(node_ref->ExtractSortKey(keyarea,inti_array[bufindex],NO),wskey,NO) )
      {
// für absteigende indizes geht das so nicht!! 
        case 0 :                                     LEAVESEQ
        case 1 : if ( !backward )                    ERROR
                 break;
        case -1: if ( backward )                     ERROR
                 break;
        default: ;         
      }
      bufindex++;
    }
  }
  instptr = bufindex < count ? inti_array[bufindex] : NULL;


RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  GetBackward - 


\return bufindex

\param  lindx0 -
\param  direction -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBackward"

int32 InstBuffer :: GetBackward (int32 lindx0, int16 direction )
{
  int32                   bufindex = 0;
  int16                   dir = direction;
  int32                   curi     = -1;
BEGINSEQ
  if ( startpos-lastpos+1 == count && 
       inti_array[count-1-(lindx0-lastpos)]->get_inst_index() == lindx0 )
  {
    bufindex = count-1-(lindx0-lastpos);
    curi     = lindx0;
  }
  else
  {
    while ( curi > lindx0 && bufindex < count )
    {
      curi = inti_array[bufindex]->get_inst_index();
      if ( lindx0 < curi )
        bufindex++;
    }
  }
  
  if ( curi != lindx0 )
  {
    if ( !dir )                                   ERROR
    if ( dir < 0 )
      dir++;
    else
      dir--, bufindex--;
  }

  bufindex -= dir;

RECOVER
  bufindex = AUTO;
ENDSEQ
  return(bufindex);
}

/******************************************************************************/
/**
\brief  GetForeward - 


\return bufindex

\param  lindx0 -
\param  direction -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetForeward"

int32 InstBuffer :: GetForeward (int32 lindx0, int16 direction )
{
  int32                   bufindex = 0;
  int16                   dir = direction;
  int                     curi     = -1;
BEGINSEQ
  if ( lastpos-startpos+1 == count && 
       inti_array[lindx0-startpos]->get_inst_index() == lindx0 )
  {
    bufindex = lindx0-startpos;
    curi     = lindx0;
  }
  else
  {
    while ( curi < lindx0 && bufindex < count )
    {
      curi = inti_array[bufindex]->get_inst_index();
      if ( lindx0 > curi )
        bufindex++;
    }
  }
  
  if ( curi != lindx0 )
  {
    if ( !dir )                                     ERROR
    if ( dir > 0 )
      dir--;
    else
      dir++, bufindex--;
  }

  bufindex += dir;

RECOVER
  bufindex = AUTO;
ENDSEQ
  return(bufindex);
}

/******************************************************************************/
/**
\brief  GetLastPos - 


\return lastpos -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLastPos"

int32 InstBuffer :: GetLastPos ( )
{

  return( backward ? startpos : lastpos );

}

/******************************************************************************/
/**
\brief  InstBuffer - Konstruktor



\param  max_inst -
\param  bnode_ptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstBuffer"

                        InstBuffer :: InstBuffer (int32 max_inst, bnode *bnode_ptr )
                     : buf_count(max_inst),
  inti_array(max_inst),
  node_ref(bnode_ptr),
  startpos(AUTO),
  lastpos(AUTO),
  last_abspos(AUTO),
  curpos(AUTO),
  count(AUTO),
  backward(NO),
  eof(NO)
{
  inti        *oldinti = bnode_ptr->get_nodeinst();
  inti        *intiptr;
  char        *maxbuf;
  int32         maxbufsize;
BEGINSEQ
  if ( maxbuf = GetSysVariable("MAX_BUFFER_SIZE") )
    if ( (maxbufsize = atol(maxbuf)) > 0 )
      max_inst = MAX(2,maxbufsize/(100+bnode_ptr->GetStructDef()->GetNetLength()));
  if ( buf_count > max_inst )
    buf_count = max_inst;
       
  while ( max_inst-- )
  {
    if ( !(intiptr = bnode_ptr->CreateInti(NULL,bnode_ptr->get_nodefield()->GetDBStruct(),NULL,NO)) )
                                                     ERROR
    intiptr->stsstrans();
    inti_array[max_inst] = intiptr;
    inti_array[max_inst]->set_inst_index(AUTO);
  }

RECOVER

ENDSEQ
  bnode_ptr->SetCurrentInti(oldinti);
}

/******************************************************************************/
/**
\brief  Locate - Locates an instance in the buffer
        The  instance is located in the  buffer according to the buffer position
        indx0.

\return term - Termination code

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

logical InstBuffer :: Locate (int32 indx0 )
{
  inti                   *intiptr = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( indx0 >= count )                              ERROR
  intiptr = inti_array[indx0];

  if ( intiptr->get_inst_index() == AUTO )           ERROR
  
  node_ref->get_nodeinst()->CopyBufferInstance(intiptr);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Read - 


\return count -

\param  lindx0 -
\param  direction -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

int32 InstBuffer :: Read (int32 lindx0, int16 direction )
{
  int32                   bufindex = 0;
  int32                   pos;
  int16                   idir     = direction;
  int32                   indx0;
  logical                 term     = NO;
BEGINSEQ
// stats.Start();
  
  if ( eof && lindx0 > lastpos )                    ERROR
  eof = NO;
  
  if ( !direction )
  {
    if ( (!backward && lindx0 < startpos) || (backward && lindx0 < lastpos))
      idir = -1;
    if ( (!backward && lindx0 > startpos) || (backward && lindx0 > lastpos))
      idir = 1;
  }
  backward = idir < 0;
  
  if ( lindx0 == AUTO )
  {
    lindx0 = backward ? LAST_INSTANCE : FIRST_INSTANCE;
    idir -= backward ? -1 : 1;
  }  
  
  indx0 = node_ref->GetAt(lindx0,backward ? -1 : 1,NO);
  
  Cancel();
  count = 0;
  
  if ( indx0 == AUTO )                               ERROR
  if ( indx0 != lindx0 )
    idir -= backward ? -1 : 1;
  if ( direction )
    node_ref->Position(idir);
  
  if ( !(count = backward ? ReadBackward()
                          : ReadForeward()) )        ERROR
  

RECOVER
  count = AUTO;
ENDSEQ
// stats.Stop();
  return(count);
}

/******************************************************************************/
/**
\brief  ReadBackward - 


\return count -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadBackward"

int32 InstBuffer :: ReadBackward ( )
{
  int32                   bufindex = 0;
  int32                   lindx0;
  int32                   pos;
  logical                 bef_beg = NO;
  logical                 term    = NO;
BEGINSEQ
  if ( (lindx0 = node_ref->GetCurrentIndex()) == AUTO ) ERROR
    
  pos = lindx0;        
  while ( bufindex < buf_count )
  {
    if ( bef_beg )
      inti_array[bufindex]->set_inst_index(AUTO);
    else
    {
      if ( lindx0 >= 0 && (lindx0 = node_ref->GetAt(lindx0,-1,NO)) != AUTO )
      {
        inti_array[bufindex]->CopyBufferInstance(node_ref->get_nodeinst());
        count++;
        lindx0--;
      }
      else
      {
        SDBCERR
        bef_beg = YES;
      }
    }
    bufindex++;
  }
  
  if ( count )
  {
    startpos = pos;
    lastpos  = inti_array[count-1]->get_inst_index();
  }
RECOVER
  count = AUTO;
ENDSEQ
// stats.Stop();
  return(count);
}

/******************************************************************************/
/**
\brief  ReadForeward - 


\return count -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadForeward"

int32 InstBuffer :: ReadForeward ( )
{
  int                     bufindex = 0;
  int32                   lindx0;
  int                     pos;
  logical                 term = NO;
BEGINSEQ
  if ( (lindx0 = node_ref->GetCurrentIndex()) == AUTO ) ERROR
    
  pos = lindx0;        
  while ( bufindex < buf_count )
  {
    if ( eof )
      inti_array[bufindex]->set_inst_index(AUTO);
    else
    {
      if ( (lindx0 = node_ref->GetAt(lindx0,1,NO)) != AUTO )
      {
        inti_array[bufindex]->CopyBufferInstance(node_ref->get_nodeinst());
        count++;
        lindx0++;
      }
      else
      {
        SDBCERR
        eof = YES;
      }
    }
    bufindex++;
  }

  if ( count )
  {
    startpos = pos;
    lastpos  = inti_array[count-1]->get_inst_index();
  }
RECOVER
  count = AUTO;
ENDSEQ
// stats.Stop();
  return(count);
}

/******************************************************************************/
/**
\brief  SetVersion - 


\return term - Termination code

\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

logical InstBuffer :: SetVersion (uint16 version_nr )
{
  int32                   lindx0 = startpos;
  int32                   count = buf_count;
  logical                 term = NO;
BEGINSEQ
  if ( startpos == AUTO )                            LEAVESEQ
  
  Cancel();
  
  while ( count-- )
    inti_array[count]->SetVersion(version_nr);

  if ( Read(lindx0,0) == AUTO )                      ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~InstBuffer - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~InstBuffer"

                        InstBuffer :: ~InstBuffer ( )
{

  Cancel();
  
  while ( buf_count-- )
    delete inti_array[buf_count];

//  stats.Print("Get",YES); // print with headline


}


