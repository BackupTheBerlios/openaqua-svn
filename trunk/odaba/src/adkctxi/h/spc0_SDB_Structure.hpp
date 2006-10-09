/********************************* Class Declaration ***************************/
/**
\package  AdkCtxi
\class    pc0_SDB_Structure



\date     $Date: 2006/05/23 13:04:42,26 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_SDB_Structure_HPP
#define   pc0_SDB_Structure_HPP

class     pc0_SDB_Structure;

#include  <sDBObjectHandle.hpp>
#include  <sPropertyHandle.hpp>
class  pc0_SDB_Structure :public PropertyHandle
{
protected  :         PropertyHandle                               member;                                                    

public     :
                     PropertyHandle                              &get_member() { return(member); }
public     :                                        PropertyHandle *GetMember (char *propnames );
public     :                                             pc0_SDB_Structure (PropertyHandle *prophdl );
public     :                                             pc0_SDB_Structure (DBObjectHandle &obhandle, PIACC accopt );
public     :                                             pc0_SDB_Structure (PropertyHandle &prophdl_ref );
public     :                                             pc0_SDB_Structure (DBObjectHandle &obhandle, char *strnames, PIACC accopt );
};

#endif
