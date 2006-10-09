/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:32:37,32}|(REF)
\class    AH

\brief    


\date     $Date: 2006/03/13 21:33:02,76 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "AH"

#include  <poadi.h>
#include  <sAH.hpp>


/******************************************************************************/
/**
\brief  AH - 



\param  _namec -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AH"

                        AH :: AH (const char *_namec )
                     : ActivityHandler<void,void> (),
  name(_namec)
{



}


