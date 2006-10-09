/********************************* Class Source Code ***************************/
/**
\package  OADI - 
\class    ODataSourceHaving

\brief    


\date     $Date: 2006/07/24 21:41:16,06 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODataSourceHaving"

#include  <poadi.h>
#include  <sODataSource.hpp>
#include  <sODataSourceHaving.hpp>


/******************************************************************************/
/**
\brief  ODataSourceHaving - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  dataSource - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODataSourceHaving"

     ODataSourceHaving :: ODataSourceHaving (ODataSource dataSource )
                     :  dataSource(dataSource)
{

/*
  "ODataSourceHaving("
  + ADK_DataSoruce::Generate()
  + ")";
*/

}

/******************************************************************************/
/**
\brief  i01 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODataSourceHaving"

     ODataSourceHaving :: ODataSourceHaving ( )
                     : dataSource()
{



}

/******************************************************************************/
/**
\brief  ResetDataSource - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetDataSource"

void ODataSourceHaving :: ResetDataSource ( )
{

  dataSource.Reset();

}


