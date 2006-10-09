/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    DLayout

\brief    


\date     $Date: 2006/03/13 21:35:00,93 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DLayout"

#include  <pogui7.h>
#include  <sDBrush.hpp>
#include  <sDLayout.hpp>


/******************************************************************************/
/**
\brief  DLayout - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DLayout"

                        DLayout :: DLayout ( )
                     :   shape()
{

  Initialize();

}

/******************************************************************************/
/**
\brief  Initialize - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void DLayout :: Initialize ( )
{

  memset(active,0,sizeof(active));
  memset(inactive,0,sizeof(inactive));
  memset(disabled,0,sizeof(disabled));


}

/******************************************************************************/
/**
\brief  Reset - 



\param  del_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void DLayout :: Reset (logical del_opt )
{
  int       indx0;
  if ( del_opt )
    for ( indx0 = 0; indx0 < 20; indx0++ )
    {
      delete active[indx0];
      delete inactive[indx0];
      delete disabled[indx0];
    }
    
  Initialize();

}

/******************************************************************************/
/**
\brief  SetActive - 



\param  rQPalette -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActive"

void DLayout :: SetActive (QPalette &rQPalette )
{

  SetColorGroup(rQPalette,QPalette::Active,active);

}

/******************************************************************************/
/**
\brief  SetColorGroup - 



\param  rQPalette -
\param  color_group -
\param  brushs[20] -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetColorGroup"

void DLayout :: SetColorGroup (QPalette &rQPalette, QPalette::ColorGroup color_group, DBrush *brushs[20] )
{
  int          indx0 = 0;
  while ( indx0 < QT_MAXCOLOR_ROLES )
  {
    if ( brushs[indx0] )
      rQPalette.setBrush(color_group,
                         (QPalette::ColorRole)indx0,
                         brushs[indx0]->ToQBrush());
    indx0++;
  }


}

/******************************************************************************/
/**
\brief  SetDisabled - 



\param  rQPalette -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDisabled"

void DLayout :: SetDisabled (QPalette &rQPalette )
{

  SetColorGroup(rQPalette,QPalette::Disabled,disabled);


}

/******************************************************************************/
/**
\brief  SetInactive - 



\param  rQPalette -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInactive"

void DLayout :: SetInactive (QPalette &rQPalette )
{

  SetColorGroup(rQPalette,QPalette::Inactive,inactive);


}

/******************************************************************************/
/**
\brief  SetPalette - 



\param  rQPalette -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPalette"

void DLayout :: SetPalette (QPalette &rQPalette )
{

  SetActive(rQPalette);
  SetInactive(rQPalette);
  SetDisabled(rQPalette);

}

/******************************************************************************/
/**
\brief  ~DLayout - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DLayout"

                        DLayout :: ~DLayout ( )
{

  Reset(YES);

}


