/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    SC_Query

\brief    


\date     $Date: 2006/03/12 19:13:51,81 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SC_Query_HPP
#define   SC_Query_HPP

class     SC_Query;

class     CS_Connection;
class     CServer;
#include  <sQueryHandle.hpp>
#include  <sSC_Handle.hpp>
#pragma pack(8)

class  SC_Query :public SC_Handle
{

public     :
public     :                                                             SC_Query (CS_Connection *cs_connection, int64 client_handle );
public     :                                                             ~SC_Query ( );
};

#pragma pack()
#endif
