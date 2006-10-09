/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OWidgetDesignModeFactory

\brief    


\date     $Date: 2006/03/13 21:34:52,93 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OWidgetDesignModeFactory_HPP
#define   OWidgetDesignModeFactory_HPP

class     OWidgetDesignModeFactory;

class     OWidget;
class     OWidgetDesignMode;
class     OWidgetDesignModeBase;
class  OWidgetDesignModeFactory
{

public     :
public     : virtual OGUI7ImpExp                 OWidgetDesignModeBase *CreateDM (OWidget *pOWidget );
};

#endif
