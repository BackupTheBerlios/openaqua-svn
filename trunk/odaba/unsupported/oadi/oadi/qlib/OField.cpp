/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OField



\date     $Date: 2006/04/28 18:35:31,18 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OField"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sOADKFactory.hpp>
#include  <sODataSource.hpp>
#include  <sOFieldControl.hpp>
#include  <sOFrameStyle.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTControl.hpp>
#include  <sTProjectManager.hpp>
#include  <sOField.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OField :: CastPointer (char *typenames )
{

  return (   !typenames                             ? NULL
           : !strcmp(typenames,"OField")            ? this
           : !strcmp(typenames,"ODataSourceHaving") ? (ODataSourceHaving *)this
                                                    : OFieldControl::CastPointer(typenames) );


}

/******************************************************************************/
/**
\brief  CreateInstance

\return rc

\param  instptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInstance"

int32 OField :: CreateInstance (void **instptrp )
{

  *instptrp = new OField();
  return(0);

}

/******************************************************************************/
/**
\brief  FrameStyle

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FrameStyle"

OFrameStyle *OField :: FrameStyle ( ) const
{

  return frameStyle;

}

/******************************************************************************/
/**
\brief  GetAccessClassName

\return clsnames

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAccessClassName"

char *OField :: GetAccessClassName ( )
{
  char             *clsnames = class_name;
  static char       clsname[ID_SIZE];
  logical                 term = NO;
BEGINSEQ
  ERROR
/*  
  if ( memcmp(class_name,"COLLECTION  ",12) &&
       memcmp(class_name,"IMBEDDED    ",12) &&
       memcmp(class_name,"ENUMERATION ",12)   )       LEAVESEQ
       
  memset(clsname,' ',sizeof(clsname));
  clsnames = clsname;
*/
RECOVER

ENDSEQ
  return(clsnames);
}

/******************************************************************************/
/**
\brief  OField

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OField"

     OField :: OField ( )
                     : OFieldControl (),
ODataSourceHaving(),
  fieldControl(0),
  frameStyle(NULL),
  used_as(OFT_undefined),
  used_recursive(NO)
{



}

/******************************************************************************/
/**
\brief  i01


\param  bcOFieldControl
\param  bcODataSourceHaving
\param  pOFieldControl
\param  pOFrameStyle
\param  used_as
\param  used_recursive
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OField"

     OField :: OField (OFieldControl bcOFieldControl, ODataSourceHaving bcODataSourceHaving, OFieldControl *pOFieldControl, OFrameStyle *pOFrameStyle, OFieldType used_as, logical used_recursive )
                     : OFieldControl (bcOFieldControl),
ODataSourceHaving (bcODataSourceHaving),
  fieldControl(pOFieldControl),
  frameStyle(pOFrameStyle),
  used_as(used_as),
  used_recursive(used_recursive)
{
  *(OFieldControl *)this = *fieldControl;
  
/*
  "OField("
  +        ADK_FieldControl::Generate(class.sys_ident)
  + ", " + ADK_ODataSourceHaving::Generate(data_ref)
  + ", " + field_control.Generate()
  + ", " + frame_style.Generate()
  + ", " + (     path == "ADK_StyleAction.columns"?"OFT_Column":
             (   path == "ADK_StyleAction.regions"?"OFT_Region":
               ( path == "ADK_StyleAction.fields" ?"OFT_Control":
                 ""
               )
             )
           )
  + ", " + used_recusive?? // not set in read
  + ")";
*/
}

/******************************************************************************/
/**
\brief  Open

\return pTControl

\param  tparent
\param  active_f
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

TControl *OField :: Open (TControl *tparent, logical active_f )
{
  TControl                 *t = NULL;
  if ( style )
    if ( t = OpenControl(style->GetObjectType(),tparent,frameStyle,this) )
      if ( active_f )
        t->Activate();
  return(t);
}

/******************************************************************************/
/**
\brief  Read

\return term

\param  ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

logical OField :: Read (PropertyHandle *ph )
{
  logical           term = NO;
BEGINSEQ
  dataSource.Read(PHREF(ph->GPH("data_ref")));
  
  if ( !strcmp(ph->GetPropertyPath(),"ADK_StyleAction.columns") )
    used_as = OFT_Column;
  else if ( !strcmp(ph->GetPropertyPath(),"ADK_StyleAction.regions") )
    used_as = OFT_Region;
  else if ( !strcmp(ph->GetPropertyPath(),"ADK_StyleAction.fields") )
    used_as = OFT_Control;
  
  if ( fieldControl = CACHE_READ(ph,"field_control",OFieldControl) )
  {
    *(OFieldControl *)this = *fieldControl;
    action_control = fieldControl;
  }
  else if ( autoOpen && used_as == OFT_Control )   OADIERR(99)
    
  UpdateStyleElement(ph);
  SetClassName(ph);
  
  delete frameStyle;
  frameStyle = new OFrameStyle;
  if ( ph = PHREF(ph->GPH("frame_style")) )
    frameStyle->Read(ph);
  
  SetupLabelSize(&labelPosition);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Read_intern

\return term

\param  ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read_intern"

logical OField :: Read_intern (PropertyHandle *ph )
{
  logical           term = NO;
BEGINSEQ
// used for reading designer controls in oadii

  used_as = OFT_Control;
  
  if ( !(fieldControl = CACHE_READ(ph,NULL,OFieldControl)) )
                                                     ERROR
  *(OFieldControl *)this = *fieldControl;
  distance = 0;
  
  frameStyle = new OFrameStyle;
  SetClassName(ph);
  
  SetupLabelSize(&labelPosition);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OField :: Reset ( )
{

  OFieldControl ofc;
  *(OFieldControl *)this = ofc;  // das koennte zu einfach sein, vor allen fuer recursiv
    
  delete frameStyle;  // kann nicht zu OResource gemacht werden, da auch Basisklasse
  frameStyle = NULL;

  if ( fieldControl )
    fieldControl->Release();
  fieldControl = NULL;

  dataSource.Reset();
}

/******************************************************************************/
/**
\brief  SetClassName

\return term

\param  ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetClassName"

logical OField :: SetClassName (PropertyHandle *ph )
{
  PropertyHandle   *class_ph;
  logical           term = NO;
  class_ph = ph->GPH("class");
  if ( class_ph->Get(FIRST_INSTANCE) )
    OFieldControl::SetClassName(class_ph->GetString("sys_ident"));

  return(term);
}

/******************************************************************************/
/**
\brief  set_position


\param  position
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_position"

void OField :: set_position (DPoint position )
{

  get_bounds().Origin = position;

}

/******************************************************************************/
/**
\brief  set_res_id


\param  resource_id
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_res_id"

void OField :: set_res_id (int resource_id )
{
  res_id = resource_id;
}

/******************************************************************************/
/**
\brief  set_size


\param  dsize
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_size"

void OField :: set_size (DSize dsize )
{

  get_bounds().Size = dsize;

}

/******************************************************************************/
/**
\brief  set_type


\param  ofield_type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_type"

void OField :: set_type (OFieldType ofield_type )
{
  used_as = ofield_type;
}

/******************************************************************************/
/**
\brief  ~OField


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OField"

     OField :: ~OField ( )
{
  if ( !Deleting() )
    Reset();
  else
  {
    OFieldControl ofc;
    *(OFieldControl *)this = ofc;  // das koennte zu einfach sein, vor allen fuer recursiv
    Deleting();  
  }
  
  delete frameStyle;  // kann nicht zu OResource gemacht werden, da auch Basisklasse
  frameStyle = NULL;

}


