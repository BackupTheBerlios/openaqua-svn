/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:32:37,32}|(REF)
\class    ActivityManagerPrivate

\brief    


\date     $Date: 2006/03/13 21:32:40,90 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ActivityManagerPrivate_HPP
#define   ActivityManagerPrivate_HPP

class     ActivityManagerPrivate;

#ifndef   DLL_AH_HPP
#define   DLL_AH_HPP
#include  <sAH.hpp>
#include  <sDLL.h>
#endif
class     AH;
class  ActivityManagerPrivate
{
public     :         DLL(AH)                                      beforeList;                                                //
public     :         DLL(AH)                                      doList;                                                    //
public     :         DLL(AH)                                      addList;                                                   //

public     :
public     : static                              int __cdecl compareBefore (void *phdl, AH *pAH );
public     : static                              int __cdecl compareDo (void *phdl, AH *pAH );
};

#endif
