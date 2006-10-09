/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc1_SDB_Resource



\date     $Date: 2006/05/23 13:11:51,00 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc1_SDB_Resource_HPP
#define   pc1_SDB_Resource_HPP

class     pc1_SDB_Resource;

#include  <sPropertyHandle.hpp>
class  pc1_SDB_Resource :public PropertyHandle
{

public     :
public     :                                        char *GetContextType ( );
public     :                                             pc1_SDB_Resource (PropertyHandle *prophdl );
};

#endif
