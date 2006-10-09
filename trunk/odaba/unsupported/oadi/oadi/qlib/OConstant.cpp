/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OConstant



\date     $Date: 2006/04/28 12:33:11,04 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OConstant"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sOFrameStyle.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTControl.hpp>
#include  <sTProjectManager.hpp>
#include  <sOConstant.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OConstant :: CastPointer (char *typenames )
{

  return (   !typenames                     ? NULL
           : !strcmp(typenames,"OConstant") ? this
                                            : OConstantControl::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  OConstant

-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OConstant"

     OConstant :: OConstant ( )
                     : OConstantControl ()
{
}

/******************************************************************************/
/**
\brief  i01


\param  bcOConstantControl
\param  pOConstantControl
\param  pOFrameStyle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OConstant"

     OConstant :: OConstant (OConstantControl bcOConstantControl, OConstantControl *pOConstantControl, OFrameStyle *pOFrameStyle )
                     : OConstantControl (bcOConstantControl),
  constControl(pOConstantControl),
  frameStyle(pOFrameStyle)
{
  *(OConstantControl *)this = *constControl;

/*
  "OConstant("
  + ADK_ConstantControl::Generate()
  + ", " + const_data.Generate()
  + ", " + frame_style.Generate()
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

TControl *OConstant :: Open (TControl *tparent, logical active_f )
{
  TControl                 *t = NULL;
  if ( t = OpenControl("OConstant",tparent,frameStyle,this) )
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

logical OConstant :: Read (PropertyHandle *ph )
{
  logical                 term = NO;
BEGINSEQ
  if ( constControl = CACHE_READ(ph,"const_data",OConstantControl) )
    *(OConstantControl *)this = *constControl;
//  else if ( autoOpen )                            OADIERR(99)
    
  UpdateStyleElement(ph);
  
  frameStyle = new OFrameStyle;
  if ( ph = PHREF(ph->GPH("frame_style")) )
    frameStyle->Read(ph);
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

void OConstant :: Reset ( )
{
  int          ic = in_cache;
  logical      iv = invalid;
  OConstantControl occ;
  *(OConstantControl *)this = occ;
  in_cache = ic;
  invalid  = iv;
    
  delete frameStyle;
  frameStyle = NULL;

  if ( constControl )
    constControl->Release();
  constControl = NULL;


}

/******************************************************************************/
/**
\brief  ~OConstant


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OConstant"

     OConstant :: ~OConstant ( )
{
  if ( !Deleting() )
    Reset();
}


