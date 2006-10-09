/********************************* Class Declaration ***************************/
/**
\package  FunctionalModel - 
\class    pc_ODC_PFunction

\brief    


\date     $Date: 2006/06/03 14:32:20,09 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ODC_PFunction_HPP
#define   pc_ODC_PFunction_HPP

class     pc_ODC_PFunction;

class     PropertyHandle;
#include  <sNString.hpp>
#include  <spc_SDB_Member.hpp>
class  pc_ODC_PFunction :public pc_SDB_Member
{

public     :
public     :                                        logical AssociateRetval (char *names );
public     :                                        char *DataTypeCString (NString &nstring );
public     :                                        char *FunctionTypeCOMString (NString &nstring, logical prototyp, logical put_opt, logical get_opt );
public     :                                        char *FunctionTypeCPPString (NString &nstring, logical prototyp );
public     :                                        char *FunctionTypeCString (NString &nstring, logical prototyp );
public     :                                        char *GetCIFunctionName (NString &nstring );
public     :                                        char *GetCIReturnValue (NString &nstring );
public     :                                        char *GetCITypePreafix (NString &nstring );
public     :                                        PropertyHandle *GetExecutable ( );
public     :                                        PropertyHandle *GetImpClass (logical pos_opt );
public     :                                        logical HasActions ( );
public     :                                        logical HasExpressions (logical only_opt );
public     :                                        logical HasFunction (char *propnames );
public     :                                        logical HasIFFunctions (char *if_imp_praefix );
public     :                                        logical InitRetval ( );
public     :                                        logical IsAction ( );
public     :                                        logical IsCIType ( );
public     :                                        logical IsConst ( );
public     :                                        logical IsConstructor ( );
public     :                                        logical IsDestructor ( );
public     :                                        logical IsExpression ( );
public     :                                        logical IsIFFunction (char *if_imp_praefix );
public     :                                        logical SetLineCount (int32 linecnt );
public     :                                             pc_ODC_PFunction (PropertyHandle *prophdl );
};

#endif
