/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    isrt_entry

\brief    


\date     $Date: 2006/03/12 19:22:37,10 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "isrt_entry"

#include  <pdefault.h>
#include  <sisrt_entry.hpp>


/******************************************************************************/
/**
\brief  isrt_entry

-------------------------------------------------------------------------------
\brief i0


\param  ident -
\param  objptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "isrt_entry"

                        isrt_entry :: isrt_entry (uint32 ident, void *objptr )
                     : ident(ident),
  datarea(objptr)
{

BEGINSEQ

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief i1


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "isrt_entry"

                        isrt_entry :: isrt_entry ( )
                     : ident(0),
  datarea(NULL)
{



}

/******************************************************************************/
/**
\brief  operator==

\return term - Success

\param  isrtentry
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical isrt_entry :: operator== (isrt_entry &isrtentry ) const
{

  return ( ident   == isrtentry.ident &&
           datarea == isrtentry.datarea  );

}


