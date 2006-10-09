/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:32:37,32}|(REF)
\class    ActivityManagerI

\brief    


\date     $Date: 2006/03/13 21:32:40,73 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ActivityManagerI_HPP
#define   ActivityManagerI_HPP

class     ActivityManagerI;

class     ActivityManagerPrivate;
#include  <sActivityHandler.hpp>
#include  <sActivityVoidFunctor.hpp>
#pragma pack(4)

class  ActivityManagerI
{
protected  :         typedef ActivityHandler<void,void>::DoF      DoF;                                                       //
protected  :         logical                                      running;                                                   //
protected  :         ActivityManagerPrivate                      *p;                                                         //

public     :
public     :         OADI8ImpExp                                         ActivityManagerI ( );
protected  :         OADI8ImpExp                 ActivityHandler<void,void> &Add (const char *cszName_0=0 );
protected  :         OADI8ImpExp                 logical Execute (void *pvoidSender, void *pvoid, const DoF &rcDoF );
public     :         OADI8ImpExp                 void Remove (const char *cszName );
protected  :                                     void flushAddList ( );
public     :         OADI8ImpExp                                         ~ActivityManagerI ( );
};

#pragma pack()
#endif
