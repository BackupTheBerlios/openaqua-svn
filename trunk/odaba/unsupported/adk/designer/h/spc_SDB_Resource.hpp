/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    pc_SDB_Resource

\brief    


\date     $Date: 2006/03/12 19:36:48,43 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_SDB_Resource_HPP
#define   pc_SDB_Resource_HPP

class     pc_SDB_Resource;

#include  <sPropertyHandle.hpp>
class  pc_SDB_Resource :public PropertyHandle
{

public     :
public     :                                     char *GetContextType ( );
public     :                                                             pc_SDB_Resource (PropertyHandle *prophdl );
};

#endif
