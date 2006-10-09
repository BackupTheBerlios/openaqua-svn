/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    EntryPoolBlock

\brief    


\date     $Date: 2006/03/12 19:21:37,32 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EntryPoolBlock"

#include  <pdefault.h>
#include  <sEntryPoolBlock.hpp>


/******************************************************************************/
/**
\brief  EntryPoolBlock


\param  size -
\param  count -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EntryPoolBlock"

                        EntryPoolBlock :: EntryPoolBlock (uint16 size, int16 count )
                     : entries(NULL)
{

BEGINSEQ
  if ( !(entries = new char[size*count]) )           SOSERR(95)

  memset(entries,0,size*count);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~EntryPoolBlock


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~EntryPoolBlock"

                        EntryPoolBlock :: ~EntryPoolBlock ( )
{

  delete entries;
  entries = NULL;

}


