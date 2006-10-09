/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    mvlz

\brief    


\date     $Date: 2006/03/12 19:14:40,71 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   mvlz_HPP
#define   mvlz_HPP

class     mvlz;

class     DBHandle;
class     DBIndex;
class     LACObject;
#include  <sEB_Number.hpp>
#include  <smvl.hpp>
#include  <smvlp.hpp>
#pragma pack(8)

class  mvlz :public mvl
{
protected  :         EB_Number                                    mvlzebsn ATTR_ALIGN(4);                                    

public     :
                     EB_Number                                   &get_mvlzebsn() { return(mvlzebsn); }
public     : virtual                             int32 AddExt (EB_Number ebsnum, char *skey, int32 lindx0 );
public     : virtual                             logical AddID (void *instptr, EB_Number entnr, int32 lindx0 );
public     : virtual                             logical DeleteID (void *instptr, void *oldinst, EB_Number entnr );
public     : virtual                             logical FillIndexEntry (int32 lindx0 );
public     : virtual                             EB_Number GetID (int32 lindx0 );
public     : virtual                             int32 GetIndex (char *skey, EB_Number ebsnum, logical exact=YES );
public     : virtual                             char *GetKey (int32 lindx0, char *keyptr );
public     :                                     logical UpdateID (void *instptr, void *oldinst, EB_Number entnr );
public     :                                                             mvlz (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, int16 maxl, logical globind );
public     : virtual                                                     ~mvlz ( );
};

#pragma pack()
#endif
