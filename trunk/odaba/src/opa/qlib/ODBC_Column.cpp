/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ODBC_Column

\brief    


\date     $Date: 2006/03/12 19:17:58,09 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODBC_Column"

#include  <popa7.h>
#include  <sODBC_Column.hpp>


/******************************************************************************/
/**
\brief  set_CLMN_NAME - 



\param  name -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_CLMN_NAME"

void ODBC_Column :: set_CLMN_NAME (char *name )
{


  gvtxstb(COLUMN_NAME,name,sizeof(COLUMN_NAME));


}

/******************************************************************************/
/**
\brief  set_DATA_TYPE - 



\param  sqltype -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_DATA_TYPE"

void ODBC_Column :: set_DATA_TYPE (int16 sqltype )
{


  DATA_TYPE = sqltype;


}

/******************************************************************************/
/**
\brief  set_LPS - 



\param  length -
\param  precision -
\param  scale -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_LPS"

void ODBC_Column :: set_LPS (int32 length, int32 precision, int16 scale )
{


  LENGTH    = length;
  PRECISION = precision;
  SCALE     = scale;


}

/******************************************************************************/
/**
\brief  set_NULLABLE - 



\param  is_nullable -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_NULLABLE"

void ODBC_Column :: set_NULLABLE (char is_nullable )
{


  NULLABLE = is_nullable;


}

/******************************************************************************/
/**
\brief  set_RADIX - 



\param  radix -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_RADIX"

void ODBC_Column :: set_RADIX (int16 radix )
{


  RADIX = radix;


}

/******************************************************************************/
/**
\brief  set_REMARKS - 



\param  description -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_REMARKS"

void ODBC_Column :: set_REMARKS (char *description )
{


   gvtxstb(REMARKS,description,sizeof(REMARKS));


}

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

void ODBC_Column :: set_TBL_QNO (char *qualifier, char *name, char *owner )
{


  gvtxstb(TABLE_QUALIFIER,qualifier,sizeof(TABLE_QUALIFIER));
  gvtxstb(TABLE_NAME,     name,     sizeof(TABLE_NAME));
  gvtxstb(TABLE_OWNER,    owner,    sizeof(TABLE_OWNER));


}

/******************************************************************************/
/**
\brief  set_TYPE_NAME - 



\param  name -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_TYPE_NAME"

void ODBC_Column :: set_TYPE_NAME (char *name )
{


  gvtxstb(TYPE_NAME,name,sizeof(TYPE_NAME));


}


