/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OWindow



\date     $Date: 2006/04/28 18:22:58,65 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OWindow"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sOADKFactory.hpp>
#include  <sODataSource.hpp>
#include  <sODataSourceHaving.hpp>
#include  <sOFieldControl.hpp>
#include  <sOSWindow.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTControl.hpp>
#include  <sTProjectManager.hpp>
#include  <sOWindow.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OWindow :: CastPointer (char *typenames )
{

  return (   !typenames                       ? NULL
           : !strcmp(typenames,"OWindow")     ? this
           : !strcmp(typenames,"OFrameStyle") ? (OFrameStyle *)this
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

int32 OWindow :: CreateInstance (void **instptrp )
{

  *instptrp = new OWindow();
  return(0);

}

/******************************************************************************/
/**
\brief  OWindow

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OWindow"

     OWindow :: OWindow ( )
                     : OFieldControl (),
OFrameStyle (),
  fieldControl(NULL),
  ds_having(NULL)
{



}

/******************************************************************************/
/**
\brief  i01


\param  bcOFieldControl
\param  bcOFrameStyle
\param  pOFieldControl
\param  pODataSourceHaving
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OWindow"

     OWindow :: OWindow (OFieldControl bcOFieldControl, OFrameStyle bcOFrameStyle, OFieldControl *pOFieldControl, ODataSourceHaving *pODataSourceHaving )
                     :  OFieldControl (bcOFieldControl)
,OFrameStyle (bcOFrameStyle)
,fieldControl(pOFieldControl)
,ds_having(pODataSourceHaving)
{
 /* 
  " OWindow( "
   +        ADK_FieldControl::Generate(field_control)
   + ", " + ADK_FrameStyle::Generate()
   + ", " + field_control.Generate()
   + ", " + ???
   + ", NULL " // OWinAction will Set It
   + ")";
  */

}

/******************************************************************************/
/**
\brief  Open

\return pTControl

\param  typenames
\param  tparent
\param  active_f
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

TControl *OWindow :: Open (char *typenames, TControl *tparent, logical active_f )
{
  TControl        *t = NULL;
  OStyleAction    *p;
  if ( !typenames )
    typenames = "OWindow";

  t = OpenControl(typenames,tparent,this,this);

  if ( t )
    if ( active_f )
{      
      t->Activate();
}
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

logical OWindow :: Read (PropertyHandle *ph )
{
  OStyleAction    *p;
  logical          term = NO;
BEGINSEQ
  OFrameStyle::Read(ph);

  if ( !(fieldControl = CACHE_READ(ph,CC fieldControlPHName(),OFieldControl)) )
                                                     OADIERR(99)
  *(OFieldControl *)this = *fieldControl;
  UpdateStyleElement(ph);
  OResource::Read(ph);

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

void OWindow :: Reset ( )
{

  OFieldControl ofc;
  *(OFieldControl *)this = ofc;  // das koennte zu einfach sein
    
  if ( fieldControl )
    fieldControl->Release();
  fieldControl = NULL;


}

/******************************************************************************/
/**
\brief  SetDataSourceHaving


\param  pODataSourceHaving
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDataSourceHaving"

void OWindow :: SetDataSourceHaving (ODataSourceHaving *pODataSourceHaving )
{
  ds_having = pODataSourceHaving;
}

/******************************************************************************/
/**
\brief  fieldControlPHName

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fieldControlPHName"

const char *OWindow :: fieldControlPHName ( ) const
{

  return "field_control";

}

/******************************************************************************/
/**
\brief  ~OWindow


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OWindow"

     OWindow :: ~OWindow ( )
{

  if ( !Deleting() )
    Reset();
  else
  {
    OFieldControl ofc;
    *(OFieldControl *)this = ofc;  // das koennte zu einfach sein, vor allen fuer recursiv
    Deleting();  
  }

}


