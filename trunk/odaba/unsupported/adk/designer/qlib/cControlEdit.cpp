/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cControlEdit

\brief    


\date     $Date: 2006/08/30 14:49:38,68 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cControlEdit"

#include  <pdesign.h>
#include  <sNString.hpp>
#include  <scControlFrame.hpp>
#include  <scControlEdit.hpp>


/******************************************************************************/
/**
\brief  AddField - 



\return  - 

\param  drop_ph - 
\param  pos - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddField"

CTX_Control *cControlEdit :: AddField (PropertyHandle *drop_ph, const DPoint &pos )
{
  logical                 term          = NO;
  char                  * ref_name      = NULL;
  char                  * class_name    = NULL;
  PropertyHandle        * field_ph      = NULL;
  NString                 field_name    = "";
  CTX_Control           * field_context = NULL;
BEGINSEQ
  static char * const fields    = "fields";
  static char * const buttons   = "buttons";
  static char * const constants = "constants";

  if ( drop_ph->Inherits("ADK_FieldControl") )
    ref_name = fields;
  else
  if ( drop_ph->Inherits("ADK_EventActionControl") )
    ref_name = buttons;
  else
  if ( drop_ph->Inherits("ADK_ConstantControl") )
    ref_name = constants;

  if ( ref_name )
  {
    field_ph = control_ph->GetPropertyHandle(ref_name);
    if ( ! field_ph )                                    OADIERR(99)

    if ( ref_name == fields
      && (class_name = drop_ph->GetPropertyHandle("class(0).sys_ident")->GetString())
      && strcmp(class_name, control_ph->GetPropertyHandle("class(0).sys_ident")->GetString()) )
    {
      field_name += class_name;
      field_name += "_";
    }
    field_name += drop_ph->GetPropertyHandle("sys_ident")->GetString();
    PropertyHandle phfield;
    phfield = PropertyHandle((char*)field_name);
    while ( field_ph->Get(phfield) ){
      field_name += "X";
      phfield = PropertyHandle((char*)field_name);
    }

    field_ph->Add();
    *field_ph->GetPropertyHandle("sys_ident") = (char*)field_name;
    *field_ph->GetPropertyHandle("position.opsx")  = pos.X;
    *field_ph->GetPropertyHandle("position.opsy")  = pos.Y;
    
    if ( ref_name == fields )
    {
      field_ph->GetPropertyHandle("class")->AddReference(*drop_ph->GetPropertyHandle("class(0)"));
      field_ph->GetPropertyHandle("field_control")->AddReference(*drop_ph);

      *field_ph->GetPropertyHandle("data_ref.data_reference") = "*";
      *field_ph->GetPropertyHandle("data_ref.ref_type") = "DRT_PropertyPath";
    }
    if ( ref_name == buttons )
        field_ph->GetPropertyHandle("button_control")->AddReference(*drop_ph);
    if ( ref_name == constants )
      field_ph->GetPropertyHandle("const_data")->AddReference(*drop_ph);
    
    field_ph->Save();
    
    if (
         ( LoadControlAttribute("allign.hori_cell") > 0 )
      && ( LoadControlAttribute("allign.vert_cell") > 0 )
    ){
      StoreFieldAttribute(field_ph, "allign.arrange", "AT_Grid");
    }

    /* das hier macht erst __NACH__ dem Save() Sinn !!! */
    if ( ref_name == fields )
      field_context = CreateField((char*)field_name, YES, pos, UNDEF);
    if ( ref_name == buttons )
      field_context = CreateButton((char*)field_name, YES, pos, UNDEF);
    // if ( ref_name == constants )
      // field_context = CreateConstant(field_name, YES, pos, UNDEF);
 }

  if ( !field_context )                              OADIERR(99)
RECOVER
  field_context = NULL;
ENDSEQ
  return(field_context);
}

/******************************************************************************/
/**
\brief  CloseFieldControl - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseFieldControl"

logical cControlEdit :: CloseFieldControl ( )
{

  return GetFrameContext()->CloseFieldControl();

}

/******************************************************************************/
/**
\brief  Create - 



\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cControlEdit :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cControlEdit();
  return(NO);

}

/******************************************************************************/
/**
\brief  DoAfterEnter - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterEnter"

int8 cControlEdit :: DoAfterEnter ( )
{
  int8                    executed = NO;
  cControlFrame         * frame    = NULL;
  GetFrameContext()->UpdatePropertiesPH(control_ph);
  return(executed);
}

/******************************************************************************/
/**
\brief  DoBeforeDrop - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeDrop"

int8 cControlEdit :: DoBeforeDrop ( )
{
  PropertyHandle        * drop_ph  = GetDropPropertyHandle();
  char                  * drop_txt = GetDropText();
  DPoint                  drop_pos = GetDropPosition();
  char                    executed      = NO;
  PropertyHandle        * attr_ph       = NULL;
  PropertyHandle        * field_ph      = NULL;
  NString                 field_opts    = "";
  char                  * field_name    = NULL;
  CTX_Control           * field_context = NULL;
BEGINSEQ
  if ( drop_ph->Inherits("ADK_FieldControl")       ||
       drop_ph->Inherits("ADK_EventActionControl") ||
       drop_ph->Inherits("ADK_ConstantControl")      )
  {
    if ( !(field_context = AddField(drop_ph, drop_pos)) )
                                                     ERROR
  } 
  else
  {
    field_ph = control_ph->GetPropertyHandle("fields");
    if ( ! field_ph )                                OADIERR(99)
  
    field_opts += drop_txt;
    field_opts += ",";
    field_opts += PropertyHandle(drop_pos.X).GetString();
    field_opts += ",";
    field_opts += PropertyHandle(drop_pos.Y).GetString();
    control_ph->ExecuteInstanceAction("AddField", field_opts);
  
    field_name = field_ph->GetPropertyHandle("sys_ident")->GetString();
    if (
         ( LoadControlAttribute("allign.hori_cell") > 0 )
      && ( LoadControlAttribute("allign.vert_cell") > 0 )
    ){
      StoreFieldAttribute(field_ph, "allign.arrange", "AT_Grid");
    }

    if ( !(field_context = CreateField(field_name, YES, drop_pos, UNDEF)) )
                                                     ERROR
  }
  if ( !field_context )                              OADIERR(99)

  EnableFieldDesignMode(field_context);
  InitDesigner();
RECOVER

ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  EditField - 



\return term - 

\param  field_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EditField"

logical cControlEdit :: EditField (PropertyHandle *field_ph )
{
  logical                 term = NO;
  ExecuteWindow(field_ph,"ADK_Field","Edit",NO);
  return(term);
}

/******************************************************************************/
/**
\brief  EditFieldLabel - 



\return term - 

\param  field_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EditFieldLabel"

logical cControlEdit :: EditFieldLabel (PropertyHandle *field_ph )
{
  logical                 term = NO;
  ExecuteWindow(field_ph,"ADK_Field","EditLabel",NO);
  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteFunction - 



\return  - 

\param  fname - 
\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical cControlEdit :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("Refresh",ALINK(this,cControlEdit,Refresh)),
                           cfte("SizeChanged",ALINK(this,cControlEdit,SizeChanged)),
                         };
  static srt  cftesrt(sizeof(acttbl)/CFTE,CFTE,UNDEF,UNDEF,UNDEF,(char *)acttbl,NO);

  if ( !cftesrt.srtkln() )
    cftesrt.srtsor(CFTE_KPS,CFTE_KLN,CFTE_KTP);

  if ( cfteptr = (cfte *)cftesrt.srtigt(cftesrt.srtssr(gvtxstb(actname,fname,ID_SIZE))) )
  {
    if ( chk_opt )                                   LEAVESEQ
    term = cfteptr->ActionCall(this);
  }
  else
    term = CTX_Design::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetFrameContext - 



\return frame - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFrameContext"

cControlFrame *cControlEdit :: GetFrameContext ( )
{
  cControlFrame      * frame = NULL;
BEGINSEQ
  if ( !(frame = (cControlFrame*)GetHighContext()) ) OADIERR(99)
RECOVER

ENDSEQ
  return(frame);
}

/******************************************************************************/
/**
\brief  OpenFieldControl - 



\return term - 

\param  field_ph - 
\param  field_control_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenFieldControl"

logical cControlEdit :: OpenFieldControl (PropertyHandle *field_ph, PropertyHandle *field_control_ph )
{
  logical                 term = NO;
  DPoint pos = DPoint(
    field_ph->GetInt("position.opsx"),
    field_ph->GetInt("position.opsy")
  );

  return GetFrameContext()->OpenFieldControl(field_control_ph, pos);

}

/******************************************************************************/
/**
\brief  Refresh - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Refresh"

logical cControlEdit :: Refresh ( )
{

  return GetFrameContext()->ReloadControl();

}

/******************************************************************************/
/**
\brief  SelectField - 



\return term - 

\param  field_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SelectField"

logical cControlEdit :: SelectField (PropertyHandle *field_ph )
{


  logical                 term     = NO;
  CloseFieldControl();
  return GetFrameContext()->UpdatePropertiesPH(field_ph);


}

/******************************************************************************/
/**
\brief  SizeChanged - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SizeChanged"

logical cControlEdit :: SizeChanged ( )
{
  logical                 term = NO;
  GetFrameContext()->ExecuteFunction("SizeChanged");
  return(term);
}

/******************************************************************************/
/**
\brief  cControlEdit - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cControlEdit"

     cControlEdit :: cControlEdit ( )
                     : CTX_Design ()
{



}

/******************************************************************************/
/**
\brief  ~cControlEdit - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cControlEdit"

     cControlEdit :: ~cControlEdit ( )
{



}


