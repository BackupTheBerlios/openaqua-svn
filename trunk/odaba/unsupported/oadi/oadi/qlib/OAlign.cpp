/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OAlign



\date     $Date: 2006/04/28 16:39:38,81 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OAlign"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sPropertyHandle.hpp>
#include  <sOAlign.hpp>


/******************************************************************************/
/**
\brief  OAlign

-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OAlign"

     OAlign :: OAlign ( )
                     : OPersistent (),
DAlign ()
{
}

/******************************************************************************/
/**
\brief  i01


\param  bcOPersistent
\param  bcDAlign
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OAlign"

     OAlign :: OAlign (OPersistent bcOPersistent, DAlign bcDAlign )
                     :  OPersistent(bcOPersistent)
,DAlign(bcDAlign)
{
/*
  "OAlign("
  +        ADK_Persistent::Generate()
  + ", " + ADK_DAlign::Generate(
               hori
             , vert
             , hori_cell
             , hori_sizing
             , hori_sizing_rate
             , vert_cells
             , vert_sizing
             , vert_sizing_rate
             , ADK_DMargin::Generate(margin)
             , position
           )
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

logical OAlign :: Read (PropertyHandle *ph )
{
  DMargin                 t_margin;
  logical                 term = NO;

  OPersistent::Read(ph);
 
  (int&)position       = ph->GetInt( "position" );
  (int&)arrange        = ph->GetInt( "arrange" );
  (int&)hori           = ph->GetInt( "hori" );
  (int&)vert           = ph->GetInt( "vert" );
  (int&)horiSizing     = ph->GetInt( "hori_sizing" );
  (int&)vertSizing     = ph->GetInt( "vert_sizing" );
  (int&)horiSizingRate = ph->GetInt( "hori_sizing_rate" );
  (int&)horiCells      = ph->GetInt( "hori_cell" );
  (int&)vertSizingRate = ph->GetInt( "vert_sizing_rate" );
  (int&)vertCells      = ph->GetInt( "vert_cell" );
  
  t_margin       = MARGIN2DMARGIN( *PHREF( ph->GetPropertyHandle( "margin" ) ) );
  if ( !t_margin.IsEmpty() )
    margin = t_margin;
  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OAlign :: Reset ( )
{
  *(DAlign *)this = DAlign();
}

/******************************************************************************/
/**
\brief  ~OAlign


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OAlign"

     OAlign :: ~OAlign ( )
{
}


