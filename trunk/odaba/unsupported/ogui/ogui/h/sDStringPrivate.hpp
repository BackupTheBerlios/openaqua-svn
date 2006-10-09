/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    DStringPrivate

\brief    


\date     $Date: 2006/03/13 21:33:38,85 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DStringPrivate_HPP
#define   DStringPrivate_HPP

class     DStringPrivate;

class  DStringPrivate
{
public     :         int                                          refCnt;                                                    
public     :         int                                          length;                                                    
public     :         char                                         data[1];                                                   

public     :
};

#endif
