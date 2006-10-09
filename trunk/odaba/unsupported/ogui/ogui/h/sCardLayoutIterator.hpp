/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    CardLayoutIterator

\brief    


\date     $Date: 2006/03/13 21:33:33,40 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CardLayoutIterator_HPP
#define   CardLayoutIterator_HPP

class     CardLayoutIterator;

class  CardLayoutIterator
{
protected  :         int                                          idx;                                                       //
protected  :         std::vector<QLayoutItem*>                   *list;                                                      //

public     :
public     :         OGUI7ImpExp                                         CardLayoutIterator (std::vector<QLayoutItem*> *pv_QLayoutItem );
public     :         OGUI7ImpExp                 QLayoutItem *current ( );
public     :         OGUI7ImpExp                 QLayoutItem *next ( );
public     :         OGUI7ImpExp                 QLayoutItem *takeCurrent ( );
};

#endif
