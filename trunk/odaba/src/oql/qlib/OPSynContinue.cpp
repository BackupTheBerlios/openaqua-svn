/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPSynContinue

\brief    


\date     $Date: 2006/03/12 19:21:02,60 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPSynContinue"

#include  <poql.h>
#include  <sOPSynContinue.hpp>


/******************************************************************************/
/**
\brief  Execute - 


\return exec_rc -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

ExecReturnCodes OPSynContinue :: Execute ( )
{

  return( ERC_continue );


}

/******************************************************************************/
/**
\brief  OPSynContinue - 


\return term

\param  parent_node -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPSynContinue"

                        OPSynContinue :: OPSynContinue (OPBase *parent_node )
                     : OPBase (NULL,parent_node)
{

  op_type = NT_OPSynContinue;

  SetOPName("continue");
  Initialize(0);

}

/******************************************************************************/
/**
\brief  ~OPSynContinue - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPSynContinue"

                        OPSynContinue :: ~OPSynContinue ( )
{



}


