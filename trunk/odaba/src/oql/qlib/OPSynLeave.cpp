/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPSynLeave

\brief    


\date     $Date: 2006/03/12 19:21:04,09 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPSynLeave"

#include  <poql.h>
#include  <sOPSynLeave.hpp>


/******************************************************************************/
/**
\brief  Execute - 


\return exec_rc -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

ExecReturnCodes OPSynLeave :: Execute ( )
{

  return( ERC_leave );


}

/******************************************************************************/
/**
\brief  OPSynLeave - 


\return term

\param  parent_node -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPSynLeave"

                        OPSynLeave :: OPSynLeave (OPBase *parent_node )
                     : OPBase (NULL,parent_node)
{

  op_type = NT_OPSynLeave;

  SetOPName("leave");
  Initialize(0);

}

/******************************************************************************/
/**
\brief  ~OPSynLeave - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPSynLeave"

                        OPSynLeave :: ~OPSynLeave ( )
{



}


