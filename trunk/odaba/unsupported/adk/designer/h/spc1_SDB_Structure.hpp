/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc1_SDB_Structure



\date     $Date: 2006/05/23 12:57:47,28 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc1_SDB_Structure_HPP
#define   pc1_SDB_Structure_HPP

class     pc1_SDB_Structure;

#include  <sDBObjectHandle.hpp>
#include  <sPropertyHandle.hpp>
class  pc1_SDB_Structure :public PropertyHandle
{

public     :
public     :                                        logical CheckContextClass (char *base_context, char *prjnames, CTX_Control *high_ctx );
public     :                                        logical InitContextClass (CTX_Types context_type );
public     :                                        logical InitContextClass (char *base_context );
public     :                                             pc1_SDB_Structure (PropertyHandle *prophdl );
public     :                                             pc1_SDB_Structure (DBObjectHandle &obhandle, char *extnames, PIACC accopt );
};

#endif
