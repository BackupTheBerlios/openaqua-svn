/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBIndex

\brief    


\date     $Date: 2006/03/12 19:17:06,32 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBIndex"

#include  <popa7.h>
#include  <cExtInstTypes.h>
#include  <sDBFieldDef.hpp>
#include  <sSDB_Index.hpp>
#include  <skcb.hpp>
#include  <sDBIndex.hpp>


/******************************************************************************/
/**
\brief  DBIndex - 


-------------------------------------------------------------------------------
\brief i0


\param  kcbptr -
\param  uniopt -
\param  tempopt -
\param  caseopt -
\param  empopt -
\param  maxcnt -
\param  settyp -
\param  idkey_opt -
\param  orgtype_w -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBIndex"

                        DBIndex :: DBIndex (kcb *kcbptr, logical uniopt, logical tempopt, logical caseopt, logical empopt, int32 maxcnt, SDB_SET settyp, logical idkey_opt, int8 orgtype_w )
                     : sts(),
  key_definition(kcbptr),
  field_definition(NULL), 
  org_type(orgtype_w),
  unique(uniopt), 
  temporary(tempopt), 
  case_sensitive(caseopt), 
  generic(NO), 
  no_empty(empopt), 
  set_type(settyp), 
  max_count(maxcnt)


{

  set_keyname(NULL);
  
  if ( kcbptr || !idkey_opt )
    stssfil();

}

/******************************************************************************/
/**
\brief i03


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBIndex"

                        DBIndex :: DBIndex ( )
                     : sts (),
  key_definition(NULL),
  field_definition(NULL),
  org_type(UNDEF),
  unique(NO),
  temporary(NO),
  case_sensitive(NO),
  generic(NO),
  no_empty(NO),
  max_count(AUTO),
  set_type(SET_undefined)


{

  set_keyname(NULL);


}

/******************************************************************************/
/**
\brief i04


\param  key_names -
\param  uniopt -
\param  tempopt -
\param  caseopt -
\param  empopt -
\param  maxcnt -
\param  settyp -
\param  idkey_opt -
\param  orgtype_w -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBIndex"

                        DBIndex :: DBIndex (char *key_names, logical uniopt, logical tempopt, logical caseopt, logical empopt, int32 maxcnt, SDB_SET settyp, logical idkey_opt, int8 orgtype_w )
                     : sts(),
  key_definition(NULL),
  field_definition(NULL), 
  org_type(orgtype_w),
  unique(uniopt), 
  temporary(tempopt), 
  case_sensitive(caseopt), 
  generic(NO), 
  no_empty(empopt), 
  set_type(settyp), 
  max_count(maxcnt)


{

  set_keyname(key_names);

}

/******************************************************************************/
/**
\brief i05


\param  kcbptr -
\param  dbfield_ptr - Property definition
\param  ph -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBIndex"

                        DBIndex :: DBIndex (kcb *kcbptr, DBFieldDef *dbfield_ptr, PropertyHandle &ph )
                     : sts(),
  key_definition(kcbptr),
  field_definition(dbfield_ptr),
  org_type(UNDEF),
  unique(ph.IsTrue("skdunique")),
  temporary(ph.IsTrue("skdtemp")),
  case_sensitive(ph.IsTrue("case_sensitive")),
  generic(kcbptr && kcbptr->get_kcbgfmcb()), 
  no_empty(ph.IsTrue("no_empty")),
  set_type((SDB_SET)ph.GetInt("skdtype")),
  max_count(ph.GetInt("skdmax"))
{

  set_keyname(NULL);
  stssfil();

}

/******************************************************************************/
/**
\brief i1


\param  kcbptr -
\param  dbfield_ptr - Property definition
\param  sdbindx -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBIndex"

                        DBIndex :: DBIndex (kcb *kcbptr, DBFieldDef *dbfield_ptr, SDB_Index *sdbindx )
                     : sts(),
  key_definition(kcbptr),
  field_definition(dbfield_ptr),
  org_type(UNDEF),
  unique(sdbindx->get_skdunique()),
  temporary(sdbindx->get_skdtemp()),
  case_sensitive(sdbindx->get_case_sensitive()),
  generic(kcbptr && kcbptr->get_kcbgfmcb()), 
  no_empty(sdbindx->get_no_empty()),
  set_type(sdbindx->get_skdtype()),
  max_count(sdbindx->get_skdmax())
{

  set_keyname(NULL);
  stssfil();

}

/******************************************************************************/
/**
\brief i2


\param  index_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBIndex"

                        DBIndex :: DBIndex (DBIndex &index_ref )
                     : sts(),
  key_definition(index_ref.get_key_def()),
  field_definition(NULL),
  org_type(index_ref.get_org_type()),
  unique(index_ref.get_unique()),
  temporary(index_ref.get_temporary()),
  case_sensitive(index_ref.get_case_sensitive()),
  generic(index_ref.get_generic()),
  no_empty(index_ref.get_no_empty()),
  max_count(index_ref.get_max_count()),
  set_type(index_ref.get_set_type())
{

  set_keyname(NULL);
  *(sts *)this = index_ref;

}

/******************************************************************************/
/**
\brief  GetKeyName - 


\return keyname -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeyName"

const char *DBIndex :: GetKeyName ( )
{

  return ( this && key_definition ? key_definition->scbsmcb->smcbname :
                                    "                                        "  );

}

/******************************************************************************/
/**
\brief  GetKeyNum - 


\return keynum -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeyNum"

int16 DBIndex :: GetKeyNum ( )
{

  return ( key_definition ? key_definition->get_key_num() : UNDEF );


}

/******************************************************************************/
/**
\brief  GetMaxCount - 


\return maxcnt -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMaxCount"

int32 DBIndex :: GetMaxCount ( )
{
  int32     elen;
  if ( field_definition && field_definition->fmcbdim == 1 || org_type == R_REFS || org_type == R_REFP )
    max_count = 1;
  else
  {
    elen = key_definition ? key_definition->kcbklng()+4 : 4;
    if ( set_type == SET_undefined )
    {
      if ( org_type )
      {
        switch ( org_type )   
        {
          case  IDB_ICBE : set_type = SET_LARG;
                           break;
          case  IDB_MVLG :
          case  IDB_MVLD : set_type = SET_SOME;
                           break;
          default        : set_type = SET_SMAL;
        }
      }
      else
      {
        set_type = SET_LARG;
//        if ( field_definition->fmcbbyte * field_definition->fmcbdim < 10000 )
//          set_type = SET_SOME;
//        else
          if ( !field_definition || elen * field_definition->fmcbdim < 32000 )
            set_type = SET_SMAL;
      }
    }
    if ( key_definition )
      switch ( set_type )
      {
        case SET_SOME      : max_count = 32000/field_definition->fmcbbyte;
                             break;
        case SET_SMAL      : max_count = 32000/(key_definition->kcbklng()+4);
                             break;
        case SET_LARG      : max_count = 2000000000;
        default            : ;
      }
    else
      max_count = 8000;
  }
  return(max_count);
}

/******************************************************************************/
/**
\brief  GetOrgTyp - 


\return otyp -

\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOrgTyp"

char DBIndex :: GetOrgTyp (logical pif )
{
  char      otyp = UNDEF;

BEGINSEQ
  if ( otyp = org_type )                             LEAVESEQ
    
  if ( !max_count ) // ist hier immer wahr, da Angabe in der Definition nicht möglich
    GetMaxCount();

  if ( max_count == 1 )
  {
    otyp = R_REFP;
    if ( field_definition->get_update() )
      otyp = R_REFS;
    LEAVESEQ
  }
  
  if ( !key_definition )
    otyp = field_definition->get_clst_table() && !pif ? IDB_MVLD : IDB_MVLP;
  else  
  {
    if ( generic )
      otyp = IDB_MVLG;
    else
      switch ( set_type )
      {
        case SET_LARG : otyp = IDB_ICBE;
                        break;
        case SET_SMAL : 
        default       : otyp = field_definition->get_clst_table() && !pif ? IDB_MVLD : 
                                                               (unique ? IDB_MVLI : IDB_MVLN);
      }
  }  

ENDSEQ
  return(otyp);

}

/******************************************************************************/
/**
\brief  IsTransient - 


\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsTransient"

logical DBIndex :: IsTransient ( )
{

  return ( temporary && set_type != SET_LARG ? YES : NO  );

}

/******************************************************************************/
/**
\brief  SetBaseStructOrgType - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBaseStructOrgType"

void DBIndex :: SetBaseStructOrgType ( )
{

  org_type = R_REFP;     // refx für baseStructures

}

/******************************************************************************/
/**
\brief  SetKCB - 



\param  kcbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetKCB"

void DBIndex :: SetKCB (kcb *kcbptr )
{

  key_definition = kcbptr;

  if ( kcbptr )
    stssfil();

}

/******************************************************************************/
/**
\brief  Setup - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

logical DBIndex :: Setup ( )
{
  kcb                    *kcbptr = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( key_definition )                              LEAVESEQ
    
  if ( keyname && *keyname > ' ' )
  {
    if ( !(kcbptr = field_definition->fmcbsmcb->GetKCB(keyname)) )
      kcbptr = new kcb(keyname,field_definition->fmcbsmcb);
    SetKCB(kcbptr);
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupIndexDef - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupIndexDef"

void DBIndex :: SetupIndexDef ( )
{

  if ( !stscfil() )
    if ( field_definition )
    {
      key_definition = field_definition->fmcbsmcb->smcbidky;  
      stssfil();
    }
  
  generic = key_definition && key_definition->get_kcbgfmcb();
  
  


}

/******************************************************************************/
/**
\brief  get_field_def - 


\return fielddef - Internal field defintion

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_field_def"

DBFieldDef *DBIndex :: get_field_def ( )
{


  return(field_definition);
}

/******************************************************************************/
/**
\brief  get_generic - 


\return generic -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_generic"

logical DBIndex :: get_generic ( )
{


  return(generic);
}

/******************************************************************************/
/**
\brief  get_key_def - 


\return kcbptr -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_key_def"

kcb *DBIndex :: get_key_def ( )
{


  return(key_definition);
}

/******************************************************************************/
/**
\brief  get_no_empty - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_no_empty"

logical DBIndex :: get_no_empty ( )
{


  return(no_empty);
}

/******************************************************************************/
/**
\brief  get_temporary - 


\return temporary -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_temporary"

logical DBIndex :: get_temporary ( )
{


  return(temporary);
}

/******************************************************************************/
/**
\brief  get_unique - 


\return unique

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_unique"

logical DBIndex :: get_unique ( )
{


  return(unique);
}

/******************************************************************************/
/**
\brief  set_keyname - 



\param  keynames -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_keyname"

void DBIndex :: set_keyname (char *keynames )
{

  if ( keynames && *keynames > ' ' )
    gvtxstb(keyname,keynames,ID_SIZE);
  else
    memset(keyname,' ',ID_SIZE);


}

/******************************************************************************/
/**
\brief  set_temporary - 



\param  temp_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_temporary"

void DBIndex :: set_temporary (logical temp_opt )
{

  temporary = temp_opt;

}


