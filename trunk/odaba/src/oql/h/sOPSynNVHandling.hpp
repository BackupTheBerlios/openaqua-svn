/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPSynNVHandling

\brief    


\date     $Date: 2006/03/12 19:20:12,59 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPSynNVHandling_HPP
#define   OPSynNVHandling_HPP

class     OPSynNVHandling;

class     BNFData;
#include  <cExecReturnCodes.h>
#include  <cVHN_Types.h>
#include  <sOPBase.hpp>
class  OPSynNVHandling :public OPBase
{
protected  :         BNFData                                     *parm_bnf ATTR_ALIGN(4);                                    
protected  :         VHN_Types                                    nvh_type;                                                  //

public     :
                     BNFData                                     *get_parm_bnf() { return(parm_bnf); }
                     VHN_Types                                    get_nvh_type() { return(nvh_type); }
public     :                                     ExecReturnCodes Execute ( );
public     :                                     logical Initialize (int32 ini_opt );
public     :                                                             OPSynNVHandling (OPBase *parent_node, BNFData *parm_bnf );
public     :                                                             ~OPSynNVHandling ( );
};

#endif
