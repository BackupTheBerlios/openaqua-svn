/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODLLItem

\brief    


\date     $Date: 2006/03/13 21:33:52,20 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODLLItem_HPP
#define   ODLLItem_HPP

class     ODLLItem;

#pragma pack(4)

class  ODLLItem
{
public     :         void                                        *prev;                                                      //
public     :         void                                        *next;                                                      //
public     :         int64                                        timetag;                                                   //

public     :
public     :                                                             ODLLItem ( )                     : prev(0),
next(0),
timetag(0)
{



}

};

#pragma pack()
#endif
