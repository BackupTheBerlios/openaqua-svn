/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    exdEntry

\brief    


\date     $Date: 2006/03/12 19:18:51,26 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "exdEntry"

#include  <popa7.h>
#include  <sexd.hpp>
#include  <sexdEntry.hpp>


/******************************************************************************/
/**
\brief  exdEntry - 



\param  entnr -
\param  exdarea -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "exdEntry"

                        exdEntry :: exdEntry (EB_Number entnr, exd *exdarea )
                     : entry_number(entnr.get_ebsnum()),
inst_area(exdarea)
{



}


