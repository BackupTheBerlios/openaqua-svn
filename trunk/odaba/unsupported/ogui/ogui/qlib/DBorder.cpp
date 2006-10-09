/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|16:34:35,87}|(REF)
\class    DBorder

\brief    


\date     $Date: 2006/04/10 17:45:10,75 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBorder"

#include  <pogui7.h>
#include  <cguimac.h>
#include  <cqt.h>
#include  <sOBorder.hpp>
#include  <sDBorder.hpp>


/******************************************************************************/
/**
\brief  DBorder - 


-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBorder"

                        DBorder :: DBorder ( )
                     :   type(BS_Panel),
  shadow_type(BSS_Plain),
  line_with(1),
  mid_line_with(1)
{



}

/******************************************************************************/
/**
\brief  i01


\param  bstyle - 
\param  sstyle - 
\param  lwith - 
\param  mlwith - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBorder"

                        DBorder :: DBorder (ADK_BorderStyles bstyle, ADK_ShadowStyles sstyle, int lwith, int mlwith )
                     :   type(bstyle),
  shadow_type(sstyle),
  line_with(lwith),
  mid_line_with(mlwith)
{



}

/******************************************************************************/
/**
\brief  FromOBorder - 



\param  pOBorder - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromOBorder"

void DBorder :: FromOBorder (OBorder *pOBorder )
{

  switch ( pOBorder->get_type() )
  {
    case QFrame::Box     : type = BS_Box;              break;
    case QFrame::HLine   : type = BS_HorizontalLine;   break;
    case QFrame::VLine   : type = BS_VerticalLine;     break;
    case QFrame::Panel   :
    default               : type = BS_Panel;
  }

  switch ( pOBorder->get_shadow_type() )
  {
    case QFrame::Raised  : shadow_type = BSS_Raised;   break;
    case QFrame::Sunken  : shadow_type = BSS_Sunken;   break;
    case QFrame::Plain   : 
    default               : shadow_type = BSS_Plain;
    
  }
  
  line_with     = pOBorder->get_line_with();
  mid_line_with = pOBorder->get_mid_line_with();


}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void DBorder :: Reset ( )
{

  type = BS_Panel;
  shadow_type = BSS_Plain;
  line_with = 1;
  mid_line_with = 1;

}

/******************************************************************************/
/**
\brief  Set - 



\param  bstyle - 
\param  sstyle - 
\param  lwith - 
\param  mlwith - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Set"

void DBorder :: Set (ADK_BorderStyles bstyle, ADK_ShadowStyles sstyle, int lwith, int mlwith )
{

  type          = bstyle;
  shadow_type   = sstyle;
  line_with     = lwith;
  mid_line_with = mlwith;

}


