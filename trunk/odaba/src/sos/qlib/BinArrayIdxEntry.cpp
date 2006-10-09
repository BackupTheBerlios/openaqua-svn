/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    BinArrayIdxEntry

\brief    


\date     $Date: 2006/03/12 19:21:19,09 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "BinArrayIdxEntry"

#include  <pdefault.h>
#include  <sBinArray.hpp>
#include  <sBinArrayIdxEntry.hpp>
#include  <sBinArrayIdxEntry.hpp>


/******************************************************************************/
/**
\brief  IsEmpty

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical BinArrayIdxEntry :: IsEmpty ( )
{
  int         i;
  for ( i=0; i<16; i++ )
    if ( lower_entries[i] )
      return(NO);

  return(YES);

}


