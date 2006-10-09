/********************************* Class Source Code ***************************/
/**
\package  ODCP - 
\class    DesignerModeFactory

\brief    


\date     $Date: 2006/07/05 14:04:38,22 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DesignerModeFactory"

#include  <podcp8.h>
#include  <cqt.h>
#include  <sDesignerMode.hpp>
#include  <sOWidget.hpp>
#include  <sOWidgetDesignModeBase.hpp>
#include  <sDesignerModeFactory.hpp>


/******************************************************************************/
/**
\brief  CreateDM - 



\return odwm - 

\param  pOWidget - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateDM"

OWidgetDesignModeBase *DesignerModeFactory :: CreateDM (OWidget *pOWidget )
{
OWidgetDesignModeBase            *design_mode;
design_mode = ((OWidgetDesignModeBase*) new DesignerMode(pOWidget));
design_mode->Initialize();
return design_mode;
}


