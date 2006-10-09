/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:39:49,98}|(REF)
\class    DesignerModeFactory

\brief    


\date     $Date: 2006/03/12 19:40:02,43 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DesignerModeFactory_HPP
#define   DesignerModeFactory_HPP

class     DesignerModeFactory;

class     OWidget;
class     OWidgetDesignModeBase;
#include  <sOWidgetDesignModeFactory.hpp>
class  DesignerModeFactory :public OWidgetDesignModeFactory
{

public     :
public     : virtual ODCP8ImpExp                 OWidgetDesignModeBase *CreateDM (OWidget *pOWidget );
};

#endif
