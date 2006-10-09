/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    cinti

\brief    


\date     $Date: 2006/03/12 19:14:07,17 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cinti_HPP
#define   cinti_HPP

class     cinti;

class     DBStructDef;
class     node;
#include  <cPIACC.h>
#include  <sbinti.hpp>
#pragma pack(8)

class  cinti :public binti
{
protected  :         uint16                                       version ATTR_ALIGN(4);                                     //

public     :
                     uint16                                       get_version() { return(version); }
public     : virtual                             logical Cancel ( );
public     :                                     logical ChangeMode (PIACC accopt );
public     :                                     logical CheckAddReference ( );
public     : virtual                             logical Close ( );
public     : virtual                             uint16 GetVersion ( );
public     : virtual                             logical IsPositioned ( );
public     : virtual                             void Reset ( );
public     :                                     logical Save (logical switchopt, logical overwrite=NO, logical refresh_opt=NO );
public     :                                     logical SetupInst (int32 lindx0, int64 obj_id, uint16 version_nr=CUR_VERSION, logical active=AUTO );
public     :                                     logical SetupNewInst (int32 lindx0, int64 obj_id, logical new_inst, uint16 version_nr=CUR_VERSION );
public     :                                     logical SetupSubNodes (logical active=AUTO );
public     :                                                             cinti (node *nodeptr, DBStructDef *strdefptr, void *instptr, logical crt_opt );
public     :                                                             cinti ( );
public     :                                                             ~cinti ( );
};

#pragma pack()
#endif
