/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/20|14:26:45,35}|(REF)
\class    OPSynExceptHandling



\date     $Date: 2006/04/03 22:14:48,85 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPSynExceptHandling_HPP
#define   OPSynExceptHandling_HPP

class     OPSynExceptHandling;

class     BNFData;
#include  <cExecReturnCodes.h>
#include  <cVHN_Types.h>
#include  <sOPBase.hpp>
class  OPSynExceptHandling :public OPBase
{
protected  :         BNFData                                     *parm_bnf ATTR_ALIGN(4);                                    
protected  :         VHN_Types                                    exh_type;                                                  

public     :
                     BNFData                                     *get_parm_bnf() { return(parm_bnf); }
                     VHN_Types                                    get_exh_type() { return(exh_type); }
public     :                                     ExecReturnCodes Execute ( );
public     :                                     logical Initialize (int32 ini_opt );
public     :                                                             OPSynExceptHandling (OPBase *parent_node, BNFData *parm_bnf );
public     :                                                             ~OPSynExceptHandling ( );
};

#endif
