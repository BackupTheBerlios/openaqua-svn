/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    refp

\brief    


\date     $Date: 2006/03/12 19:15:04,23 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   refp_HPP
#define   refp_HPP

class     refp;

class     DBHandle;
class     DBIndex;
class     LACObject;
class     exd;
class     inti;
class     refx;
#include  <sEB_Number.hpp>
#include  <srefs.hpp>
#pragma pack(8)

class  refp :public refs
{
protected  :         refx                                        *refprefx ATTR_ALIGN(4);                                    

public     :
                     refx                                        *get_refprefx() { return(refprefx); }
public     : virtual                             int32 AddExt (EB_Number ebsnum, char *skey, int32 lindx0 );
public     : virtual                             logical AddID (inti *intiptr, EB_Number entnr, int32 lindx0 );
public     :                                     logical CheckVersion6 ( );
public     : virtual                             logical CheckWProtect ( );
public     : virtual                             logical DelExt (int32 lindx0 );
public     : virtual                             logical DeleteID (inti *intiptr, void *oldinst, EB_Number entnr );
public     : virtual                             int32 GetCount ( );
public     : virtual                             EB_Number GetID (int32 indx0 );
public     : virtual                             int32 GetIndex (char *skey, EB_Number ebsnum, logical exact=YES );
public     : virtual                             exd *ProvideEXD ( );
public     : virtual                             logical Refresh ( );
public     :                                     logical Save ( );
public     :                                     void SetVersion (uint16 version_nr=CUR_VERSION );
public     : virtual                             logical UpdateID (inti *intiptr, void *oldinst, EB_Number entnr );
public     :                                                             refp (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, DBIndex *akcbptr, logical globind );
public     : virtual                                                     ~refp ( );
};

#pragma pack()
#endif
