/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/15|18:19:36,78}|(REF)
\class    ACHierNode

\brief    


\date     $Date: 2006/04/03 14:15:00,04 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACHierNode_HPP
#define   ACHierNode_HPP

class     ACHierNode;

class     ACExtend;
class     ACObject;
class     PropertyHandle;
#include  <cPIACC.h>
#include  <sACTopNode.hpp>
#pragma pack(8)

class  ACHierNode :public ACTopNode
{
protected  :         PropertyHandle                             **nodelist ATTR_ALIGN(4);                                    // 
protected  :         int16                                        pib_count;                                                 // 

public     :
                     PropertyHandle                             **get_nodelist() { return(nodelist); }
                     int16                                        get_pib_count() { return(pib_count); }
public     :                                                             ACHierNode (ACExtend *sysnode, PIACC accopt );
public     : virtual                             void *Add (int32 lindx0, logical global_add=NO );
public     : virtual                             void *Add (int32 lindx0, char *skey, char *idkey, void *initinst=NULL );
public     : virtual                             logical Delete (int32 lindx0, logical chknode=YES, logical del_dep=YES, logical del_inst=NO );
public     : virtual                             void *Get (int32 indx0, logical chknode=YES );
public     : virtual                             void *Get (char *skey, logical chknode=YES );
public     : virtual                             int16 GetMainBase ( );
public     :                                     logical InitReference ( );
public     :                                     logical SetWrite ( );
public     : virtual                                                     ~ACHierNode ( );
};

#pragma pack()
#endif
