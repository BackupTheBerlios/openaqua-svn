/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    mvli

\brief    


\date     $Date: 2006/03/12 19:14:36,53 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   mvli_HPP
#define   mvli_HPP

class     mvli;

#define  MVLI_OLN                                  8
class     DBHandle;
class     DBIndex;
class     LACObject;
class     exd;
class     inti;
#include  <cPIACC.h>
#include  <sEB_Number.hpp>
#include  <smvlp.hpp>
#pragma pack(8)

class  mvli :public mvlp
{

public     :
public     : virtual                             int32 AddExt (EB_Number ebsnum, char *skey, int32 lindx0 );
public     : virtual                             logical AddID (inti *intiptr, EB_Number entnr, int32 lindx0 );
public     : virtual                             logical DeleteID (inti *intiptr, void *oldinst, EB_Number entnr );
public     :                                     EB_Number *GetIDPointer (char *skey );
public     : virtual                             int32 GetIndex (char *skey, EB_Number ebsnum, logical exact=YES );
public     : virtual                             char *GetKey (int32 lindx0, char *keyptr );
public     : virtual                             logical UpdateID (inti *intiptr, void *oldinst, EB_Number entnr );
public     :                                                             mvli (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, DBIndex *akcbptr, int16 maxl, logical globind );
public     : virtual                                                     ~mvli ( );
};

#pragma pack()
#endif
