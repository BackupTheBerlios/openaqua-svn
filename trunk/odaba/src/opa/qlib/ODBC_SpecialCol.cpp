/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ODBC_SpecialCol

\brief    


\date     $Date: 2006/03/12 19:17:58,35 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODBC_SpecialCol"

#include  <popa7.h>
#include  <sODBC_SpecialCol.hpp>


/******************************************************************************/
/**
\brief  set_CLMN_NAME - 



\param  name -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_CLMN_NAME"

void ODBC_SpecialCol :: set_CLMN_NAME (char *name )
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

void ODBC_SpecialCol :: set_DATA_TYPE (int16 sqltype )
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

void ODBC_SpecialCol :: set_LPS (int32 length, int32 precision, int16 scale )
{


  LENGTH    = length;
  PRECISION = precision;
  SCALE     = scale;


}

/******************************************************************************/
/**
\brief  set_PSEUDO - 



\param  is_pseudo -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_PSEUDO"

void ODBC_SpecialCol :: set_PSEUDO (char is_pseudo )
{


  PSEUDO_COLUMN = is_pseudo;


}

/******************************************************************************/
/**
\brief  set_SCOPE - 



\param  scope -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_SCOPE"

void ODBC_SpecialCol :: set_SCOPE (int16 scope )
{


  SCOPE = scope;


}

/******************************************************************************/
/**
\brief  set_TYPE_NAME - 



\param  name -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_TYPE_NAME"

void ODBC_SpecialCol :: set_TYPE_NAME (char *name )
{

  
  gvtxstb(TYPE_NAME,name,sizeof(TYPE_NAME));


}


