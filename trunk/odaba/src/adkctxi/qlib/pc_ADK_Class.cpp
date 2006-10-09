/********************************* Class Source Code ***************************/
/**
\package  AdkCtxi - 
\class    pc_ADK_Class

\brief    


\date     $Date: 2006/06/19 21:16:04,17 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ADK_Class"

#include  <padkctxi.h>
#include  <sTypeKey.hpp>
#include  <spc0_SDB_ValueList.hpp>
#include  <spc_ADK_Class.hpp>


/******************************************************************************/
/**
\brief  ProvideDefaultCollectionControl - 


\return prophdl - Property handle

\param  prophdl - Property handle
\param  rhgrow - 
\param  rvgrow - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideDefaultCollectionControl"

PropertyHandle *pc_ADK_Class :: ProvideDefaultCollectionControl (PropertyHandle *prophdl, logical &rhgrow, logical &rvgrow )
{
  PropertyHandle *fc        = GPH("controls");
  char           *fc_names;
  if (prophdl->GPH("ddedim")->GetInt() == 1) 
     fc_names =  "_Single";
   else "_Multiple";
  logical         term      = NO;
BEGINSEQ
  PropertyHandle phCOLLECTION("COLLECTION");
  PropertyHandle phfc_names(fc_names);
  if ( !Provide(phCOLLECTION) )                     ERROR
  if ( !fc->Get(phfc_names) )                       ERROR
  
  if ( prophdl->GPH("ddedim")->GetInt() == 1 )
    rvgrow = NO;

/*  
  PropertyHandle   astract_class(*this);
  PropertyHandle *abstract_fc = astract_class.GPH("controls");

  if ( !astract_class.Get(PropertyHandle("COLLECTION")) )
                                                     ERROR
  if ( !abstract_fc->Get(PropertyHandle(fc_names)) ) ERROR
    
  if ( !Provide(*prophdl->GPH("ddetype")) )          ERROR
  if ( !fc->Get(PropertyHandle(fc_names)) )
  {
    fc->Copy(*abstract_fc);                          SDBCERR
  }
*/

RECOVER
  fc   = NULL;
  term = YES;
ENDSEQ
  return(fc);
}

/******************************************************************************/
/**
\brief  ProvideDefaultControl - 


\return prophdl - Property handle

\param  prophdl - Property handle
\param  rhgrow - 
\param  rvgrow - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideDefaultControl"

PropertyHandle *pc_ADK_Class :: ProvideDefaultControl (PropertyHandle *prophdl, logical &rhgrow, logical &rvgrow )
{
  PropertyHandle *fc        = GPH("controls");
  char           *meta_type = prophdl->GetCurrentType();
  char           *type      = prophdl->GPH("ddetype")->GetString();
  int32           size      = prophdl->GPH("ddesize")->GetInt();
  logical         term      = NO;
BEGINSEQ
  if ( !strcmp(meta_type,"SDB_Attribute") )
  {
    if ( !strcmp(type,"LOGICAL") || !strcmp(type,"bool") )
    {
      PropertyHandle phLOGICAL("LOGICAL");
      PropertyHandle ph_CheckBox("_CheckBox");
      if ( !Get(phLOGICAL) )                        ERROR
      if ( !fc->Get(ph_CheckBox) )                  ERROR
      rhgrow = NO;
      rvgrow = NO;
    }
    else if ( !strcmp(type,"DATE") )
    {
      PropertyHandle phDATE("DATE");
      PropertyHandle ph_Edit("_DateEdit");
      if ( !Get(phDATE) )                           ERROR
      if ( !fc->Get(ph_Edit) )                      ERROR
      rhgrow = NO;
      rvgrow = NO;
    }
    else if ( !strcmp(type,"TIME") )
    {
      PropertyHandle phTIME("TIME");
      PropertyHandle ph_Edit("_TimeEdit");
      if ( !Get(phTIME) )                           ERROR
      if ( !fc->Get(ph_Edit) )                      ERROR
      rhgrow = NO;
      rvgrow = NO;
    }
    else if ( !strcmp(type,"DATETIME") )
    {
      PropertyHandle phTIME("DATETIME");
      PropertyHandle ph_Edit("_DateTimeEdit");
      if ( !Get(phTIME) )                           ERROR
      if ( !fc->Get(ph_Edit) )                      ERROR
      rhgrow = NO;
      rvgrow = NO;
    }
    else if ( !strcmp(type,"CHAR") )
    {
      PropertyHandle phCHAR("CHAR");
      PropertyHandle phLE((char*) ( size <=  8 ? "_LineEdit08" :
                                    size <= 20 ? "_LineEdit20" :
                                    size <= 40 ? "_LineEdit40" :
                                                 "_LineEdit99"));
      if ( !Get(phCHAR) )                           ERROR
      if ( !fc->Get(phLE) )                         ERROR
      rvgrow = NO;
    }
    else if ( !strcmp(type,"CCHAR") )
    {
      PropertyHandle phCCHAR("CCHAR");
      PropertyHandle phLE((char*) (size <=  8 ? "_LineEdit08" :
                                   size <= 20 ? "_LineEdit20" :
                                   size <= 40 ? "_LineEdit40" :
                                                "_LineEdit99") );
      if ( !Get(phCCHAR) )                          ERROR
      if ( !fc->Get(phLE) )                         ERROR
      rvgrow = NO;
    }
    else if ( !strcmp(type,"STRING") )
    {
      PropertyHandle phSTRING("STRING");
      PropertyHandle phLE((char*) (size <=  8 ? "_LineEdit08" :
                                   size <= 20 ? "_LineEdit20" :
                                   size <= 40 ? "_LineEdit40" :
                                                "_LineEdit99"));
      if ( !Get(phSTRING) )                         ERROR
      if ( !fc->Get(phLE) )                         ERROR
      rvgrow = NO;
    }
    else if ( !strcmp(type,"INT") || !strcmp(type,"UCHAR") || !strcmp(type,"int") )
    {
      PropertyHandle phINT("INT");
      PropertyHandle phLE((char*) (size <= 2 ? "_LineEdit2" :
                                   size <= 4 ? "_LineEdit4" :
                                   size <= 8 ? "_LineEdit8" :
                                               "_LineEdit9"));
      if ( !Get(phINT) )                            ERROR
      if ( !fc->Get(phLE) )                         ERROR
      rhgrow = NO;
      rvgrow = NO;
    }
    else if ( !strcmp(type,"UINT") )
    {
      PropertyHandle phUINT("UINT");
      PropertyHandle phLE((char*) (size <= 2 ? "_LineEdit2" :
                                   size <= 4 ? "_LineEdit4" :
                                   size <= 8 ? "_LineEdit8" :
                                               "_LineEdit9"));
      if ( !Get(phUINT) )                           ERROR
      if ( !fc->Get(phLE) )                         ERROR
      rhgrow = NO;
      rvgrow = NO;
    }
    else if ( !strcmp(type,"REAL") )
    {
      PropertyHandle phREAL("REAL");
      PropertyHandle phLE("_LineEdit");
      if ( !Get(phREAL) )                           ERROR
      if ( !fc->Get(phLE) )                         ERROR
      rhgrow = NO;
      rvgrow = NO;
    }
    else if ( pc0_SDB_ValueList(GetObjectHandle()).IsEnumeration(prophdl) )
    {
      PropertyHandle phENUMERATION("ENUMERATION");
      PropertyHandle ph_DropCombo("_DropCombo");
      if ( !Get(phENUMERATION) )                    ERROR
      if ( !fc->Get(ph_DropCombo) )                 ERROR
      rvgrow = NO;
    }
    else
      fc = ProvideDefaultImbeddedControl(prophdl,type);
  }
  
  if ( !strcmp(meta_type,"SDB_BaseStruct") )
    fc = ProvideDefaultImbeddedControl(prophdl,type);
  
  if ( !strcmp(meta_type,"SDB_Reference")    ||
       !strcmp(meta_type,"SDB_Relationship") ||
       !strcmp(meta_type,"SDB_Extend")         )
  {
    if ( !strcmp(type,"MEMO") )
    {
      PropertyHandle phMEMO("MEMO");
      PropertyHandle phBE((char*) (size <= 512 ? "_BoxEdit512" :
                                                 "_BoxEdit999"));
      if ( !Get(phMEMO) )                           ERROR
      if ( !fc->Get(phBE) )                         ERROR
    }
    else
      fc = ProvideDefaultCollectionControl(prophdl,rhgrow,rvgrow);
  }

RECOVER
  fc   = NULL;
  term = YES;
ENDSEQ
  return(fc);
}

/******************************************************************************/
/**
\brief  ProvideDefaultImbeddedControl - 


\return prophdl - Property handle

\param  prophdl - Property handle
\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideDefaultImbeddedControl"

PropertyHandle *pc_ADK_Class :: ProvideDefaultImbeddedControl (PropertyHandle *prophdl, char *typenames )
{
  PropertyHandle *fc        = GPH("controls");
  TypeKey         tkey(GetDictionary(),typenames);
  logical         term      = NO;
BEGINSEQ
  PropertyHandle phIMBEDDED("IMBEDDED");
  PropertyHandle phedit("edit");

  if ( Get(tkey.GetKey()) && fc->Get(phedit) )      LEAVESEQ
  
  PropertyHandle   astract_class(*this);
  PropertyHandle *abstract_fc = astract_class.GPH("controls");
  if ( !astract_class.Get(phIMBEDDED) )             ERROR
  if ( !abstract_fc->Get(phedit) )                  ERROR
  if ( !Provide(*prophdl->GPH("ddetype")) )         ERROR
  if ( !fc->Get(phedit) )
  {
    fc->Copy(*abstract_fc);                          SDBCERR
  }


RECOVER
  fc   = NULL;
  term = YES;
ENDSEQ
  return(fc);
}

/******************************************************************************/
/**
\brief  ProvideDefaultTabControl - 


\return prophdl - Property handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideDefaultTabControl"

PropertyHandle *pc_ADK_Class :: ProvideDefaultTabControl ( )
{
  PropertyHandle *fc        = GPH("controls");
  logical         term      = NO;
BEGINSEQ
  PropertyHandle   astract_class(*this);
  PropertyHandle *abstract_fc = astract_class.GPH("controls");
  PropertyHandle phIMBEDDED("IMBEDDED");
  PropertyHandle phtab("tab");
  if ( !astract_class.Get(phIMBEDDED) )             ERROR
  if ( !abstract_fc->Get(phtab) )                   ERROR
    
  if ( NoWrite() )                                  ERROR
  if ( !fc->Get(phtab) )
  {
    fc->Copy(*abstract_fc);                         SDBCERR
  }
RECOVER
  fc   = NULL;
  term = YES;
ENDSEQ
  return(fc);
}

/******************************************************************************/
/**
\brief  pc_ADK_Class - Konstruktor


-------------------------------------------------------------------------------
\brief  i0 - 


\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ADK_Class"

     pc_ADK_Class :: pc_ADK_Class (PropertyHandle *prophdl )
                     : pc0_SDB_Structure (prophdl)
{



}

/******************************************************************************/
/**
\brief  i01 - 


\param  prophdl_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ADK_Class"

     pc_ADK_Class :: pc_ADK_Class (PropertyHandle &prophdl_ref )
                     : pc0_SDB_Structure (prophdl_ref)
{



}

/******************************************************************************/
/**
\brief  i02 - 


\param  obhandle - 
\param  accopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ADK_Class"

     pc_ADK_Class :: pc_ADK_Class (DBObjectHandle &obhandle, PIACC accopt )
                     : pc0_SDB_Structure (obhandle,"ADK_Class",accopt)
{



}


