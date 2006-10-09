/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OButtonControl



\date     $Date: 2006/04/28 17:09:59,26 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OButtonControl"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sOADKFactory.hpp>
#include  <sOCAU_Action.hpp>
#include  <sOSButton.hpp>
#include  <sPropertyHandle.hpp>
#include  <sOButtonControl.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OButtonControl :: CastPointer (char *typenames )
{

  return (   !typenames                          ? NULL
           : !strcmp(typenames,"OButtonControl") ? this
                                                 : OActionControl::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  GetFrameSize

\return dsize

\param  dsize
\param  field_margin
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFrameSize"

DSize OButtonControl :: GetFrameSize (DSize dsize, DMargin &field_margin )
{
  int    margin = align.get_margin().Maximum();

  return( DSize(dsize.Width + align.get_margin().Left+align.get_margin().Right,
                dsize.Height + align.get_margin().Top+align.get_margin().Bottom) );

  return(dsize);
}

/******************************************************************************/
/**
\brief  OButtonControl

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OButtonControl"

     OButtonControl :: OButtonControl ( )
                     : OActionControl ()
{


}

/******************************************************************************/
/**
\brief  i01


\param  bcOActionControl
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OButtonControl"

     OButtonControl :: OButtonControl (OActionControl bcOActionControl )
                     : OActionControl (bcOActionControl)
{
   style = ADKFACTORY(NULL,OSButton);
/*
  "OButtonControl("
  + ADK_ActionControl::Generate()
  + ")";
*/
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

logical OButtonControl :: Read (PropertyHandle *ph )
{

  OActionControl::Read(ph);

  if ( style && !OI_CAST(OSButton,style) )
  {
    style->Release();
    style = NULL;
  }
    
  if ( !style )
    style = ADKFACTORY(NULL,OSButton);

  return(NO);
}

/******************************************************************************/
/**
\brief  ~OButtonControl


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OButtonControl"

     OButtonControl :: ~OButtonControl ( )
{
}


