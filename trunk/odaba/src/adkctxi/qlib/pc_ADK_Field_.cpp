/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/20|15:35:34,34}|(REF)
\class    pc_ADK_Field_

\brief    


\date     $Date: 2006/04/21 18:20:50,98 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ADK_Field_"

#include  <padkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <spc_ADK_Allign.hpp>
#include  <spc_ADK_Class.hpp>
#include  <spc_SDB_Member.hpp>
#include  <spc_ADK_Field_.hpp>


/******************************************************************************/
/**
\brief  IsInitialized

\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsInitialized"

logical pc_ADK_Field_ :: IsInitialized ( )
{
  logical                 cond = YES;
BEGINSEQ
// muss ggf. noch erweitert werden ...

  if ( GPH("data_ref.data_reference")->IsEmpty() ||
       GPH("data_ref.reference_type")->IsEmpty()   )   ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  NewField - 


\return term - 

\param  propnames - 
\param  posx - 
\param  posy - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NewField"

logical pc_ADK_Field_ :: NewField (char *propnames, int32 posx, int32 posy )
{
  char            string[ID_SIZE+1];
  char            propname[ID_SIZE];
  logical         term = NO;
BEGINSEQ
  strncpy(string,propnames,ID_SIZE);
  
  while ( Get(string) )
  {
    if ( strlen(string) >= 40 )                      ERROR
    strcat(string,"X");
  }

  gvtxstb(propname,string,ID_SIZE);
  Add(LAST_INSTANCE,propname);                        CTXCERR
  
  *GPH("position.opsx") = posx;
  *GPH("position.opsy") = posy;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupColumn

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupColumn"

logical pc_ADK_Field_ :: SetupColumn ( )
{
  PropertyHandle        *pfc = GetParentProperty();
  PropertyHandle        *my_class  = pfc->GPH("class");
  PropertyHandle        *member;
  logical                coll_opt;
  char                  *type;
  char                  *propnames = NULL;
  logical                term = NO;
BEGINSEQ
  if ( IsInitialized() )                             LEAVESEQ
  
  propnames = strdup(GPH("sys_ident")->GetString());
  if ( !my_class->Get(FIRST_INSTANCE) )              ERROR
    
  pc_ADK_Class   structure(*my_class);  
  if ( member = structure.GetMember(propnames) )
    coll_opt = pc_SDB_Member(member).IsMultipleRef() ? YES : NO;
  else
  {
    pc_ADK_Class  all_class(GetObjectHandle(),PI_Read);  
    PropertyHandle phpropnames(propnames);
    if ( all_class.Get(phpropnames) )
    {
      type     = "DRT_Extent";
      coll_opt = YES;
    }
  }

  *GPH("auto_open") = YES;
  *GPH("size.oszwdth") = -1;
  *GPH("size.oszhgth") = 20;
  SetupDataSource(propnames,type,coll_opt);
  SetupTitle(propnames);

RECOVER
  term = YES;
ENDSEQ
  if ( propnames )
    free(propnames);
  return(term);
}

/******************************************************************************/
/**
\brief  SetupDataSource - 


\return term - 

\param  propnames - 
\param  type_string - 
\param  coll_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupDataSource"

logical pc_ADK_Field_ :: SetupDataSource (char *propnames, char *type_string, logical coll_opt )
{
  logical                 term = NO;
  *GPH("data_ref.data_reference") = propnames;
  *GPH("data_ref.reference_type") = type_string;
  *GPH("data_ref.is_collection")  = coll_opt;

  return(term);
}

/******************************************************************************/
/**
\brief  SetupField - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupField"

logical pc_ADK_Field_ :: SetupField ( )
{
  PropertyHandle        *pfc = GetParentProperty();
  PropertyHandle        *my_class  = pfc->GPH("class");
  PropertyHandle        *member;
  PropertyHandle        *fc;
  logical                vgrow = YES;
  logical                hgrow = YES;
  logical                coll_opt;
  char                  *ref_type;  
  char                  *propnames = NULL;
  char                   strnames[ID_SIZE+1];
  logical                term = NO;
BEGINSEQ
  if ( IsInitialized() )                             LEAVESEQ
    
  propnames = strdup(GPH("sys_ident")->GetString());
    
  SetupFromParent();
  
  if ( !my_class->Get(FIRST_INSTANCE) )              ERROR
    
  pc_ADK_Class   new_class(GetObjectHandle(),PI_Update);  
  PropertyHandle extent(GetObjectHandle(),"SDB_Extend",PI_Read);  
  PropertyHandle phpropnames(propnames);
  pc_ADK_Class    structure(*my_class);  
  if ( member = structure.GetMember(propnames) )
  {
    if ( !(fc = new_class.ProvideDefaultControl(member,hgrow,vgrow)) ||
         !fc->Exist()  )                             ERROR
    coll_opt = pc_SDB_Member(member).IsMultipleRef() ? YES : NO;
    ref_type = "DRT_PropertyPath";
    strcpy(strnames,member->GetString("ddetype"));
  }
  else if ( extent.Get(phpropnames) )
  {
    if ( !(fc = new_class.ProvideDefaultControl(&extent,hgrow,vgrow)) ||
         !fc->Exist()  )                             ERROR
    coll_opt = YES;
    ref_type = "DRT_Extent";
    strcpy(strnames,extent.GetString("ddetype"));
  }
  else                                               ERROR
    
  if ( !hgrow )
    *GPH("allign.hori_sizing") = "SIZE_Fixed";
  if ( !vgrow )
    *GPH("allign.vert_sizing") = "SIZE_Fixed";
  
  *GPH("auto_open") = YES;
  SetupDataSource(propnames,ref_type,coll_opt);
  SetupTitle(propnames);
  SetupFromFieldControl(fc);

  GPH("class")->Add(new_class.ExtractKey());        CTXCERR
  GPH("field_control")->Add(fc->ExtractKey());      CTXCERR


RECOVER
  term = YES;
ENDSEQ
  if ( propnames )
    free(propnames);
  return(term);
}

/******************************************************************************/
/**
\brief  SetupFromFieldControl - 


\return term - 

\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupFromFieldControl"

logical pc_ADK_Field_ :: SetupFromFieldControl (PropertyHandle *prophdl )
{
  logical                 term = NO;
  *GPH("label_position") = *prophdl->GPH("label_position");
  
  *GPH("separate")       = *prophdl->GPH("separate");
  *GPH("accept_drop")    = *prophdl->GPH("accept_drop");
  


  return(term);
}

/******************************************************************************/
/**
\brief  SetupRegion

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupRegion"

logical pc_ADK_Field_ :: SetupRegion ( )
{
  PropertyHandle        *pfc = GetParentProperty();
  PropertyHandle        *my_class  = pfc->GPH("class");
  PropertyHandle        *member;
  logical                coll_opt;
  char                  *type;
  char                  *propnames = NULL;
  logical                term = NO;
BEGINSEQ
  if ( IsInitialized() )                             LEAVESEQ
  
  propnames = strdup(GPH("sys_ident")->GetString());
  if ( !my_class->Get(FIRST_INSTANCE) )              ERROR

  pc_ADK_Class   structure(*my_class);  
  if ( member = structure.GetMember(propnames) )
    coll_opt = pc_SDB_Member(member).IsMultipleRef() ? YES : NO;
  else
  {
    pc_ADK_Class  all_class(GetObjectHandle(),PI_Read);  
    PropertyHandle phpropnames(propnames);
    if ( all_class.Get(phpropnames) )
    {
      type     = "DRT_Extent";
      coll_opt = YES;
    }
  }

  *GPH("auto_open") = YES;
  SetupDataSource(propnames,type,coll_opt);
  SetupTitle(propnames);

RECOVER
  term = YES;
ENDSEQ
  if ( propnames )
    free(propnames);
  return(term);
}

/******************************************************************************/
/**
\brief  SetupTitle - 


\return term - 

\param  propnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupTitle"

logical pc_ADK_Field_ :: SetupTitle (char *propnames )
{
  logical                 term = NO;
  *propnames = toupper(*propnames);
  STRExchange(propnames,"_"," ",UNDEF);
  
  *GPH("text_definitions.title") = propnames;

  return(term);
}

/******************************************************************************/
/**
\brief  pc_ADK_Field_ - Konstruktor



\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ADK_Field_"

                        pc_ADK_Field_ :: pc_ADK_Field_ (PropertyHandle *prophdl )
                     : pc_ADK_StyleElement_(prophdl)
{



}


