/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    refEntry

\brief    


\date     $Date: 2006/03/12 19:19:24,51 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "refEntry"

#include  <popa7.h>
#include  <sref.hpp>
#include  <srefEntry.hpp>


/******************************************************************************/
/**
\brief  refEntry - 


-------------------------------------------------------------------------------
\brief i0


\param  indxnam -
\param  refptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "refEntry"

                        refEntry :: refEntry (char *indxnam, ref *refptr )
                     : ref_pointer(refptr)
{

  memcpy(ref_name,indxnam,sizeof(ref_name));

}

/******************************************************************************/
/**
\brief i1


\param  refptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "refEntry"

                        refEntry :: refEntry (ref *refptr )
                     : ref_pointer(refptr)
{

  memset(ref_name,' ',ID_SIZE);

}


