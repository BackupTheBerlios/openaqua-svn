/********************************* Class Declaration ***************************/
/**
\package  OPS
\class    pc_SDB_Type



\date     $Date: 2006/05/14 13:13:48,85 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_SDB_Type_HPP
#define   pc_SDB_Type_HPP

class     pc_SDB_Type;

#include  <sPropertyHandle.hpp>
#include  <sTypeKey.hpp>
class  pc_SDB_Type :public PropertyHandle
{

public     :
public     :                  OPSImpExp             logical GetTypeInfo (char *scoped_name, int32 *pstyp, int32 *pityp, int32 *patyp, char *idkeyn );
public     :                  OPSImpExp             logical GetTypeInfo (int32 *pstyp, int32 *pityp, int32 *patyp, char *idkeyn );
public     :                  OPSImpExp             TypeKey &GetTypeKey (TypeKey &tkey );
public     :                  OPSImpExp             logical IsBaseType ( );
public     :                  OPSImpExp             logical IsPersistent (int32 *pityp );
public     :                  OPSImpExp             char *ScopedName (char *string, int16 leng );
public     :                  OPSImpExp                  pc_SDB_Type (PropertyHandle *prophdl );
public     :                  OPSImpExp                  pc_SDB_Type (DatabaseHandle &dbhandle, PIACC accopt_w=PI_Read );
public     :                  OPSImpExp                  pc_SDB_Type (DatabaseHandle &dbhandle, char *strnames, PIACC accopt_w=PI_Read );
};

#endif
