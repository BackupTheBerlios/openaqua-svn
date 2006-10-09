/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OWidgetDesignModeFactory

\brief    


\date     $Date: 2006/03/13 21:36:25,73 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OWidgetDesignModeFactory"

#include  <pogui7.h>
#include  <sOWidget.hpp>
#include  <sOWidgetDesignMode.hpp>
#include  <sOWidgetDesignModeBase.hpp>
#include  <sOWidgetDesignModeFactory.hpp>


/******************************************************************************/
/**
\brief  CreateDM - 


\return owdm -

\param  pOWidget -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateDM"

OWidgetDesignModeBase *OWidgetDesignModeFactory :: CreateDM (OWidget *pOWidget )
{
OWidgetDesignModeBase            * design_mode;
design_mode = ((OWidgetDesignModeBase*) new OWidgetDesignMode(pOWidget));
design_mode->Initialize();
return design_mode;
}


