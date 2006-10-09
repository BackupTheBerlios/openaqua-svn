/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ODBC_Statistics

\brief    


\date     $Date: 2006/03/12 19:17:58,57 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODBC_Statistics"

#include  <popa7.h>
#include  <sODBC_Statistics.hpp>


/******************************************************************************/
/**
\brief  set_CLMN_NAME - 



\param  name -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_CLMN_NAME"

void ODBC_Statistics :: set_CLMN_NAME (char *name )
{


  gvtxstb(COLUMN_NAME,name,sizeof(COLUMN_NAME));


}

/******************************************************************************/
/**
\brief  set_INDX_FLT - 



\param  flt_cond -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_INDX_FLT"

void ODBC_Statistics :: set_INDX_FLT (char *flt_cond )
{


  gvtxstb(FILTER_CONDITION,flt_cond,sizeof(FILTER_CONDITION));


}

/******************************************************************************/
/**
\brief  set_INDX_QN - 



\param  qualifier -
\param  name -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_INDX_QN"

void ODBC_Statistics :: set_INDX_QN (char *qualifier, char *name )
{


  gvtxstb(INDEX_QUALIFIER,qualifier,sizeof(INDEX_QUALIFIER));
  gvtxstb(INDEX_NAME,name,sizeof(INDEX_NAME));


}

/******************************************************************************/
/**
\brief  set_INDX_TSCCP - 



\param  idx_type -
\param  seqnr -
\param  collation -
\param  card -
\param  pages -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_INDX_TSCCP"

void ODBC_Statistics :: set_INDX_TSCCP (int16 idx_type, int16 seqnr, char collation, int32 card, int32 pages )
{


  TYPE         = idx_type;
  SEQ_IN_INDEX = seqnr;
  COLLATION    = collation;
  CARDINALITY  = card;
  PAGES        = pages;


}

/******************************************************************************/
/**
\brief  set_UNIQUE - 



\param  is_unique -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_UNIQUE"

void ODBC_Statistics :: set_UNIQUE (logical is_unique )
{


  NON_UNIQUE =! is_unique;


}


