/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    cFieldTable

\brief    


\date     $Date: 2006/03/12 19:36:23,81 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cFieldTable_HPP
#define   cFieldTable_HPP

class     cFieldTable;

class  cFieldTable :public CTX_Control
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     :                                     logical SetDataSource (PropertyHandle *prophdl );
public     :                                                             cFieldTable ( );
public     :                                                             ~cFieldTable ( );
};

#endif
