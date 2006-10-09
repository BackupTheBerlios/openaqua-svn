/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OperResources

\brief    


\date     $Date: 2006/03/12 19:21:10,70 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OperResources"

#include  <poql.h>
#include  <sACObject.hpp>
#include  <sDictionary.hpp>
#include  <sOperResources.hpp>


/******************************************************************************/
/**
\brief  OperResources - 



\param  dictptr
\param  resobj -
\param  obhandle -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OperResources"

                        OperResources :: OperResources (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle )
                     : dictionary(dictptr),
  resource_hdl(resobj),
  object_ref(obhandle)
{



}


