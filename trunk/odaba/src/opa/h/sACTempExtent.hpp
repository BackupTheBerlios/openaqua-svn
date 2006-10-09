/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/15|18:19:36,78}|(REF)
\class    ACTempExtent

\brief    


\date     $Date: 2006/04/03 14:20:46,76 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACTempExtent_HPP
#define   ACTempExtent_HPP

class     ACTempExtent;

class     ACExtend;
class     CTX_Base;
class     DBFieldDef;
class     bnode;
class     node;
#include  <cPIACC.h>
#include  <sACReference.hpp>
#include  <sACTempExtent.hpp>
#include  <sEB_Number.hpp>
#pragma pack(8)

class  ACTempExtent :public ACReference
{
protected  :         ACExtend                                    *system_node ATTR_ALIGN(4);                                 // 
protected  :         EB_Number                                    current_id;                                                // 
protected  :         EB_Number                                    int_extref;                                                // 

public     :
                     ACExtend                                    *get_system_node() { return(system_node); }
                     EB_Number                                   &get_current_id() { return(current_id); }
                     EB_Number                                   &get_int_extref() { return(int_extref); }
public     :                                                             ACTempExtent (bnode *bnode_ptr, char *extname_w=NULL );
public     :                                                             ACTempExtent ( );
public     :                                                             ACTempExtent (ACTempExtent &actempref );
public     : virtual                             void *Add (int32 lindx0, logical global_add=NO );
public     : virtual                             logical AddGenericRef (char *fldname );
public     : virtual                             PIACC ChangeMode (PIACC accopt, char chkopt=AUTO );
public     : virtual                             logical Check (logical autoini=NO, logical acccheck=YES );
public     : virtual                             logical Close ( );
public     : virtual                             node *CreateCopyNode ( );
public     : virtual                             logical DelGenericRef (char *fldname );
public     : virtual                             logical Delete (int32 lindx0, logical chknode=YES, logical del_dep=YES, logical del_inst=NO );
public     : virtual                             node *GetExtentNode ( );
public     : virtual                             EB_Number GetGlobalID ( );
public     : virtual                             int16 GetMainBase ( );
public     : virtual                             ACExtend *GetSystemNode ( );
public     : virtual                             logical InitReference ( );
public     :                                     logical IsTempExtent ( );
public     : virtual                             logical Save (logical switchopt, logical overwrite=NO, logical chknode=YES );
public     : virtual                                                     ~ACTempExtent ( );
};

#pragma pack()
#endif
