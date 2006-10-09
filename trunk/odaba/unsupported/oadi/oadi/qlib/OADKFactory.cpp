/********************************* Class Source Code ***************************/
/**
\package  OADI - 
\class    OADKFactory

\brief    


\date     $Date: 2006/06/19 18:46:05,21 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OADKFactory"

#include  <poadi.h>
#include  <cfctp.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sOADKFactory.hpp>
#include  <sOAction.hpp>
#include  <sOApplication.hpp>
#include  <sOBitmap.hpp>
#include  <sOBrush.hpp>
#include  <sOButton.hpp>
#include  <sOCAU_Action.hpp>
#include  <sOCAU_SimpleAction.hpp>
#include  <sOCBitmap.hpp>
#include  <sOColorGroup.hpp>
#include  <sOConstAction.hpp>
#include  <sOField.hpp>
#include  <sOFieldControl.hpp>
#include  <sOFont_.hpp>
#include  <sOFrameStyle.hpp>
#include  <sOFunctAction.hpp>
#include  <sOHighlightRule.hpp>
#include  <sOHighlighter.hpp>
#include  <sOJumpAction.hpp>
#include  <sOLayout.hpp>
#include  <sOMenAction.hpp>
#include  <sOMenu.hpp>
#include  <sOProject.hpp>
#include  <sOSButtonBox.hpp>
#include  <sOSButtonGroup.hpp>
#include  <sOSCheckBox.hpp>
#include  <sOSDate.hpp>
#include  <sOSEdit.hpp>
#include  <sOSGroupBox.hpp>
#include  <sOSListBox.hpp>
#include  <sOSRadioGroup.hpp>
#include  <sOSSplitter.hpp>
#include  <sOSTabControl.hpp>
#include  <sOSTime.hpp>
#include  <sOSWindow.hpp>
#include  <sOSyntaxClass.hpp>
#include  <sOToolBox.hpp>
#include  <sOWinAction.hpp>
#include  <sOWindow.hpp>
#include  <sPropertyHandle.hpp>
#include  <scftd.hpp>
#include  <sOADKFactory.hpp>

OADKFactory            * factory = NULL;

/******************************************************************************/
/**
\brief  Factory - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Factory"

OADKFactory *__cdecl OADKFactory :: Factory ( )
{

  if ( !factory ) 
    factory = new OADKFactory;

  return factory;
}

/******************************************************************************/
/**
\brief  New - 


\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  ph - 
\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "New"

void *OADKFactory :: New (PropertyHandle *ph, char *typenames )
{
  char      *ph_type = ph ? ph->GetCurrentType() : "";
  cftd      *cftdptr = NULL;
  char       name[ID_SIZE];
  void      *res     = NULL;
BEGINSEQ
  if ( !ph )
    res = New(typenames);
  else
  {
    cftdsrt->srtsor(CFTE_KPS,CFTE_KLN,CFTE_KTP);
    if ( cftdptr = (cftd *)cftdsrt->srtigt(cftdsrt->srtssr(gvtxstb(name,ph_type,ID_SIZE))) )
    {
      cftdptr->VoidCall(&res);
      if ( !res )                                   ERROR
      if ( !((OResource *)res)->CastPointer(typenames) )
                                                    OADIERR(99)
    }
    else                                            ERROR
  }

RECOVER
  OADIEV1(*ph_type ? ph_type : "empty PH-type",ID_SIZE);
  OADISET(103)

ENDSEQ
  return(res);

}

/******************************************************************************/
/**
\brief  i01 - 


\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "New"

void *OADKFactory :: New (char *typenames )
{
  cftd      *cftdptr = NULL;
  char       name[ID_SIZE];
  void      *res     = NULL;
BEGINSEQ
  if ( !typenames )                                 ERROR

  cftdsrt->srtsor(CFTD_KPS,CFTD_KLN,CFTD_KTP);
  if ( cftdptr = (cftd *)cftdsrt->srtigt(cftdsrt->srtssr(gvtxstb(name,typenames,ID_SIZE))) )
    cftdptr->VoidCall(&res);
  else                                              ERROR
RECOVER
  OADIEV1(typenames ? typenames : "empty type",ID_SIZE);
  OADISET(103)

ENDSEQ
  return(res);
}

/******************************************************************************/
/**
\brief  OADKFactory - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OADKFactory"

     OADKFactory :: OADKFactory ( )
                     :   cftdsrt(NULL)
{

  static cftd table[] = {
    cftd("ADA_WinAction",          "OWinAction",SLINK(OWinAction,CreateInstance)),
    cftd("ADK_Application",        "OApplication",SLINK(OApplication,CreateInstance)),
    cftd("ADK_Bitmap",             "OBitmap",SLINK(OBitmap,CreateInstance)),
    cftd("ADK_Brush",              "OBrush",SLINK(OBrush,CreateInstance)),
    cftd("ADK_Button",             "OButton",SLINK(OButton,CreateInstance)),
    cftd("ADK_ColorGroup",         "OColorGroup",SLINK(OColorGroup,CreateInstance)),
    cftd("ADK_EventAction",        "OEventAction",SLINK(OEventAction,CreateInstance)),
    cftd("ADK_EventActionControl", "OEventActionControl",SLINK(OEventActionControl,CreateInstance)),
    cftd("ADK_Field",              "OField",SLINK(OField,CreateInstance)),
    cftd("ADK_FieldControl",       "OFieldControl",SLINK(OFieldControl,CreateInstance)),
    cftd("ADK_Font",               "OFont_",SLINK(OFont_,CreateInstance)),
    cftd("ADK_Highlighter",        "OHighlighter",SLINK(OHighlighter,CreateInstance)),
    cftd("ADK_HighlightRule",      "OHighlightRule",SLINK(OHighlightRule,CreateInstance)),
    cftd("ADK_Layout",             "OLayout",SLINK(OLayout,CreateInstance)),
    cftd("ADK_Menu",               "OMenu",SLINK(OMenu,CreateInstance)),
    cftd("ADK_Project",            "OProject",SLINK(OProject,CreateInstance)),
    cftd("ADK_Style",              "OStyle",SLINK(OStyle,CreateInstance)),
    cftd("ADK_SyntaxClass",        "OSyntaxClass",SLINK(OSyntaxClass,CreateInstance)),
    cftd("ADK_ToolBox",            "OToolBox",SLINK(OToolBox,CreateInstance)),
    cftd("ADK_Window",             "OWindow",SLINK(OWindow,CreateInstance)),
    cftd("ADKC_Bitmap",            "OCBitmap",SLINK(OCBitmap,CreateInstance)),
    cftd("ADKS_ButtonGroup",       "OSButtonGroup",SLINK(OSButtonGroup,CreateInstance)),
    cftd("ADKS_ButtonBox",         "OSButtonBox",SLINK(OSButtonBox,CreateInstance)),
    cftd("ADKS_CheckBox",          "OSCheckBox",SLINK(OSCheckBox,CreateInstance)),
    cftd("ADKS_Date",              "OSDate",SLINK(OSDate,CreateInstance)),
    cftd("ADKS_Edit",              "OSEdit",SLINK(OSEdit,CreateInstance)),
    cftd("ADKS_GroupBox",          "OSGroupBox",SLINK(OSGroupBox,CreateInstance)),
    cftd("ADKS_ListBox",           "OSListBox",SLINK(OSListBox,CreateInstance)),
    cftd("ADKS_RadioGroup",        "OSRadioGroup",SLINK(OSRadioGroup,CreateInstance)),
    cftd("ADKS_Splitter",          "OSSplitter",SLINK(OSSplitter,CreateInstance)),
    cftd("ADKS_Time",              "OSTime",SLINK(OSTime,CreateInstance)),
//    cftd("ADKS_StatLine",          "OSStatLine",SLINK(OSStatLine,CreateInstance)),
//    cftd("ADKS_Symbol",            "OSSymbol",SLINK(,CreateInstance)),
    cftd("ADKS_Tab",               "OSTabControl",SLINK(OSTabControl,CreateInstance)),
    cftd("ADKS_Window",            "OSWindow",SLINK(OSWindow,CreateInstance)),
    cftd("CAU_Action",             "OCAU_Action",SLINK(OCAU_Action,CreateInstance)),
    cftd("CAU_simpleAction",       "OCAU_SimpleAction",SLINK(OCAU_SimpleAction,CreateInstance)),
  };
  cftdsrt = new srt(sizeof(table)/CFTD,CFTD,UNDEF,UNDEF,UNDEF,(char *)table,NO);

}

/******************************************************************************/
/**
\brief  ~OADKFactory - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OADKFactory"

     OADKFactory :: ~OADKFactory ( )
{

  delete cftdsrt;
  cftdsrt = NULL;

}


