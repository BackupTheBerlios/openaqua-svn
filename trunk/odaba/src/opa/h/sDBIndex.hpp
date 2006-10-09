/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBIndex

\brief    


\date     $Date: 2006/03/12 19:12:58,15 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBIndex_HPP
#define   DBIndex_HPP

class     DBIndex;

class     DBFieldDef;
class     SDB_Index;
class     kcb;
#include  <cPIACC.h>
#include  <cSDB_SET.h>
#include  <sDBIndex.hpp>
#include  <ssts.hpp>
#pragma pack(8)

class  DBIndex :public sts
{
protected  :         char                                         keyname[40] ATTR_ALIGN(4);                                 //
protected  :         kcb                                         *key_definition;                                            //
protected  :         DBFieldDef                                  *field_definition;                                          //
protected  :         int16                                        org_type;                                                  //
protected  :         logical                                      unique;                                                    //
protected  :         logical                                      temporary;                                                 //
protected  :         logical                                      case_sensitive;                                            //
protected  :         logical                                      generic;                                                   //
protected  :         logical                                      no_empty;                                                  //
protected  :         int32                                        max_count;                                                 //
protected  :         SDB_SET                                      set_type;                                                  //

public     :
                     int16                                        get_org_type() { return(org_type); }
                     logical                                      get_case_sensitive() { return(case_sensitive); }
                     int32                                        get_max_count() { return(max_count); }
                     SDB_SET                                      get_set_type() { return(set_type); }
public     :                                                             DBIndex (kcb *kcbptr, logical uniopt, logical tempopt, logical caseopt, logical empopt, int32 maxcnt, SDB_SET settyp, logical idkey_opt, int8 orgtype_w=UNDEF );
public     :                                                             DBIndex ( );
public     :                                                             DBIndex (char *key_names, logical uniopt, logical tempopt, logical caseopt, logical empopt, int32 maxcnt, SDB_SET settyp, logical idkey_opt, int8 orgtype_w=UNDEF );
public     :                                                             DBIndex (kcb *kcbptr, DBFieldDef *dbfield_ptr, PropertyHandle &ph );
public     :                                                             DBIndex (kcb *kcbptr, DBFieldDef *dbfield_ptr, SDB_Index *sdbindx );
public     :                                                             DBIndex (DBIndex &index_ref );
public     :         opa7ImpExp                  const char *GetKeyName ( );
public     :                                     int16 GetKeyNum ( );
public     :         opa7ImpExp                  int32 GetMaxCount ( );
public     :         opa7ImpExp                  char GetOrgTyp (logical pif );
public     :                                     logical IsTransient ( );
public     :                                     void SetBaseStructOrgType ( );
public     :                                     void SetKCB (kcb *kcbptr );
public     :                                     logical Setup ( );
public     :                                     void SetupIndexDef ( );
public     :         opa7ImpExp                  DBFieldDef *get_field_def ( );
public     :         opa7ImpExp                  logical get_generic ( );
public     :         opa7ImpExp                  kcb *get_key_def ( );
public     :         opa7ImpExp                  logical get_no_empty ( );
public     :         opa7ImpExp                  logical get_temporary ( );
public     :         opa7ImpExp                  logical get_unique ( );
public     :                                     void set_keyname (char *keynames=NULL );
public     :                                     void set_temporary (logical temp_opt );
public     :                                     void set_field_def (DBFieldDef *flddefptr ){

  field_definition = flddefptr;

}

public     :                                     void set_generic (logical gen_opt ){

  generic = gen_opt;

}

};

#pragma pack()
#endif
