/********************************* Class Declaration ***************************/
/**
\package  ODCP
\class    DesignerModeControl



\date     $Date: 2006/05/22 17:57:56,76 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DesignerModeControl_HPP
#define   DesignerModeControl_HPP

class     DesignerModeControl;

class     CTX_Design;
class     OWidget;
#include  <sDSize.hpp>
#include  <sOWidgetDesignModeBase.hpp>
class  DesignerModeControl :public OWidgetDesignModeBase
{
protected  :         CTX_Design                                  *ctx_design;                                                
protected  :         QWidget                                     *client_qwidget;                                            
protected  :         QWidget                                     *control_qwidget;                                           
protected  :         QGridLayout                                 *grid;                                                      
protected  :         QGridLayout                                 *grid_backup;                                               
protected  :         QWidget                                     *viewport;                                                  
protected  :         logical                                      preview;                                                   

public     :
                     CTX_Design                                  *get_ctx_design() { return(ctx_design); }
public     : virtual          ODCPImpExp            QPoint CellizePosition (const QPoint rcQPos );
public     : virtual          ODCPImpExp            logical ChildEvent (QChildEvent *pQChildEvent, QWidget *event_target );
public     :                                             DesignerModeControl (OWidget *pOWidget );
public     :                                        logical DropEvent (QDropEvent *pQDropEvent, QWidget *event_target );
public     :                                        logical Event (QEvent *pQEvent, QWidget *event_target );
public     :                                        logical HasPreview ( );
public     :                                        DSize InitGrid ( );
public     : virtual          ODCPImpExp            logical Initialize ( );
public     :                                        logical PaintEvent (QPaintEvent *pQPaintEvent, QWidget *event_target );
public     :                                        DSize Preview (logical pv );
public     :                                        logical Refresh ( );
public     :                                        logical SetClientWidget (OWidget *pOWidget );
public     :                                        logical SetContext (CTX_Design *ctx_dsgn );
public     :                                        logical SetControlWidget (OWidget *pOWidget );
public     :                                             ~DesignerModeControl ( );
};

#endif
