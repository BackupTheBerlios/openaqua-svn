/********************************* Class Declaration ***************************/
/**
\package  OADI - 
\class    ODataSourceHaving

\brief    


\date     $Date: 2006/07/24 21:41:14,75 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODataSourceHaving_HPP
#define   ODataSourceHaving_HPP

class     ODataSourceHaving;

#include  <sODataSource.hpp>
#pragma pack(4)

class  ODataSourceHaving
{
protected  :         ODataSource                                  dataSource;                                                // 

public     :
                     ODataSource                                 &get_dataSource() { return(dataSource); }
public     :                                             ODataSourceHaving (ODataSource dataSource );
public     :                                             ODataSourceHaving ( );
public     :                                        void ResetDataSource ( );
public     :                                        ODataSource *DataSource ( ){

  return ( &dataSource );

}

};

#pragma pack()
#endif
