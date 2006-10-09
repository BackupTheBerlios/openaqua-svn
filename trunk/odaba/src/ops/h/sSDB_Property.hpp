/********************************* Class Declaration ***************************/
/**
\package  OPS
\class    SDB_Property

\brief    Property
          Properties   of   a   structure   definition   define base structures,
          attributes, references and relationships for a structure.

\date     $Date: 2006/05/11 16:08:56,37 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_Property_HPP
#define   SDB_Property_HPP

class     SDB_Property;

class     DBFieldDef;
#include  <cTYP_TYPES.h>
#include  <sCAU_Causality.hpp>
#include  <sDatabaseHandle.hpp>
#include  <sSDB_Member.hpp>
#include  <sSDB_Property.hpp>
#pragma pack(8)

class  SDB_Property :public SDB_Member,
public CAU_Causality
{
protected  :         logical                                      ddetrans;                                                  // Transient property
protected  :         logical                                      shared;                                                    // Shared collection
protected  :         uint8                                        version;                                                   // Member version

public     :
                     logical                                      get_ddetrans() { return(ddetrans); }
                     logical                                      get_shared() { return(shared); }
                     uint8                                        get_version() { return(version); }
public     :                  OPSImpExp             FieldDef *CreateFieldDef (FieldDef *fieldptr );
public     :                  OPSImpExp             logical Fill (DatabaseHandle &dbhandle, char *propnames, char *proptypes );
public     :                                        logical GetAlignInfo (char *propname, int16 &size_info, int16 &offset_info );
public     :                  OPSImpExp             void Initialize ( );
public     :                  OPSImpExp             void InitializeBase (char *gentype, char privileg );
public     :                  OPSImpExp                  SDB_Property (SDB_Member &dbmref, logical transopt, uint8 ver );
public     :                  OPSImpExp                  SDB_Property ( );
public     :                  OPSImpExp                  ~SDB_Property ( );
public     :                  OPSImpExp             void set_ddetrans (logical trans_opt ){
  ddetrans = trans_opt;
}

};

#pragma pack()
#endif
