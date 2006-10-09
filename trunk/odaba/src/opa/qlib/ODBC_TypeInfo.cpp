/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ODBC_TypeInfo

\brief    


\date     $Date: 2006/03/12 19:17:58,89 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODBC_TypeInfo"

#include  <popa7.h>
#include  <sODBC_TypeInfo.hpp>


/******************************************************************************/
/**
\brief  ODBC_TypeInfo - 



\param  name -
\param  sqltype -
\param  prec -
\param  prfx -
\param  suff -
\param  args -
\param  isNULL -
\param  isCS -
\param  isSRCH -
\param  isUNSD -
\param  isMNY -
\param  isAINC -
\param  smin -
\param  smax -
\param  sqlish -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODBC_TypeInfo"

                        ODBC_TypeInfo :: ODBC_TypeInfo (char *name, int16 sqltype, int32 prec, char *prfx, char *suff, char *args, char isNULL, char isCS, char isSRCH, char isUNSD, char isMNY, char isAINC, int16 smin, int16 smax, int16 sqlish )
                     :   DATA_TYPE(sqltype),
  PRECISION(prec),
  NULLABLE(isNULL),
  CASE_SENSITIVE(isCS),
  SEARCHABLE(isSRCH),
  UNSIGNED_ATTRIB(isUNSD),
  MONEY(isMNY),
  AUTO_INCREMENT(isAINC),
  MINIMUM_SCALE(smin),
  MAXIMUM_SCALE(smax),
  sql_match(sqlish)
{

    
  gvtxstb(TYPE_NAME      ,name,sizeof(TYPE_NAME));
  gvtxstb(LOCAL_TYPE_NAME,""  ,sizeof(LOCAL_TYPE_NAME));
  gvtxstb(LITERAL_PREFIX ,prfx,sizeof(LITERAL_PREFIX));
  gvtxstb(LITERAL_SUFFIX ,suff,sizeof(LITERAL_SUFFIX));
  gvtxstb(CREATE_PARAMS  ,args,sizeof(CREATE_PARAMS));


}

/******************************************************************************/
/**
\brief  set_LOCAL_NAME - 



\param  name -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_LOCAL_NAME"

void ODBC_TypeInfo :: set_LOCAL_NAME (char *name )
{

  
  gvtxstb(LOCAL_TYPE_NAME,name,sizeof(LOCAL_TYPE_NAME));


}


