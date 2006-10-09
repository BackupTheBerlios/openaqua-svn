/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|16:34:35,87}|(REF)
\class    ODDesktop

\brief    


\date     $Date: 2006/03/23 20:02:59,18 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODDesktop"

#include  <pogui7.h>
#include  <cguimac.h>
#include  <sOApplicationO.hpp>
#include  <sODesktopO.hpp>
#include  <sODDesktop.hpp>


/******************************************************************************/
/**
\brief  GetSize - 


\return DSize -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSize"

DSize ODDesktop :: GetSize ( )
{

  return(QSIZE2DSIZE(QApplication::desktop()->size()));


}

/******************************************************************************/
/**
\brief  ODDesktop - Konstruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODDesktop"

                        ODDesktop :: ODDesktop ( )
                     : ODControl (NULL,"DESKTOP")
{

  frameInnerWidget = 
  frameOuterWidget = ((OApplicationO *)qApp)->desktop();

}

/******************************************************************************/
/**
\brief  ~ODDesktop - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODDesktop"

                        ODDesktop :: ~ODDesktop ( )
{



}


