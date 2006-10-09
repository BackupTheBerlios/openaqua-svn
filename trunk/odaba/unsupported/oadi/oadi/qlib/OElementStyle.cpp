/********************************* Class Source Code ***************************/
/**
\package  OADI - 
\class    OElementStyle

\brief    


\date     $Date: 2006/07/09 17:25:52,64 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OElementStyle"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#ifndef   DLL_OEventAction_HPP
#define   DLL_OEventAction_HPP
#include  <sOEventAction.hpp>
#include  <sDLL.h>
#endif
#include  <sOADKFactory.hpp>
#include  <sOBitmap.hpp>
#include  <sOButton.hpp>
#include  <sOCBitmap.hpp>
#include  <sOContextStyle.hpp>
#include  <sODataSource.hpp>
#include  <sOElementStyle.hpp>
#include  <sOEventAction.hpp>
#include  <sOField.hpp>
#include  <sOFont_.hpp>
#include  <sOFrameStyle.hpp>
#include  <sOLayout.hpp>
#include  <sOListLayout.hpp>
#include  <sOMenu.hpp>
#include  <sOResource.hpp>
#include  <sOStyle.hpp>
#include  <sOToolBox.hpp>
#include  <sOTreeLayout.hpp>
#include  <sOWidget.hpp>
#include  <sOWindow.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTControl.hpp>
#include  <sTControlFactory.hpp>
#include  <sTProjectManager.hpp>
#include  <sOElementStyle.hpp>


/******************************************************************************/
/**
\brief  CastPointer - 



\return pointer - 

\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OElementStyle :: CastPointer (char *typenames )
{

  return (   !typenames                         ? NULL
           : !strcmp(typenames,"OElementStyle") ? this
                                                : OStyleElement::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  GetControlName - 



\return string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetControlName"

char *OElementStyle :: GetControlName ( )
{
  OField          *ofield;
  OWindow         *owin;
  OEventAction    *oaction;
//  OConstant       *oconstant;
  char            *string = NULL;
  if ( ofield = OI_CAST(OField,this) )
    string = ofield->get_fieldControl()->get_sys_ident();
  else if ( owin = OI_CAST(OWindow,this) )
    string = owin->get_fieldControl()->get_sys_ident();
  else if ( (oaction = OI_CAST(OButton,this)) ||
       (oaction = OI_CAST(OMenu,this))   ||
       (oaction = OI_CAST(OToolBox,this))  )
    string = oaction->get_action_control()->get_sys_ident();
//  if ( oconst = OI_CAST(OConstant,elementStyle->Owner()) )
//    string = oconst->get_constControl()->get_sys_ident();


  return(string);
}

/******************************************************************************/
/**
\brief  GetDataSource - 



\return pODataSource - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDataSource"

ODataSource *OElementStyle :: GetDataSource ( )
{
  OField          *ofield;
  OWindow         *owin;
  ODataSource     *odsource = NULL;
  if ( ofield = OI_CAST(OField,this) )
    odsource = &ofield->get_dataSource();
  if ( owin = OI_CAST(OWindow,this) )
    if ( owin->get_ds_having() )
      odsource = &owin->get_ds_having()->get_dataSource();
  return(odsource);
}

/******************************************************************************/
/**
\brief  GetEnabledBitmap - 



\return pOBitmap - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEnabledBitmap"

OBitmap *OElementStyle :: GetEnabledBitmap ( )
{
  OBitmap        *pOBitmap = NULL;
BEGINSEQ
  if ( !bitmap )                                     ERROR

  if ( pOBitmap = bitmap->GetActiveBitmap() )        LEAVESEQ
  if ( pOBitmap = bitmap->GetInactiveBitmap() )      LEAVESEQ

RECOVER

ENDSEQ
  return(pOBitmap);
}

/******************************************************************************/
/**
\brief  GetFrameSize - 



\return dsize - 

\param  dsize - 
\param  field_margin - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFrameSize"

DSize OElementStyle :: GetFrameSize (DSize dsize, DMargin &field_margin )
{


  return(dsize);
}

/******************************************************************************/
/**
\brief  IsConcealed - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsConcealed"

logical OElementStyle :: IsConcealed ( )
{

  return hidden || concealed;


}

/******************************************************************************/
/**
\brief  IsField - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsField"

logical OElementStyle :: IsField ( )
{

  return ( OI_CAST(OField,this) ? YES : NO);


}

/******************************************************************************/
/**
\brief  OElementStyle - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OElementStyle"

     OElementStyle :: OElementStyle ( )
                     : OStyleElement (),
  style(NULL),
  layout(NULL),
  font(NULL),
  bitmap(NULL),
  concealed(NO)
{



}

/******************************************************************************/
/**
\brief  i01 - 



\param  bcOStyleElement - 
\param  pOStyle - 
\param  pOLayout - 
\param  pOFont_ - 
\param  pOCBitmap - 
\param  concealed - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OElementStyle"

     OElementStyle :: OElementStyle (OStyleElement bcOStyleElement, OStyle *pOStyle, OLayout *pOLayout, OFont_ *pOFont_, OCBitmap *pOCBitmap, logical concealed )
                     :   OStyleElement(bcOStyleElement)
, style(pOStyle)
, layout(pOLayout)
, font(pOFont_)
, bitmap(pOCBitmap)
, concealed(concealed)
{

/*
  "OElementStyle("
   +        ADK_StyleElement::Generate()
   + ", " + style.Generate()
   + ", " + layout.Generate()
   + ", " + font.Generate()
   + ", " + bitmap.Generate()
   + ", NO" //concealed - not set by read
   + ")";
*/

}

/******************************************************************************/
/**
\brief  OpenControl - 



\return pTControl - 

\param  typenames - 
\param  tparent - 
\param  pOFrameStyle - 
\param  owner - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenControl"

TControl *OElementStyle :: OpenControl (char *typenames, TControl *tparent, OFrameStyle *pOFrameStyle, OResource *owner )
{
  TControl          *t= NULL;
BEGINSEQ
  OADIRESET
  
  if ( !typenames && style )
    typenames = style->GetObjectType();
    
  if ( !(t = TControlFactory::NewControl(typenames)) )
                                                     OADICSERR(99)

  if ( t->Create(tparent,this,pOFrameStyle) )        ERROR
RECOVER
  t = NULL; // t has already been deleted by Create
ENDSEQ
  return(t);
}

/******************************************************************************/
/**
\brief  Read - 



\return term - 

\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

logical OElementStyle :: Read (PropertyHandle *ph )
{
  logical          term = NO;

  OStyleElement::Read(ph);

  style  = CACHE_READ(ph,"style",OStyle);  
  font   = CACHE_READ(ph,"font",OFont_);  
  layout = CACHE_READ(ph,"layout",OLayout);  
  bitmap = CACHE_READ(ph,"bitmap",OCBitmap);  

  return(term);
}

/******************************************************************************/
/**
\brief  Reset - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OElementStyle :: Reset ( )
{

  if ( style )
    style->Release();
  style = NULL;

  if ( layout )
    layout->Release();
  layout = NULL;

  if ( font )
    font->Release();
  font = NULL;
  
  if ( bitmap )
    bitmap->Release();
  bitmap = NULL;

  concealed = NO;

  OStyleElement::Reset();

}

/******************************************************************************/
/**
\brief  ResetActions - 




\param  action_list - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetActions"

void OElementStyle :: ResetActions (DLL(OEventAction) *action_list )
{
  OEventAction        *action;
  if ( action_list ) 
    while ( action = action_list->RemoveTail() )
      action->Release();


}

/******************************************************************************/
/**
\brief  SetStyle - 




\param  pOStyle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetStyle"

void OElementStyle :: SetStyle (OStyle *pOStyle )
{

  if ( style ) 
    style->Release();
  
  if ( style = pOStyle )
    style->Reserve();

}

/******************************************************************************/
/**
\brief  SetupListLayout - 



\return term - 

\param  pOListLayout - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupListLayout"

logical OElementStyle :: SetupListLayout (OListLayout *pOListLayout )
{

  if ( bitmap )
    pOListLayout->SetIcon(bitmap->GetInactiveBitmap(),bitmap->GetActiveBitmap(),bitmap->GetDisabledBitmap());
  
  if ( font )
    pOListLayout->SetFont(font);
  

  return(NO);
}

/******************************************************************************/
/**
\brief  SetupTreeLayout - 



\return term - 

\param  pOTreeLayout - 
\param  recursive - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupTreeLayout"

logical OElementStyle :: SetupTreeLayout (OTreeLayout *pOTreeLayout, logical recursive )
{
  logical    term = NO;
BEGINSEQ
  if ( !pOTreeLayout )                              LEAVESEQ
  
  pOTreeLayout->set_intern_id(GetID());
  
  if ( SetupListLayout(pOTreeLayout) )              ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Style - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Style"

OStyle *OElementStyle :: Style ( ) const
{

  return style;

}

/******************************************************************************/
/**
\brief  setConcealed - 




\param  f - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "setConcealed"

void OElementStyle :: setConcealed (logical f )
{

  concealed = f;

}

/******************************************************************************/
/**
\brief  ~OElementStyle - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OElementStyle"

     OElementStyle :: ~OElementStyle ( )
{

  if ( !Deleting() )
    Reset();


}


