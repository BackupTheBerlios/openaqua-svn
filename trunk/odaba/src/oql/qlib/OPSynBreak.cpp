/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPSynBreak

\brief    


\date     $Date: 2006/03/12 19:21:02,09 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPSynBreak"

#include  <poql.h>
#include  <sOPSynBreak.hpp>


/******************************************************************************/
/**
\brief  Execute - 


\return exec_rc -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

ExecReturnCodes OPSynBreak :: Execute ( )
{

  return( ERC_break );


}

/******************************************************************************/
/**
\brief  OPSynBreak - 


\return term

\param  parent_node -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPSynBreak"

                        OPSynBreak :: OPSynBreak (OPBase *parent_node )
                     : OPBase (NULL,parent_node)
{

  op_type = NT_OPSynBreak;

  SetOPName("break");
  Initialize(0);

}

/******************************************************************************/
/**
\brief  ~OPSynBreak - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPSynBreak"

                        OPSynBreak :: ~OPSynBreak ( )
{



}


