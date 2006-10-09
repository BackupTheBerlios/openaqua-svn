/********************************* Class Declaration ***************************/
/**
\package  OPS - 
\class    pc_SDB_Member

\brief    


\date     $Date: 2006/06/22 18:54:54,42 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_SDB_Member_HPP
#define   pc_SDB_Member_HPP

class     pc_SDB_Member;

class     ErrorProtocol;
#include  <sPropertyHandle.hpp>
#include  <sTypeKey.hpp>
class  pc_SDB_Member :public PropertyHandle
{

public     :
public     :                                        char *BitSize (NString &nstring );
public     :                                        char *CharSize (NString &nstring );
public     :                  OPSImpExp             logical CheckType (ErrorProtocol *protocol, PropertyHandle *str_ph, PropertyHandle *cs_ph );
public     :                  OPSImpExp             char *DataTypeCOMString (NString &nstring, logical output_parm );
public     :                  OPSImpExp             char *DataTypeCString (NString &nstring, int16 align );
public     :                  OPSImpExp             logical Fill (char *propnames, char *proptypes );
public     :                  OPSImpExp             char *GetCOMSystemType (NString &nstring, int16 itype );
public     :                  OPSImpExp             char *GetCOMSystemType (NString &nstring, char *typstr );
public     :                  OPSImpExp             char *GetCOMTypeString (NString &nstring, int16 *lchange, logical keyfield=NO );
public     :                  OPSImpExp             char *GetCSystemType (NString &nstring, int16 itype );
public     :                  OPSImpExp             char *GetCTypeString (NString &nstring, int16 *lchange, logical keyfield=NO );
public     :                  OPSImpExp             char *GetCTypeString (char *string, int16 leng, int16 *lchange, logical keyfield=NO );
public     :                  OPSImpExp             char *GetRefLevelString (NString &nstring );
public     :                  OPSImpExp             char *GetScopedType (NString &nstring );
public     :                  OPSImpExp             char *GetScopedType ( );
public     :                  OPSImpExp             TypeKey &GetTypeKey (TypeKey &tkey );
public     :                  OPSImpExp             logical Initialize ( );
public     :                  OPSImpExp             char *KeyTypeCString (NString &nstring, int16 align );
public     :                  OPSImpExp             char *ParmTypeCString (NString &nstring, int16 align );
public     :                  OPSImpExp             logical SetDefault ( );
public     :                                        logical SetProperty (char *propnames, char *string, ErrorProtocol *protocol, char *remarks );
public     :                                        logical Store (DBFieldDef *dbflddef );
public     :                  OPSImpExp                  pc_SDB_Member (PropertyHandle *prophdl );
};

#endif
