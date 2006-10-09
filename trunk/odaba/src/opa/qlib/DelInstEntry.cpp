/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DelInstEntry

\brief    


\date     $Date: 2006/03/12 19:17:17,60 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DelInstEntry"

#include  <popa7.h>
#include  <sDelInstEntry.hpp>


/******************************************************************************/
/**
\brief  DelInstEntry - 


-------------------------------------------------------------------------------
\brief i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DelInstEntry"

                        DelInstEntry :: DelInstEntry ( )
                     :   entnr(),
  next(NULL)
{

  memset(extent_name,' ',ID_SIZE);

}

/******************************************************************************/
/**
\brief i01


\param  extnames - Extent name
\param  pifent -
\param  di_entry -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DelInstEntry"

                        DelInstEntry :: DelInstEntry (char *extnames, EB_Number pifent, DelInstEntry *di_entry )
                     :   entnr(pifent),
  next(di_entry)
{

  gvtxstb(extent_name,extnames,ID_SIZE);

}

/******************************************************************************/
/**
\brief  GetLast

\return di_entry -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLast"

DelInstEntry *DelInstEntry :: GetLast ( )
{
  DelInstEntry   *di_entry = this;
BEGINSEQ
  if ( !di_entry )                                   ERROR
    
  while ( di_entry->next )
    di_entry = di_entry->next;
RECOVER

ENDSEQ
 return(di_entry);
}

/******************************************************************************/
/**
\brief  set_next


\param  di_entry -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_next"

void DelInstEntry :: set_next (DelInstEntry *di_entry )
{

  next = di_entry;

}

/******************************************************************************/
/**
\brief  ~DelInstEntry - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DelInstEntry"

                        DelInstEntry :: ~DelInstEntry ( )
{

  if ( next ) 
    delete next;
  next = NULL;

}


