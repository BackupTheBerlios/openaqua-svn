/********************************* Class Declaration ***************************/
/**
\package  AdkCtxi
\class    pc0_SDB_Member



\date     $Date: 2006/05/23 13:04:35,29 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_SDB_Member_HPP
#define   pc0_SDB_Member_HPP

class     pc0_SDB_Member;

#include  <sPropertyHandle.hpp>
class  pc0_SDB_Member :public PropertyHandle
{

public     :
public     :                                        PropertyHandle *GetMember (char *propnames );
public     :                                        logical IsMultipleRef ( );
public     :                                             pc0_SDB_Member (PropertyHandle *prophdl );
};

#endif
