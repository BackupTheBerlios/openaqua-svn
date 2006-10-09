/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:32:37,32}|(REF)
\class    ActivityHandler

\brief    


\date     $Date: 2006/03/13 21:32:40,25 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ActivityHandler_HPP
#define   ActivityHandler_HPP


#include  <sActivityHandler.hpp>
#include  <sActivityLogicalFunctor.hpp>
#include  <sActivityVoidFunctor.hpp>
#pragma pack(4)

template < class I, class A >
class  ActivityHandler
{
protected  :         friend class                                 ActivityManagerI;                                          //
protected  :         friend class                                 ActivityManagerPrivate;                                    //
protected  :         typedef ActivityLogicalFunctor<I,A>          BeforeF;                                                   //
protected  :         typedef ActivityVoidFunctor<I,A>             DoF;                                                       //
protected  :         typedef ActivityVoidFunctor<I,A>             CancelF;                                                   //
protected  :         BeforeF                                      beforeF;                                                   //
protected  :         logical                                      beforePre;                                                 //
protected  :         int                                          beforePos;                                                 //
protected  :         DoF                                          doF;                                                       //
protected  :         logical                                      doPre;                                                     //
protected  :         int                                          doPos;                                                     //
protected  :         CancelF                                      cancelF;                                                   //

public     :
protected  :                                                             ActivityHandler ( )                     :   beforeF(),
  beforePre(0),
  beforePos(0),
  doF(),
  doPre(0),
  doPos(0),
  cancelF()
{



}

public     :         OADI8ImpExp                 ActivityHandler &Before (const BeforeF &rcBeforeF, logical fPre, int iPos, const CancelF &rcCancelF_=CancelF() ){

  beforeF   = rcBeforeF; 
  beforePre = fPre;
  beforePos = iPos;
  cancelF   = rcCancelF_;


  return *this;
}

public     :         OADI8ImpExp                 ActivityHandler &Do (const DoF &rcDoF, logical fPre, int iPos ){

  doF   = rcDoF;
  doPre = fPre;
  doPos = iPos;


  return *this;
}

};

#pragma pack()
#endif
