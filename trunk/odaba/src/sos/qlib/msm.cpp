/********************************* Class Source Code ***************************/
/**
\package  SOS
\class    msm



\date     $Date: 2006/05/01 18:15:19,06 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "msm"

#include  <pdefault.h>
#include  <cpscb.h>
#include  <fileacc.h>
int32 msm_area = 0;
int32 msm_count = 0;
DLL(pecb) pecb_list;

#include  <imsm.h>

/******************************************************************************/
/**
\brief  msmAppend

\return term - Success

\param  pecbptr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "msmAppend"

logical __cdecl msmAppend (pecb *pecbptr )
{
  logical      test = NO;
  if ( pecbptr )
  {
    msm_count++;
    msm_area += pecbptr->pecbsize;

#ifdef PECB_LIST
    pecb_list.AddTail(pecbptr);

    if ( test )
    {
      int32    indx = 0;
      pecb_list.GoBottom();
      while ( pecbptr = pecb_list.GetPrev() )
      {
        indx++;
        test = NO;
      }
    }
#endif
  }
  return(NO);
}

/******************************************************************************/
/**
\brief  msmInit

\return area - 

\param  pecbptr
\param  lsize
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "msmInit"

void *__cdecl msmInit (pecb *pecbptr, uint32 lsize )
{
  void                   *area = NULL;
  memset(pecbptr,0,lsize+sizeof(pecb));
  pecbptr->pecbsize = lsize+sizeof(pecb);
  pecbptr->pecbstat[3] = 'A';

  return(pecbptr+1);
}

/******************************************************************************/
/**
\brief  msmRemove

\return term - Success

\param  pecbptr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "msmRemove"

logical __cdecl msmRemove (pecb *pecbptr )
{

  if ( pecbptr  )
  {
#ifdef PECB_LIST
    if ( pecb_list.Find(pecbptr))
      pecb_list.RemoveAt();
#endif
    msm_count--;
    msm_area -= pecbptr->pecbsize;
  }
  return(NO);
}

/******************************************************************************/
/**
\brief  msmcl

\return term - Success

\param  pscbptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "msmcl"

int __cdecl msmcl (void **pscbptrp )
{
  logical     term = NO;
BEGINSEQ
  LEAVESEQ

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  msmclck


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "msmclck"

void __cdecl msmclck ( )
{
  pecb       *pecbptr;
  int         blknum  = 0;
  FILE        *filptr = NULL;
BEGINSEQ
  if ( !(filptr = fopen("e:/temp/memcl.lst","at")) )
                                                     ERROR
  fprintf( filptr,"\nMSM-Pool  Entries: %d\n",pecb_list.GetCount());

  if ( pecb_list.GetCount() <= 0 )                   LEAVESEQ
  
  pecb_list.GoTop();
  while ( pecbptr = pecb_list.GetNext() )
    switch ( pecbptr->pecbstat[3]  )
    {
      case 'F'  : break;
      case 'A'  : fprintf(filptr,"    Nicht freigegeben %d\n",(int)pecbptr->pecbsize);
                  break;
      default   : fprintf(filptr,"    Ungültiger Eintrag\n");  ERROR
    }

RECOVER

ENDSEQ
  if ( filptr )
    fclose(filptr);

}

/******************************************************************************/
/**
\brief  msmcs

\return lsize

\param  areaptr - 
\param  lsize
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "msmcs"

uint32 __cdecl msmcs (void **areaptr, uint32 lsize )
{
  pecb     *pecbptr = ((pecb *)*areaptr)-1;
  uint32    space   = pecbptr->pecbsize-sizeof(pecb);
  void     *newarea;
BEGINSEQ
  if ( pecbptr->pecbstat[3] != 'A' )                 SOSERR(1)
  
  if ( lsize <= space )                              LEAVESEQ
  
msmRemove(pecbptr);   
  pecbptr->pecbstat[3] = 'F';
  if ( !(newarea = realloc(pecbptr,lsize+sizeof(pecb))) ) 
                                                     SOSERR(95)
  if ( newarea != pecbptr )
  {
    pecbptr = ((pecb *)newarea);
  }
  
  pecbptr->pecbsize = lsize+sizeof(pecb);
  pecbptr->pecbstat[3] = 'A';
  
msmAppend(pecbptr);   
  *areaptr = pecbptr+1;  
  memset(((char *)*areaptr)+space,0,lsize-space);
RECOVER

ENDSEQ
  return(lsize);

}

/******************************************************************************/
/**
\brief  msmfs

\return term - Success

\param  areaptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "msmfs"

int __cdecl msmfs (void **areaptr )
{
  pecb     *pecbptr;
  logical   term = NO;
BEGINSEQ
  if ( *areaptr )
  {
    pecbptr = ((pecb *)*areaptr)-1;
    if ( pecbptr->pecbstat[3] != 'A' )               SOSERR(1)
      
    pecbptr->pecbstat[3] = 'F';
msmRemove(pecbptr); 

    free(pecbptr);
    *areaptr = NULL;
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  msmgs

\return area - 

\param  lsize
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "msmgs"

void *__cdecl msmgs (uint32 lsize )
{
  pecb       *pecbptr = NULL;
  void       *area;
  short int   pnum;
BEGINSEQ
  SOSRESET

  if ( !lsize )                                             SOSERR(99)
  if ( !(pecbptr = (pecb *)malloc(lsize+sizeof(pecb))) )    SOSERR(95)

  area = msmInit(pecbptr,lsize);
msmAppend(pecbptr);   




RECOVER

ENDSEQ
  return(area);
}

/******************************************************************************/
/**
\brief  msmop

\return pscbptr

\param  psize
\param  emsopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "msmop"

void *__cdecl msmop (int16 psize, logical emsopt )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  msmsize

\return lsize

\param  area - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "msmsize"

uint32 __cdecl msmsize (void *area )
{
  pecb     *pecbptr = ((pecb *)area)-1;
  uint32    lsize = UNDEF;
BEGINSEQ
  if ( pecbptr->pecbstat[3] != 'A' )             SOSERR(1)

  lsize =  pecbptr->pecbsize - sizeof(pecb);

RECOVER

ENDSEQ
  return(lsize);
}

