/********************************* Class Declaration ***************************/
/**
\package  FunctionalModel
\class    pc_ODC_FunctImp



\date     $Date: 2006/04/25 14:34:33,50 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ODC_FunctImp_HPP
#define   pc_ODC_FunctImp_HPP

class     pc_ODC_FunctImp;

#include  <cProgramLanguage.h>
#include  <sNString.hpp>
#include  <sPropertyHandle.hpp>
class  pc_ODC_FunctImp :public PropertyHandle
{

public     :
public     :                                     char *CI_Headline (logical prototyp );
public     :                                     char *CI_Headline (NString &nstring, logical prototyp );
public     :                                     char *CPP_Headline (logical prototyp );
public     :                                     char *CPP_Headline (NString &nstring, logical prototyp );
public     :                                     char *CPP_Headline_COM (logical prototyp );
public     :                                     char *CPP_Headline_COM (NString &nstring, logical prototyp );
public     :                                     char *CPP_Headline_IF (logical prototyp );
public     :                                     char *CPP_Headline_IF (NString &nstring, logical prototyp );
public     :                                     char *C_Headline (logical prototyp );
public     :                                     char *C_Headline (NString &nstring, logical prototyp );
public     :                                     char *GetCIFunctionName (NString &nstring );
public     :                                     char *GetCIReturnValue (NString &nstring );
public     :                                     char *GetCOMParmList (NString &nstring, logical prototyp, logical par_opt_w=YES );
public     :                                     char *GetCParmList (NString &nstring, logical prototyp, logical par_opt_w=YES );
public     :                                     PropertyHandle *GetPFunction (logical pos_opt );
public     :                                     char *GetParmCallList (NString &nstring );
public     :                                     ProgramLanguage GetProgramLanguage ( );
public     :                                     logical HasIFImplement (char *if_imp_praefix );
public     :                                     char *Headline (logical prototyp );
public     :                                     char *Headline (NString &nstring, logical prototyp );
public     :                                     logical IsIFImplement (char *if_imp_praefix );
public     :                                     logical Merge (PropertyHandle *srce_ph, logical replace, logical replace_parms, logical replace_sys );
public     :                                     logical MergeCode (PropertyHandle *targ_ph, PropertyHandle *srce_ph, logical replace );
public     :                                     logical SetLineCount (char *propnames, int16 line_cnt );
public     :                                     logical SetupCodeBlockOptions ( );
public     :                                     logical SetupCodeBlocks (char glob_opt, char *glob_ident );
public     :                                     logical SetupCodeBlocksFromGlobal (char glob_opt, char *glob_ident );
public     :                                     logical SetupInitCode (PropertyHandle *class_ph, logical clear_opt );
public     :                                     logical SetupInitCode (NString &nstring, PropertyHandle *prophdl, logical &first_ref, logical init_opt );
public     :                                                             pc_ODC_FunctImp (PropertyHandle *prophdl );
};

#endif
