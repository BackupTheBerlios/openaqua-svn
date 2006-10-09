/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ACDefine

\brief    


\date     $Date: 2006/03/12 19:15:18,23 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACDefine"

#include  <popa7.h>
#include  <sACDefine.hpp>


/******************************************************************************/
/**
\brief  ACDefine - 



\param  view_def - Internal view definition
\param  access_mode -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACDefine"

                        ACDefine :: ACDefine (DBViewDef &view_def, PIACC access_mode )
                     : ACView()
{


BEGINSEQ
  nodetype = NT_ACDefine;
  
  if ( InitViewParent(view_def) )                    ERROR
    
  nodenode = view_base->get_nodenode();
  view_base->SetPIRef((PropertyHandle *)&view_base);
  
  if ( InitViewStructure(view_def) )                 ERROR

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~ACDefine - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACDefine"

                        ACDefine :: ~ACDefine ( )
{

  if ( nodeidnt == NODE_ID )
    Close();

}


