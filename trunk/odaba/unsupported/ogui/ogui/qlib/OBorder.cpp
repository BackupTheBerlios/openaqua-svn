/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OBorder

\brief    


\date     $Date: 2006/03/13 21:35:11,14 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OBorder"

#include  <pogui7.h>
#include  <sDBorder.hpp>
#include  <sOBorder.hpp>


/******************************************************************************/
/**
\brief  FromDBorder - 



\param  pDBorder -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromDBorder"

void OBorder :: FromDBorder (DBorder *pDBorder )
{

  if ( !pDBorder )
  {
    type          = QFrame::NoFrame;
    shadow_type   = QFrame::Plain;
    line_with     = 0;
    mid_line_with = 0;    
  }
  else
  {
    line_with     = pDBorder->get_line_with();
    mid_line_with = pDBorder->get_mid_line_with();

    switch ( pDBorder->get_type() )
    {
      case BS_Box            : type = QFrame::Box;           break;
      case BS_HorizontalLine : type = QFrame::HLine;         break;
      case BS_VerticalLine   : type = QFrame::VLine;         break;
      case BS_Panel          :
      default                : type = QFrame::Panel;
    }

    switch ( pDBorder->get_shadow_type() )
    {
      case BSS_Raised        : shadow_type = QFrame::Raised; break;
      case BSS_Sunken        : shadow_type = QFrame::Sunken; break;
      case BSS_Plain         : 
      default                : shadow_type = QFrame::Plain;
    }
  }

}

/******************************************************************************/
/**
\brief  OBorder - Konstruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OBorder"

                        OBorder :: OBorder ( )
                     :   type(QFrame::Panel),
  shadow_type(QFrame::Plain),
  line_with(1),
  mid_line_with(0)
{



}


