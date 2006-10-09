/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    FInsert

\brief    Insert
          Constructs a dialog that inserts a string to a selectable region

\date     $Date: 2006/03/13 21:33:39,84 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   FInsert_HPP
#define   FInsert_HPP

class     FInsert;

class     ODS;
class     ODataWidget;
class     PropertyHandle;
#include  <sODialog.hpp>
class  FInsert :public ODialog
{
protected  :                                                      Q_OBJECT;                                                  //
protected  :         QStandardItemModel                          *meta_model;                                                //
protected  :         QTreeView                                   *meta_tree;                                                 //
protected  :         QLineEdit                                   *line_edit;                                                 //
protected  :         QGridLayout                                 *grid;                                                      //
protected  :         PropertyHandle                              *ph_selected;                                               //
protected  :         QString                                      input_string;                                              //
protected  :         QLabel                                      *label;                                                     //

public     :
                     PropertyHandle                              *get_ph_selected() { return(ph_selected); }
                     QLabel                                      *get_label() { return(label); }
public     :         OGUI7ImpExp                                         FInsert (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS );
public     :                                     PropertyHandle *ResultPH ( );
public     :                                     QString ResultString ( );
public     :                                     public slots: void accept ( );
public     :         OGUI7ImpExp                 logical exec ( );
public     :                                                             ~FInsert ( );
};

#endif
