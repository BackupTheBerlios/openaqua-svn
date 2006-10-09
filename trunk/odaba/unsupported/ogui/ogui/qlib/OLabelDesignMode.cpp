/********************************* Class Source Code ***************************/
/**
\package  OGUI
\class    OLabelDesignMode



\date     $Date: 2006/05/22 18:00:27,33 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OLabelDesignMode"

#include  <pogui7.h>
#include  <cqt.h>
#include  <mOLabelDesignMode.h>
#include  <sOLabel.hpp>
#include  <sOWidget.hpp>
#include  <sOLabelDesignMode.hpp>


/******************************************************************************/
/**
\brief  CMChangeText - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CMChangeText"

void OLabelDesignMode :: CMChangeText ( )
{
  logical cond  = NO;
  QString qtext;
  QWidget *control_widget = NULL; //j
  qtext = QInputDialog::getText((QWidget *) control_widget
                               ,tr("Set Label Text")
                               ,QString::null
                               ,QLineEdit::Normal
                               ,SZ2QS(olabel->GetText())
                               ,(bool*)&cond
                                );
  
  if ( cond )
    olabel->setText(qtext);

}

/******************************************************************************/
/**
\brief  CreateContextMenu - create context menu
        this function builds the olabels context menu for design mode.
        (see OWidgetDesignMode::CreateContextMenu() for details).

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateContextMenu"

logical OLabelDesignMode :: CreateContextMenu ( )
{
  logical term        = NO;
  OWidgetDesignMode::CreateContextMenu();

  context_menu->addSeparator();
  context_menu->addAction(SZ2QS("&Change Text"), this, SLOT(CMChangeText()));

  return (term);
}

/******************************************************************************/
/**
\brief  OLabelDesignMode - Konstruktor



\param  pOLabel
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OLabelDesignMode"

     OLabelDesignMode :: OLabelDesignMode (OLabel *pOLabel )
                     : OWidgetDesignMode (pOLabel),
  olabel(pOLabel)
{
BEGINSEQ
  if ( !pOLabel )                                    OGUIERR(99)

RECOVER
ENDSEQ
}

/******************************************************************************/
/**
\brief  ~OLabelDesignMode - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OLabelDesignMode"

     OLabelDesignMode :: ~OLabelDesignMode ( )
{
}


