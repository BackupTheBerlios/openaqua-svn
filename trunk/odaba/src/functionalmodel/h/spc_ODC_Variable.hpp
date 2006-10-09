/********************************* Class Declaration ***************************/
/**
\package  FunctionalModel
\class    pc_ODC_Variable



\date     $Date: 2006/04/25 14:24:34,06 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ODC_Variable_HPP
#define   pc_ODC_Variable_HPP

class     pc_ODC_Variable;

class     PropertyHandle;
#include  <sNString.hpp>
#include  <spc_SDB_Member.hpp>
class  pc_ODC_Variable :public pc_SDB_Member
{

public     :
public     :                                     char *DataTypeCString (NString &nstring );
public     :                                     logical Fill (char *propnames, char *proptypes );
public     :                                     char *GetCastType (NString &nstring );
public     :                                     char *GetParmCallList (NString &nstring );
public     :                                     char *GetParmList (NString &nstring, logical com_opt, logical prototyp );
public     :                                     char *ParmTypeCOMString (NString &nstring, logical prototyp, logical retvar_opt );
public     :                                     char *ParmTypeCString (NString &nstring, logical prototyp );
public     :                                                             pc_ODC_Variable (PropertyHandle *prophdl );
};

#endif
