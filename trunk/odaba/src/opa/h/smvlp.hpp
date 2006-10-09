/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    mvlp

\brief    


\date     $Date: 2006/03/12 19:14:38,68 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   mvlp_HPP
#define   mvlp_HPP

class     mvlp;

#define  MVLP_ECT                                  3
#define  MVLP_OLN                                  8
class     DBHandle;
class     DBIndex;
class     LACObject;
class     exd;
class     inti;
#include  <cPIACC.h>
#include  <sEB_Number.hpp>
#include  <smvl.hpp>
#pragma pack(8)

class  mvlp :public mvl
{
protected  :         EB_Number                                   *mvlpenty ATTR_ALIGN(4);                                    

public     :
                     EB_Number                                   *get_mvlpenty() { return(mvlpenty); }
public     : virtual                             int32 AddExt (EB_Number ebsnum, char *skey, int32 lindx0 );
public     : virtual                             logical AddID (inti *intiptr, EB_Number entnr, int32 lindx0 );
public     : virtual                             logical DeleteID (inti *intiptr, void *oldinst, EB_Number entnr );
protected  : virtual                             logical FillIndexEntry (int32 lindx0 );
public     : virtual                             EB_Number GetID (int32 lindx0 );
public     :                                     int32 MoveDown (int32 lindx0 );
public     :                                     int32 MoveUp (int32 lindx0 );
public     : virtual                             logical RepairMVL ( );
public     : virtual                             logical UpdateID (inti *intiptr, void *oldinst, EB_Number entnr );
public     :                                                             mvlp (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, char otyp, int16 olen, int16 maxl, DBIndex *akcbptr, logical globind );
public     :                                     void mvlpcrt (EB_Number ebsnum, char *skey );
public     :                                     int32 mvlpidxg (EB_Number ebsnum );
public     : virtual                                                     ~mvlp ( );
};

#pragma pack()
#endif
