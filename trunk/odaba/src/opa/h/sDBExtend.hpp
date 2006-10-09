/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    DBExtend

\brief    Database extent
          The  internal  presentation  of  a  database extent is a picture of an
          external  extent  definition.  It  can  be used for providing internal
          extent  definitions  while  running  an  application. You may also use
          DBExtent  constructors for reading external extent definition into the
          internal presentation.
          fmcbvirt - indicates transient (osi) extent.

\date     $Date: 2006/06/05 13:02:59,39 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBExtend_HPP
#define   DBExtend_HPP

class     DBExtend;

#include  <sDLL.h>
class     DBExtend;
class     ACObject;
class     DBIndex;
class     DBStructDef;
class     Dictionary;
class     ENUM_Value;
class     ENUM_ValueList;
class     LACObject;
class     SDB_CSEntry;
class     SDB_Extend;
class     SDB_Reference;
class     SDB_ViewExtent;
class     StructDef;
class     smcb;
#include  <cSDB_AT.h>
#include  <sDBExtend.hpp>
#include  <sDBFieldDef.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTypeKey.hpp>
#pragma pack(8)

class  DBExtend :public DBFieldDef
{
public     :         TypeKey                                      type_key;                                                  // 
protected  :         DLL(DBExtend)                               *base_extend;                                               // 
protected  :         DLL(DBExtend)                               *derived_extends;                                           // 
protected  :         ENUM_ValueList                              *cs_values;                                                 // 
protected  :         logical                                      intersect;                                                 // 
protected  :         logical                                      union_set;                                                 // 
protected  :         logical                                      disjunct;                                                  // 
protected  :         logical                                      controlled;                                                // 
protected  :         SDB_AT                                       acctype;                                                   // 
protected  :         logical                                      copy_def;                                                  // 

public     :
                     DLL(DBExtend)                               *get_base_extend() { return(base_extend); }
                     DLL(DBExtend)                               *get_derived_extends() { return(derived_extends); }
                     ENUM_ValueList                              *get_cs_values() { return(cs_values); }
public     :                                        logical AddEnumValue (ENUM_Value *csentry );
public     :                  OPAImpExp                  DBExtend (DBFieldDef *fielddef, char *extnames );
public     :                  OPAImpExp                  DBExtend ( );
public     :                  OPAImpExp                  DBExtend (PropertyHandle &ph, Dictionary *dictptr, DBStructDef *dbstrdef, DBExtend *baseext );
public     :                  OPAImpExp                  DBExtend (Dictionary *dictptr, SDB_Reference *dbrptr, DBStructDef *dbstrdef, logical disjopt=NO, logical unionopt=NO, logical intersopt=NO, logical contr_opt=NO );
public     :                  OPAImpExp                  DBExtend (PropertyHandle &ph, Dictionary *dictptr, DBStructDef *dbstrdef );
public     :                  OPAImpExp                  DBExtend (Dictionary *dictptr, DBStructDef *dbstrdef, PropertyHandle &ph );
public     :                  OPAImpExp                  DBExtend (DBExtend &db_ext_ref, char *extnames );
public     :                  OPAImpExp                  DBExtend (Dictionary *dictptr, PropertyHandle *cs_ph, DBStructDef *dbstrdef );
public     :                  OPAImpExp                  DBExtend (Dictionary *dictptr, char *base_type, ENUM_Value **value_list, DBStructDef *dbstrdef, int32 count );
public     :                  OPAImpExp             DBExtend *GetBaseExtent (int16 extent_pos );
public     :                  OPAImpExp             DBExtend *GetBaseExtent (char *extnames );
public     :                  OPAImpExp             DBExtend *GetDerivedExtent (int16 extent_pos );
public     :                  OPAImpExp             DBExtend *GetDerivedExtent (char *extnames );
public     :                                        int16 GetMainBase (ACObject *obhandle );
public     :                                        TypeKey &GetNameKey ( );
public     :                                        logical HasValues ( );
public     :                                        void InitEnumExtent (Dictionary *dictptr, DBStructDef *dbstrdef, char *strnames, int32 nsid );
public     :                  OPAImpExp             logical IsTempExtent (LACObject *lobhandle );
public     :                                        logical SetValueList (Dictionary *dictionary, ENUM_ValueList *vlist );
public     :                  OPAImpExp             void SetupNameKey ( );
public     :                  OPAImpExp             SDB_AT get_acctype ( );
public     :                  OPAImpExp             logical get_disjunct ( );
public     :                  OPAImpExp             logical get_intersect ( );
public     :                  OPAImpExp             logical get_union_set ( );
public     :                                        void set_acctype (SDB_AT acctype );
public     :                  OPAImpExp             void set_disjunct (logical disjopt=NO );
public     :                  OPAImpExp             void set_intersect (logical intersopt=NO );
public     :                  OPAImpExp             void set_union_set (logical unionopt=NO );
public     :                  OPAImpExp                  ~DBExtend ( );
};

#pragma pack()
#endif
