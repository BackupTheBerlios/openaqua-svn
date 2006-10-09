/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|18:19:36,78}|(REF)
\class    LOperation

\brief    


\date     $Date: 2006/04/05 23:10:13,73 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "LOperation"

#include  <popa7.h>
#include  <podaba2.h>
#include  <sACObject.hpp>
#include  <sDBHandle.hpp>
#include  <sDictionary.hpp>
#include  <sParmList.hpp>
#include  <sPropertyHandle.hpp>
#include  <sLOperation.hpp>


/******************************************************************************/
/**
\brief  LOperation - 



\param  prophdl_ref - Reference to Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LOperation"

                        LOperation :: LOperation (PropertyHandle &prophdl_ref )
                     : Operation (prophdl_ref)
{



}

/******************************************************************************/
/**
\brief  ~LOperation - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~LOperation"

                        LOperation :: ~LOperation ( )
{

  Close();

}


