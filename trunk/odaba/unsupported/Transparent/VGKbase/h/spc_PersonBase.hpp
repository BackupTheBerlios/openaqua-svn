/********************************* Class Declaration ***************************/
/**
\package  VGKbase - 
\class    pc_PersonBase

\brief    


\date     $Date: 2006/07/18 11:36:28,31 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_PersonBase_HPP
#define   pc_PersonBase_HPP

class     pc_PersonBase;

#include  <sPropertyHandle.hpp>
class  pc_PersonBase :public PropertyHandle
{

public     :
public     :                                        char *GetEmail ( );
public     :                                             pc_PersonBase (PropertyHandle *prophdl );
};

#endif
