/********************************* Class Source Code ***************************/
/**
\package  FunctionalModel - 
\class    pc_SDB_TypeRef_fm

\brief    


\date     $Date: 2006/06/03 20:29:21,26 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_SDB_TypeRef_fm"

#include  <pfmodel.h>
#include  <sSDB_Member.hpp>
#include  <spc_ODC_ImpClass.hpp>
#include  <spc_SDB_TypeRef_fm.hpp>


/******************************************************************************/
/**
\brief  ProvideReference - 


\return term - 

\param  member_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideReference"

logical pc_SDB_TypeRef_fm :: ProvideReference (PropertyHandle *member_ph )
{
  PropertyHandle    *ddetype         = member_ph->GPH("ddetype");
  PropertyHandle    *ddegent         = member_ph->GPH("ddegent");
  PropertyHandle    *reference_level = member_ph->GPH("reference_level");
  PropertyHandle     string_key_ph("");
  int16              itype           = UNDEF;
  char               stype[ID_SIZE+1];
  char              *stype_str       = NULL;
  logical            term            = NO;

BEGINSEQ
  if ( !member_ph->IsPositioned() )                  ERROR
  
  if ( ddetype->IsEmpty() || *ddetype == "MEMO" )    LEAVESEQ

  if ( itype = GetDictionary().BaseType(ddetype->GetString()) )
  {
    if ( ddegent->IsEmpty() )                        LEAVESEQ
    if ( !(stype_str = ((SDB_Member *)member_ph->Get().GetData())->GetSystemType(itype,stype)) )
                                                     SDBERR(99)
    string_key_ph += stype_str;
  }
  else
    string_key_ph += ddetype->GetString();

  string_key_ph += "|";
  string_key_ph += ddegent->GetString();
  
  Provide(string_key_ph);                             SDBCERR
  if ( NoWrite() )                                    SDBERR(99)

  SetupReference(reference_level->GetInt() > 0 ? IRL_Pointer : IRL_Member,
                 reference_level->GetInt() > 0 ? IRL_Member  : IRL_undefined,
                 YES);
  Save();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetCompRequest - 


\return term - 

\param  cmod_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCompRequest"

logical pc_SDB_TypeRef_fm :: SetCompRequest (ClassModLevel cmod_level )
{
  PropertyHandle         *owner           = GPH("owner");
  PropertyHandle         *code_level      = GPH("code_level");
  PropertyHandle         *inc_level       = GPH("inc_level");
  PropertyHandle         *owner_mod_level = NULL;
  int32                   indx0           = 0;
  logical                 term            = NO;
BEGINSEQ
  if ( GetCount() <= 0 )                             LEAVESEQ
  
  owner->SetType("ODC_ImpClass");
  owner_mod_level = owner->GPH("code_level");

  while ( Get(indx0++) )
    if ( owner->Get(FIRST_INSTANCE) && !strcmp(owner->GetCurrentType(),"ODC_ImpClass") )
    {
      pc_ODC_ImpClass  cls_pc(owner);
      if ( code_level->GetInt() > IRL_Pointer || inc_level->GetInt() > IRL_Pointer )
      {
        if ( cmod_level == CML_Intern && inc_level->GetInt() == IRL_SensiRef )
        {
          if ( owner_mod_level->GetInt() < CML_Intern )
          {
            cls_pc.SetModified(CML_Intern,NO);
            cls_pc.ResModLevel();
          }
          else
            cls_pc.SetCompileState(CPS_requested);
        }
        else
          cls_pc.SetCompileState(CPS_requested);
        cls_pc.Save(YES);
      }
      
    }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc_SDB_TypeRef_fm - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_SDB_TypeRef_fm"

     pc_SDB_TypeRef_fm :: pc_SDB_TypeRef_fm (PropertyHandle *prophdl )
                     : pc_SDB_TypeRef (prophdl)
{



}


