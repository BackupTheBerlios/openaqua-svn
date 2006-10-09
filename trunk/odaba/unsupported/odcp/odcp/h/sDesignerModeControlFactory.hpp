/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/15|12:48:28,62}|(REF)
\class    DesignerModeControlFactory



\date     $Date: 2006/03/27 15:51:45,00 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DesignerModeControlFactory_HPP
#define   DesignerModeControlFactory_HPP

class     DesignerModeControlFactory;

class     OWidget;
class     OWidgetDesignModeBase;
#include  <sOWidgetDesignModeFactory.hpp>
class  DesignerModeControlFactory :public OWidgetDesignModeFactory
{

public     :
public     :                                     OWidgetDesignModeBase *CreateDM (OWidget *pOWidget );
};

#endif
