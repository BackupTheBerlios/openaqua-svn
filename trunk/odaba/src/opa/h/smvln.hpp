/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    mvln

\brief    


\date     $Date: 2006/03/12 19:14:38,04 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   mvln_HPP
#define   mvln_HPP

class     mvln;

class     DBHandle;
class     DBIndex;
class     LACObject;
class     exd;
class     inti;
#include  <cPIACC.h>
#include  <sEB_Number.hpp>
#include  <smvlx.hpp>
#pragma pack(8)

class  mvln :public mvlx
{
protected  :         EB_Number                                    mvlnebs ATTR_ALIGN(4);                                     

public     :
public     : virtual                             int32 AddExt (EB_Number ebsnum, char *skey, int32 lindx0 );
public     : virtual                             logical AddID (inti *intiptr, EB_Number entnr, int32 lindx0 );
public     : virtual                             logical DelExt (int32 lindx0 );
public     : virtual                             logical DeleteID (inti *intiptr, void *oldinst, EB_Number entnr );
public     : virtual                             logical DeleteID (EB_Number entnr );
protected  : virtual                             logical FillIndexEntry (int32 lindx0 );
public     : virtual                             int32 GetIndex (char *skey, EB_Number ebsnum, logical exact=YES );
public     : virtual                             logical UpdateID (inti *intiptr, void *oldinst, EB_Number entnr );
public     :                                                             mvln (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, DBIndex *akcbptr, int16 maxl, logical globind );
public     : virtual                                                     ~mvln ( );
};

#pragma pack()
#endif
