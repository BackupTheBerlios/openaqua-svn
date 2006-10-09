/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OAccel

\brief    


\date     $Date: 2006/03/13 21:35:09,92 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OAccel"

#include  <pogui7.h>
#include  <sOSlotRouter.hpp>
#include  <sOSlotRouterExtended.hpp>
#include  <sOAccel.hpp>


/******************************************************************************/
/**
\brief  InitList - 



\param  pOSlotRouterE -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitList"

void OAccel :: InitList (OSlotRouterExtended *pOSlotRouterE )
{

/*  
  connectItem(insertItem(Key_A  + CTRL) ,pOSlotRouterE,SLOT(Append()));
  connectItem(insertItem(Key_F2)        ,pOSlotRouterE,SLOT(Edit()));
  connectItem(insertItem(Key_A  + CTRL) ,pOSlotRouterE,SLOT(Append()));
  connectItem(insertItem(Key_I  + CTRL) ,pOSlotRouterE,SLOT(Insert()));
  connectItem(insertItem(Key_D  + CTRL) ,pOSlotRouterE,SLOT(Delete()));
  connectItem(insertItem(Key_F1 + SHIFT),pOSlotRouterE,SLOT(InsertHelp()));
  connectItem(insertItem(Key_F2)        ,pOSlotRouterE,SLOT(Edit()));
  connectItem(insertItem(Key_F7)        ,pOSlotRouterE,SLOT(Find()));
  connectItem(insertItem(Key_F7 + SHIFT),pOSlotRouterE,SLOT(SetFilter()));
  connectItem(insertItem(Key_F7 + CTRL) ,pOSlotRouterE,SLOT(ResetFilter()));
*/

}

/******************************************************************************/
/**
\brief  InitMultiLine - 



\param  pOSlotRouterE -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitMultiLine"

void OAccel :: InitMultiLine (OSlotRouterExtended *pOSlotRouterE )
{

/*
  connectItem(insertItem(Key_A  + CTRL) ,pOSlotRouterE,SLOT(Append()));
  connectItem(insertItem(Key_F2)        ,pOSlotRouterE,SLOT(Edit())); // == maximize
*/

}

/******************************************************************************/
/**
\brief  InitSingleLine - 



\param  pOSlotRouterE -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitSingleLine"

void OAccel :: InitSingleLine (OSlotRouterExtended *pOSlotRouterE )
{

/*  
  connectItem(insertItem(Key_F2)        ,pOSlotRouterE,SLOT(Edit())); // == maximize
  connectItem(insertItem(Key_F1 + SHIFT),pOSlotRouterE,SLOT(InsertHelp()));
  connectItem(insertItem(Key_F2)        ,pOSlotRouterE,SLOT(Edit()));
*/

}

/******************************************************************************/
/**
\brief  OAccel - 



\param  pQWidget -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OAccel"

                        OAccel :: OAccel (QWidget *pQWidget )
                     : QShortcut (pQWidget)
{



}


