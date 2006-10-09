/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    FAssociate

\brief    Constructs a Dialog to Associate Items
          displays  a list  of items  of the  basecollection. you can check them
          and say ok to associate the items.
          already associated items will not apear in the list

\date     $Date: 2006/07/26 16:54:15,28 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   FAssociate_HPP
#define   FAssociate_HPP

class     FAssociate;

class     ODS;
class     ODataWidget;
class     OTreeView;
class     QGridLayout;
class     QPushButton;
#include  <sODialog.hpp>
#include  <sPropertyHandle.hpp>
class  FAssociate :public ODialog
{
protected  :                                                      Q_OBJECT;                                                  // 
protected  :         OTreeView                                   *base_list;                                                 // 
protected  :         ODControl                                   *od_control;                                                // 
protected  :         PropertyHandle                              *source;                                                    // 
protected  :         PropertyHandle                               parent;                                                    // 

public     :
                     ODControl                                   *get_od_control() { return(od_control); }
                     PropertyHandle                              *get_source() { return(source); }
public     :                  OGUIImpExp                 FAssociate (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS );
public     :                                        logical InitODControl (char *control_name );
public     :                                        logical Initialize (PropertyHandle *source_ph, char *control_name, char *title );
public     : public slots:                          void ToggleItem (const QModelIndex &model_index );
protected  : private slots:                         void accept ( );
public     :                  OGUIImpExp            logical exec ( );
public     : public slots:                          void slotHideAssociated (logical *pterm );
public     :                                             ~FAssociate ( );
};

#endif
