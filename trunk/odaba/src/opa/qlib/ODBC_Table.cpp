/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ODBC_Table

\brief    


\date     $Date: 2006/03/12 19:17:58,78 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODBC_Table"

#include  <popa7.h>
#include  <sODBC_Table.hpp>


/******************************************************************************/
/**
\brief  set_TBL_QNO - 



\param  qualifier -
\param  name -
\param  owner -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_TBL_QNO"

void ODBC_Table :: set_TBL_QNO (char *qualifier, char *name, char *owner )
{

  
  gvtxstb(TABLE_QUALIFIER,qualifier,sizeof(TABLE_QUALIFIER));
  gvtxstb(TABLE_NAME,     name,     sizeof(TABLE_NAME));
  gvtxstb(TABLE_OWNER,    owner,    sizeof(TABLE_OWNER));


}

/******************************************************************************/
/**
\brief  set_TBL_REMARKS - 



\param  description -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_TBL_REMARKS"

void ODBC_Table :: set_TBL_REMARKS (char *description )
{

  
  gvtxstb(REMARKS,description,sizeof(REMARKS));


}

/******************************************************************************/
/**
\brief  set_TBL_TYPE - 



\param  tbl_type -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_TBL_TYPE"

void ODBC_Table :: set_TBL_TYPE (char *tbl_type )
{

  
  gvtxstb(TABLE_TYPE,tbl_type,sizeof(TABLE_TYPE));


}


