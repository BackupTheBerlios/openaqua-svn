/********************************* Class Declaration ***************************/
/**
\package  ODCP
\class    DMCLayoutItem



\date     $Date: 2006/04/24 16:53:27,15 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DMCLayoutItem_HPP
#define   DMCLayoutItem_HPP

class     DMCLayoutItem;

class  DMCLayoutItem :public QLayoutItem
{
protected  :         QRect                                        rectangle;                                                 

public     :
                     QRect                                       &get_rectangle() { return(rectangle); }
public     :                                                             DMCLayoutItem ( );
public     : virtual                             Qt::Orientations expandingDirections ( ) const;
public     : virtual                             QRect geometry ( ) const;
public     : virtual                             bool isEmpty ( ) const;
public     : virtual                             QSize maximumSize ( ) const;
public     : virtual                             QSize minimumSize ( ) const;
public     : virtual                             void setGeometry (const QRect &rqRect );
public     : virtual                             QSize sizeHint ( ) const;
};

#endif
