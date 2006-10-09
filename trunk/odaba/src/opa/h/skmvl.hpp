/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    kmvl

\brief    


\date     $Date: 2006/03/12 19:14:32,53 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   kmvl_HPP
#define   kmvl_HPP

class     kmvl;

class     DBHandle;
class     DBIndex;
class     LACObject;
class     ref;
#include  <cPIACC.h>
#include  <sEB_Number.hpp>
#include  <smvli.hpp>
#pragma pack(8)

class  kmvl :public mvli
{

public     :
public     :                                     EB_Number *GetExtRef (ref *refptr );
public     :                                     logical IsEmpty ( );
public     :                                     EB_Number *ProvideExtRef (ref *refptr, PIACC accopt );
public     :                                                             kmvl (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, uint16 version, logical globind );
public     :                                                             ~kmvl ( );
};

#pragma pack()
#endif
