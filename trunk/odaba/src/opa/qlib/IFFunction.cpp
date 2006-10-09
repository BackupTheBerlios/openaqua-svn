/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    IFFunction

\brief    


\date     $Date: 2006/03/12 19:17:36,39 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "IFFunction"

#include  <popa7.h>
#include  <csfctp.h>
#include  <sCSInstanceList.hpp>
#include  <sCS_Connection.hpp>
#include  <sIFFunction.hpp>


/******************************************************************************/
/**
\brief  Execute - 


\return term - Termination code

\param  connection -
\param  cso_ptr -
\param  cparms -
\param  result -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical IFFunction :: Execute (CS_Connection *connection, void *cso_ptr, CSInstanceList *cparms, CSInstanceList *result )
{

  return ( (*function_ptr)(connection,cso_ptr,cparms,result) );

}

/******************************************************************************/
/**
\brief  IFFunction - 



\param  cs_execute -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IFFunction"

                        IFFunction :: IFFunction (CS_FCTP cs_execute )
                     : function_ptr()
{

  function_ptr = cs_execute;

}


