/********************************* Class Source Code ***************************/
/**
\package  ODCP - 
\class    DesignerModeControlFactory

\brief    


\date     $Date: 2006/07/05 14:04:38,10 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DesignerModeControlFactory"

#include  <podcp8.h>
#include  <cqt.h>
#include  <sDSize.hpp>
#include  <sDesignerModeControl.hpp>
#include  <sOWidget.hpp>
#include  <sOWidgetDesignModeBase.hpp>
#include  <sDesignerModeControlFactory.hpp>


/******************************************************************************/
/**
\brief  CreateDM - 



\return odwm - 

\param  pOWidget - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateDM"

OWidgetDesignModeBase *DesignerModeControlFactory :: CreateDM (OWidget *pOWidget )
{
  OWidgetDesignModeBase            *design_mode;
  design_mode = ((OWidgetDesignModeBase*) new DesignerModeControl(pOWidget));
  design_mode->Initialize();
  return design_mode;
}


