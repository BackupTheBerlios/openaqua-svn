/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    cPropertyTable

\brief    


\date     $Date: 2006/03/12 19:36:31,87 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cPropertyTable_HPP
#define   cPropertyTable_HPP

class     cPropertyTable;

class     PropertyHandle;
#include  <cPropTableMode.h>
class  cPropertyTable :public CTX_Control
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     :                                     logical Update (PropertyHandle *ph_ptr );
public     :                                                             cPropertyTable ( );
public     :                                                             ~cPropertyTable ( );
};

#endif
