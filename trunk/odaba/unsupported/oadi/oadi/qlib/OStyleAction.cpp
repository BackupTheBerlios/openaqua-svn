/********************************* Class Source Code ***************************/
/**
\package  OADI - 
\class    OStyleAction

\brief    


\date     $Date: 2006/06/20 13:14:12,96 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OStyleAction"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#ifndef   DLL_OButton_HPP
#define   DLL_OButton_HPP
#include  <sOButton.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLL_OEventAction_HPP
#define   DLL_OEventAction_HPP
#include  <sOEventAction.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLL_OField_HPP
#define   DLL_OField_HPP
#include  <sOField.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLL_OToolBox_HPP
#define   DLL_OToolBox_HPP
#include  <sOToolBox.hpp>
#include  <sDLL.h>
#endif
#include  <sOADKFactory.hpp>
#include  <sOButton.hpp>
#include  <sOButtonControl.hpp>
#include  <sOCBitmap.hpp>
#include  <sOContextStyle.hpp>
#include  <sOElementStyle.hpp>
#include  <sOEventAction.hpp>
#include  <sOField.hpp>
#include  <sOFieldControl.hpp>
#include  <sOFrameStyle.hpp>
#include  <sOLabelDefinition.hpp>
#include  <sOListLayout.hpp>
#include  <sOMenu.hpp>
#include  <sOResource.hpp>
#include  <sOToolBox.hpp>
#include  <sOTreeLayout.hpp>
#include  <sOWindow.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTControl.hpp>
#include  <sTProjectManager.hpp>
#include  <sOStyleAction.hpp>


/******************************************************************************/
/**
\brief  CastPointer - 


\return pointer - 

\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OStyleAction :: CastPointer (char *typenames )
{

  return (   !typenames                        ? NULL
           : !strcmp(typenames,"OStyleAction") ? this
                                               : OEventActionControl::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  Column - 


\return pOField - 

\param  index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Column"

OField *OStyleAction :: Column (int index )
{

  return (columns ? columns->Get(index) : NULL);

}

/******************************************************************************/
/**
\brief  ContextMenu - 


\return OMenu - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ContextMenu"

OMenu *OStyleAction :: ContextMenu ( )
{

  return contextmenu;

}

/******************************************************************************/
/**
\brief  Field - 


\return term - 

\param  index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Field"

OField *OStyleAction :: Field (int index )
{

  return ( fields ? fields->Get(index) : NULL);

}

/******************************************************************************/
/**
\brief  FieldByName - 


\return term - 

\param  rcdsName - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FieldByName"

OField *OStyleAction :: FieldByName (const DString &rcdsName )
{
  OField   *f = NULL;
BEGINSEQ
  if ( !fields )                                     ERROR
    
  DLL(OField) fit(*fields);
  fit.GoTop();
  while( f = fit.GetNext() )
    if ( f->get_sys_ident() == rcdsName )            LEAVESEQ
      
  ERROR

RECOVER
  f = NULL;
ENDSEQ
  return(f);
}

/******************************************************************************/
/**
\brief  FieldCount - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FieldCount"

int OStyleAction :: FieldCount ( )
{

  return ( fields ? fields->GetCount() : UNDEF);


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

DSize OStyleAction :: GetFrameSize (DSize dsize, DMargin &field_margin )
{
  int    margin = field_margin.Maximum();
  return( DSize(MAX(right_size,MAX(top_right_width,bottom_right_width))   +
                MAX(left_size,MAX(top_left_width,bottom_left_width))      +
                MAX(dsize.Width,MAX(top_width,bottom_width))              +
                align.get_margin().Left+align.get_margin().Right,
                MAX(dsize.Height,MAX(left_height,right_height))           +
                top_size+bottom_size                                      +
                align.get_margin().Top+align.get_margin().Bottom) );

}

/******************************************************************************/
/**
\brief  Menu - 


\return OMenu - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Menu"

OMenu *OStyleAction :: Menu ( )
{

  return(menu);

}

/******************************************************************************/
/**
\brief  OStyleAction - 


\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OStyleAction"

     OStyleAction :: OStyleAction ( )
                     : OEventActionControl (),
  outer_elements(NO),
  fields(NULL),
  columns(NULL),
  regions(NULL),
  buttons(NULL),
  menu(NULL),
  contextmenu(NULL),
  tool_bars(NULL),
  reactions(NULL),
  left_size(0),
  top_size(0),
  right_size(0),
  bottom_size(0),
  left_height(0),
  right_height(0),
  top_width(0),
  top_left_width(0),
  top_right_width(0),
  bottom_width(0),
  bottom_left_width(0),
  bottom_right_width(0)
{



}

/******************************************************************************/
/**
\brief  i01 - 


\param  bc - 
\param  outer_elements - 
\param  fields - 
\param  columns - 
\param  regions - 
\param  buttons - 
\param  menu - 
\param  contextmenu - 
\param  tool_bars - 
\param  reactions - 
\param  left_size - 
\param  top_size - 
\param  right_size - 
\param  bottom_size - 
\param  left_height - 
\param  right_height - 
\param  top_width - 
\param  top_left_width - 
\param  top_right_width - 
\param  bottom_width - 
\param  blw - 
\param  brw - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OStyleAction"

     OStyleAction :: OStyleAction (OEventActionControl bc, logical outer_elements, DLL(OField) *fields, DLL(OField) *columns, DLL(OField) *regions, DLL(OButton) *buttons, OMenu *menu, OMenu *contextmenu, DLL(OToolBox) *tool_bars, DLL(OEventAction) *reactions, int32 left_size, int32 top_size, int32 right_size, int32 bottom_size, int32 left_height, int32 right_height, int32 top_width, int32 top_left_width, int32 top_right_width, int32 bottom_width, int32 blw, int32 brw )
                     : OEventActionControl (bc),
  outer_elements(outer_elements),
  fields(fields),
  columns(columns),
  regions(regions),
  buttons(buttons),
  menu(menu),
  contextmenu(contextmenu),
  tool_bars(tool_bars),
  reactions(reactions),
  left_size(left_size),
  top_size(top_size),
  right_size(right_size),
  bottom_size(bottom_size),
  left_height(left_height),
  right_height(right_height),
  top_width(top_width),
  top_left_width(top_left_width),
  top_right_width(top_right_width),
  bottom_width(bottom_width),
  bottom_left_width(blw),
  bottom_right_width(brw)
{

/*
  "OStyleAction("
  +        ADK_EventActionControl::Generate()
??  + ", NO" // outer elements 
  + ", " + fields.GenerateList()
  + ", " + columns.GenerateList()
  + ", " + regions.GenerateList()
  + ", " + buttons.GenerateList()
  + ", " + menu.Generate()
  + ", " + context_menu.Generate()
  + ", " + tool_boxes.GenerateList()
  + ", " + sub_actions.GenerateList()
  + ", 0"  //left_size
  + ", 0"  //top_size 
  + ", 0"  //right_size
  + ", 0"  //bottom_size
  + ", 0"  //left_height 
  + ", 0"  //right_height 
  + ", 0"  //top_width
  + ", 0"  //top_left_width 
  + ", 0"  //top_right_width 
  + ", 0"  //bottom_width 
  + ", 0"  //bottom_left_width 
  + ", 0"  //bottom_right_width 
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

TControl *OStyleAction :: OpenControl (char *typenames, TControl *tparent, OFrameStyle *pOFrameStyle, OResource *owner )
{
  OField   *f;
  OButton  *b;
  TControl *t;
BEGINSEQ
  if ( !(t = OElementStyle::OpenControl(typenames,tparent,pOFrameStyle,owner)) )
                                                     ERROR
  if ( fields )
  {
    DLL(OField) fit(*fields);
    fit.GoTop();
    while( f = fit.GetNext() )
      if( f->IsAutoOpen() )
      {
        f->Open(t,YES);
        SetupElementSize(f);
      }
  }
  
  if ( buttons )
  {
    DLL(OButton) bit(*buttons);
    bit.GoTop();
    while( b = bit.GetNext() )
      if( b->IsAutoOpen() )
      {
        b->Open(t,YES);
        SetupElementSize(b);
      }
  }
  

RECOVER

ENDSEQ
  return(t);
}

/******************************************************************************/
/**
\brief  PrepareRead - 


\return term - 

\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PrepareRead"

logical OStyleAction :: PrepareRead (PropertyHandle *ph )
{
  logical                 term = NO;
  if ( !fields && ph->GPH("fields")-> GetCount() )
    fields = new DLL(OField)();
  
  if ( !buttons && ph->GPH("buttons")->GetCount() )
    buttons = new DLL(OButton)();
  
  if ( !regions && ph->GPH("regions")->GetCount() )
    regions = new DLL(OField)();
  
  if ( !columns && ph->GPH("columns")->GetCount() )
    columns = new DLL(OField)();

  if ( !tool_bars && ph->GPH("tool_boxes")->GetCount() )
    tool_bars = new DLL(OToolBox)();
  return(term);
}

/******************************************************************************/
/**
\brief  Reactions - 


\return reactions - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reactions"

DLL(OEventAction) *OStyleAction :: Reactions ( )
{

  return(reactions);

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

logical OStyleAction :: Read (PropertyHandle *ph )
{
  logical                 term = NO;
  OEventActionControl::Read(ph);

  textDefinitions.Read(PHREF(ph->GPH("text_definitions")));
  
  PrepareRead(ph);
  
  ReadActions(ph->GPH("sub_actions"),&reactions);
  ReadFields(ph);
  ReadButtons(ph);
  ReadRegions(ph);
  ReadColumns(ph);
  ReadMenu(ph);
  ReadContextMenu(ph);
  ReadToolBars(ph);

  return(term);
}

/******************************************************************************/
/**
\brief  ReadButtons - 


\return term - 

\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadButtons"

logical OStyleAction :: ReadButtons (PropertyHandle *ph )
{
  OButton         *bu;
  long             indx0 = 0;
  logical          term  = NO;
BEGINSEQ
  if ( !buttons )                                    LEAVESEQ
    
  ph = ph->GPH("buttons");
  while ( ph->Get(indx0++) )
    if ( bu = CACHE_READ(ph,NULL,OButton) )
    {
      buttons->AddTail(bu);
      if ( !outer_elements && bu->get_action_control()->IsOuterElement() )
        outer_elements = YES;
    }
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReadColumns - 


\return term - 

\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadColumns"

logical OStyleAction :: ReadColumns (PropertyHandle *ph )
{
  OField          *fi;
  long             indx0 = 0;
  logical          term  = NO;
BEGINSEQ
  if ( !columns )                                    LEAVESEQ
  
  ph = ph->GPH("columns");
  while ( ph->Get(indx0++) )
    if ( fi = CACHE_READ(ph,NULL,OField) )
    {
      if( fi->IsAutoOpen() )
      {
        columns->AddTail(fi);
        fi->set_type(OFT_Column);
      }
    }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReadContextMenu - 


\return term - 

\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadContextMenu"

logical OStyleAction :: ReadContextMenu (PropertyHandle *ph )
{
  OEventAction    *eventact;
  logical          term  = NO;
  if ( contextmenu = CACHE_READ(ph,"context_menu",OMenu) )
  {
    eventact = new OEventAction();
    eventact->SetContextMenuProperty();
    reactions->AddTail(eventact);
  }

  return(term);
}

/******************************************************************************/
/**
\brief  ReadFields - 


\return term - 

\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadFields"

logical OStyleAction :: ReadFields (PropertyHandle *ph )
{
  OField          *fi;
  long             indx0 = 0;
  logical          term  = NO;
BEGINSEQ
  if ( !fields )                                     LEAVESEQ
    
  ph = ph->GPH("fields");
  while ( ph->Get(indx0++) )
    if ( fi = CACHE_READ(ph,NULL,OField) )
    {
      fields->AddTail(fi);
      fi->set_type(OFT_Control);
      if ( !outer_elements && fi->get_fieldControl() && 
           fi->get_fieldControl()->IsOuterElement() )
        outer_elements = YES;
    }
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReadMenu - 


\return term - 

\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadMenu"

logical OStyleAction :: ReadMenu (PropertyHandle *ph )
{
  long             indx0 = 0;
  logical          term  = NO;
  menu = CACHE_READ(ph,"menu",OMenu);

  return(term);
}

/******************************************************************************/
/**
\brief  ReadRegions - 


\return term - 

\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadRegions"

logical OStyleAction :: ReadRegions (PropertyHandle *ph )
{
  OField          *fi;
  long             indx0 = 0;
  logical          term  = NO;
BEGINSEQ
  if ( !regions )                                    LEAVESEQ
    
  ph = ph->GPH("regions");
  while ( ph->Get(indx0++) )
    if ( fi = CACHE_READ(ph,NULL,OField) )
    {
      if( fi->IsAutoOpen() )
      {
        regions->AddTail(fi);
        fi->set_type(OFT_Region);
      }
    }
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReadToolBars - 


\return term - 

\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadToolBars"

logical OStyleAction :: ReadToolBars (PropertyHandle *ph )
{
  OToolBox        *tb;
  long             indx0 = 0;
  logical          term  = NO;
BEGINSEQ
  if ( !tool_bars )                                  LEAVESEQ
    
  ph = ph->GPH("tool_boxes");
  while ( ph->Get(indx0++) )
    if ( tb = CACHE_READ(ph,NULL,OToolBox) )
      tool_bars->AddTail(tb);

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Region - 


\return pOField - 

\param  index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Region"

OField *OStyleAction :: Region (int index )
{

  return ( regions ? regions->Get(index) : NULL );

}

/******************************************************************************/
/**
\brief  Reset - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OStyleAction :: Reset ( )
{
  OResource       *resource;
  if ( fields )
    while ( resource = fields->RemoveHead() )
      resource->Release();
  
  if ( columns )
    while ( resource = columns->RemoveHead() )
      resource->Release();

  if ( regions )
    while ( resource = regions->RemoveHead() )
      resource->Release();

  if ( buttons )
    while ( resource = buttons->RemoveHead() )
      resource->Release();
  
  if ( tool_bars )
    while ( resource = tool_bars->RemoveHead() )
      resource->Release();
  
  if ( menu )
    menu->Release();
  menu = NULL;

  if ( contextmenu )
    contextmenu->Release();
  contextmenu = NULL;

  if ( reactions )
    while ( resource = reactions->RemoveHead() )
      resource->Release();
  
  textDefinitions.Reset();
  OElementStyle::Reset();
  ResetActions(reactions);

}

/******************************************************************************/
/**
\brief  SetupElementSize - 


\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  pOElementStyle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupElementSize"

logical OStyleAction :: SetupElementSize (OElementStyle *pOElementStyle )
{
  DMargin       margin;
  return ( SetupElementSize(pOElementStyle,
                            pOElementStyle->GetFrameSize(pOElementStyle->Size(),
                                                         margin)) );

}

/******************************************************************************/
/**
\brief  i02 - 


\param  pOFieldControl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupElementSize"

logical OStyleAction :: SetupElementSize (OFieldControl *pOFieldControl )
{

  return ( SetupElementSize(pOFieldControl,
                            pOFieldControl->GetFrameSize(pOFieldControl->Size(),
                                                         pOFieldControl->get_field_margin())) );

}

/******************************************************************************/
/**
\brief  i2 - 


\param  pOContextStyle - 
\param  dsize - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupElementSize"

logical OStyleAction :: SetupElementSize (OContextStyle *pOContextStyle, DSize dsize )
{
  OAlign            &align = pOContextStyle->get_align();

  return( SetupSize(align.get_vert(),align.get_hori(),dsize,
                    pOContextStyle->get_distance()) );


}

/******************************************************************************/
/**
\brief  SetupLabelSize - 


\return term - 

\param  pOLabelDefinition - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupLabelSize"

logical OStyleAction :: SetupLabelSize (OLabelDefinition *pOLabelDefinition )
{
  ADK_VertPos    vert_pos;
  ADK_HoriPos    hori_pos;
  logical     term = NO;

  if ( pOLabelDefinition->HasShowLabel() )
  {
    vert_pos = pOLabelDefinition->VertPos(VPS_undefined);
    hori_pos = pOLabelDefinition->HoriPos(HPS_undefined);
    
    if ( !outer_elements &&
         (vert_pos == VPS_OuterTop  || vert_pos == VPS_OuterBottom ||
          hori_pos == HPS_OuterLeft || hori_pos == HPS_OuterRight    ) )
      outer_elements = YES;
  
    term = SetupSize(vert_pos,hori_pos,
                     pOLabelDefinition->Size(),0);
  }

  return(term);
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

logical OStyleAction :: SetupListLayout (OListLayout *pOListLayout )
{
  OField           *ofield;
  ODataSource      *odsource;
  OListLayout      *column;
  OTreeLayout      *region;
  OFont_           *fnt;
  OCBitmap         *bm;
  char             *text;
  DSize             hsize;
  int               indx0 = 0;
  logical           term = NO;
  OElementStyle::SetupListLayout(pOListLayout);
  
  while ( ofield = Column(indx0++) )
  {
    odsource = &ofield->get_dataSource();
    if ( column = pOListLayout->AddColumn((char *)odsource->GetPath(),odsource->get_structureName(),
                                          odsource->get_isCollection(),odsource->get_sortOrder(),
                                          odsource->GetPathType(),odsource->get_accmode()) )
    {
      if ( text = ofield->GetTitle(odsource) )
      {
        column->SetStaticText(text);
        hsize = ofield->LabelPosition()->Size();
        column->SetHeaderSize(hsize.Width  ? hsize.Width  : AUTO,
                              hsize.Height ? hsize.Height : AUTO);      
      }
      column->SetWidth(ofield->Size().Width);      
      column->SetHeight(ofield->Size().Height);
      ofield->SetupListLayout(column);
    }
  }


  return(term);
}

/******************************************************************************/
/**
\brief  SetupMargin - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupMargin"

void OStyleAction :: SetupMargin ( )
{
  OFieldControl    *fc;
BEGINSEQ
  if ( outer_elements )                            LEAVESEQ

  if ( fc = OI_CAST(OFieldControl,this) )
  {
    fc->get_align().get_margin() = fc->get_field_margin();
    fc->get_field_margin()       = DMargin();
  }

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetupSize - 


\return term - 

\param  vert_pos - 
\param  hori_pos - 
\param  dsize - 
\param  distance - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupSize"

logical OStyleAction :: SetupSize (ADK_VertPos vert_pos, ADK_HoriPos hori_pos, DSize dsize, int32 distance )
{
  logical            term  = NO;
  switch ( vert_pos )
  {
    case VPS_OuterTop    : if ( dsize.Height > top_size )
                             top_size = dsize.Height;
                           if ( hori_pos == HPS_InnerLeft || hori_pos == HPS_InnerRight )
                             top_width += (dsize.Width + distance);
                           if ( hori_pos == HPS_OuterLeft )
                             top_left_width += (dsize.Width + distance);
                           if ( hori_pos == HPS_OuterRight )
                             top_right_width += (dsize.Width + distance);
                           break;
    case VPS_OuterBottom : if ( dsize.Height > bottom_size )
                             bottom_size = dsize.Height;
                           if ( hori_pos == HPS_InnerLeft || hori_pos == HPS_InnerRight )
                             bottom_width += (dsize.Width + distance);
                           if ( hori_pos == HPS_OuterLeft )
                             bottom_left_width += (dsize.Width + distance);
                           if ( hori_pos == HPS_OuterRight )
                             bottom_right_width += (dsize.Width + distance);
                           break;
    default              : ; // no influence on frame hight
  }
  
  switch ( hori_pos )
  {
    case HPS_OuterLeft   : if ( dsize.Width > left_size )
                             left_size = dsize.Width;
                           if ( vert_pos == VPS_InnerTop || vert_pos == VPS_InnerBottom )
                             left_height += (dsize.Height + distance);
                           break;
    case HPS_OuterRight  : if ( dsize.Width > right_size )
                             right_size = dsize.Width;
                           if ( vert_pos == VPS_InnerTop || vert_pos == VPS_InnerBottom )
                             right_height += (dsize.Height + distance);
                           break;
    default              : ;  // no influence on frame width
  }

  return(term);
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

logical OStyleAction :: SetupTreeLayout (OTreeLayout *pOTreeLayout, logical recursive )
{
  OField           *ofield   = NULL;
  ODataSource      *odsource = NULL;
  OListLayout      *column   = NULL;
  OTreeLayout      *region   = NULL;
  OFont_           *fnt      = NULL;
  OCBitmap         *bm       = NULL;
  char             *text     = NULL;
  DSize             hsize;
  int               indx0    = 0;
  logical           term     = NO;
BEGINSEQ
  if ( !pOTreeLayout )                              LEAVESEQ
  
  OElementStyle::SetupTreeLayout(pOTreeLayout,recursive);
  
  if ( !recursive )
  {
    if ( pOTreeLayout->AddSubRegions(GetID()) )      ERROR
    LEAVESEQ
  }
  
  indx0 = 0;
  while ( ofield = Region(indx0++) )
  {
    odsource = &ofield->get_dataSource();
    if ( region = pOTreeLayout->AddRegion((char *)odsource->GetPath(),odsource->get_isCollection(),
                                          odsource->get_structureName(),
                                          odsource->get_sortOrder(),odsource->GetPathType(),
                                          odsource->get_accmode()) )
    {
      if ( text = ofield->GetTitle(odsource) )
        region->SetStaticText(text);
      ofield->SetupTreeLayout(region,!region->IsRecursive(ofield->GetID()));
    }
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Toolbars - 


\return toolbars - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Toolbars"

DLL(OToolBox) *OStyleAction :: Toolbars ( )
{

  return(tool_bars);

}

/******************************************************************************/
/**
\brief  ~OStyleAction - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OStyleAction"

     OStyleAction :: ~OStyleAction ( )
{

  if ( !Deleting() )
    Reset();
    
  delete fields;
  fields = NULL;
  
  delete columns;
  columns = NULL;

  delete regions;
  regions = NULL;

  delete buttons;
  buttons = NULL;

  delete tool_bars;
  tool_bars = NULL;

  delete reactions;
  reactions = NULL;

}


