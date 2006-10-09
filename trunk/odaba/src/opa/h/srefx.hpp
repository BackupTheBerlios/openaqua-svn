/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    refx

\brief    


\date     $Date: 2006/03/12 19:15:07,64 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   refx_HPP
#define   refx_HPP

class     refx;

class     DBHandle;
class     DBIndex;
class     LACObject;
class     exd;
class     inti;
#include  <cPIACC.h>
#include  <sEB_Number.hpp>
#include  <sref.hpp>
#pragma pack(8)

class  refx :public ref
{

public     :
public     : virtual                             int32 AddExt (EB_Number ebsnum, char *skey, int32 lindx0 );
public     : virtual                             logical AddID (inti *intiptr, EB_Number entnr, int32 lindx0 );
public     : virtual                             logical CheckWProtect ( );
public     : virtual                             logical DelExt (int32 lindx0 );
public     : virtual                             logical DeleteID (inti *intiptr, void *oldinst, EB_Number entnr );
public     : virtual                             int32 GetCount ( );
public     : virtual                             EB_Number GetID (int32 indx0 );
public     :                                     int32 GetIndex (char *skey, EB_Number ebsnum, logical exact=YES );
public     : virtual                             logical UpdateID (inti *intiptr, void *oldinst, EB_Number entnr );
public     :                                                             refx (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, DBIndex *akcbptr, logical globind );
public     :                                     void refxsup (EB_Number *rexptr );
public     : virtual                                                     ~refx ( );
};

#pragma pack()
#endif
