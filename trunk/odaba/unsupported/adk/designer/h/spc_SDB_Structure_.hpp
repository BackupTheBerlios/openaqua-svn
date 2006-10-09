/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    pc_SDB_Structure_

\brief    


\date     $Date: 2006/03/12 19:36:48,62 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_SDB_Structure__HPP
#define   pc_SDB_Structure__HPP

class     pc_SDB_Structure_;

#include  <cCTX_Types.h>
#include  <cPIACC.h>
#include  <sDBObjectHandle.hpp>
#include  <sPropertyHandle.hpp>
class  pc_SDB_Structure_ :public PropertyHandle
{

public     :
public     :                                     logical CheckContextClass (char *base_context, char *prjnames, CTX_Control *high_ctx );
public     :                                     logical InitContextClass (CTX_Types context_type );
public     :                                     logical InitContextClass (char *base_context );
public     :                                                             pc_SDB_Structure_ (PropertyHandle *prophdl );
public     :                                                             pc_SDB_Structure_ (DBObjectHandle &obhandle, char *extnames, PIACC accopt );
};

#endif
