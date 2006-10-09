/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    mvld

\brief    


\date     $Date: 2006/03/12 19:14:35,34 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   mvld_HPP
#define   mvld_HPP

class     mvld;

class     DBIndex;
class     LACObject;
class     binti;
class     exd;
class     inti;
#include  <sEB_Number.hpp>
#include  <smvl.hpp>
#include  <smvlp.hpp>
#pragma pack(8)

class  mvld :public mvlp
{
protected  :         char                                        *ext_area ATTR_ALIGN(4);                                    
protected  :         DBStructDef                                 *cur_struct;                                                

public     :
                     char                                        *get_ext_area() { return(ext_area); }
                     DBStructDef                                 *get_cur_struct() { return(cur_struct); }
public     : virtual                             int32 AddExt (EB_Number ebsnum, char *skey, int32 lindx0 );
public     : virtual                             logical AddID (inti *intiptr, EB_Number entnr, int32 lindx0 );
public     :                                     logical CheckVersion ( );
public     :                                     logical ConvertInstVersion (void *instptr, void *oldinst );
public     : virtual                             logical DeleteID (inti *intiptr, void *oldinst, EB_Number entnr );
public     : virtual                             logical DeleteID (EB_Number entnr );
public     :                                     int32 EBSNumToIndex (EB_Number ebsnum );
public     :                                     logical FillIndexEntry (int32 lindx0 );
public     : virtual                             EB_Number GetID (int32 lindx0 );
public     : virtual                             int32 GetIndex (char *skey, EB_Number ebsnum, logical exact=YES );
public     : virtual                             int32 GetIndex (EB_Number ebsnum );
public     : virtual                             char *GetKey (int32 lindx0, char *keyptr );
public     :                                     EB_Number IndexToEBSNum (int32 lindx0 );
public     : virtual                             logical ReadIndexEntry (int32 lindx0, void *instptr );
public     : virtual                             logical Refresh ( );
public     :                                     logical SetCurrentStructDef ( );
public     : virtual                             logical UpdateID (inti *intiptr, void *oldinst, EB_Number entnr );
public     : virtual                             logical WriteIndexEntry (int32 lindx0, void *instptr );
public     :                                                             mvld (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, DBIndex *akcbptr, int16 maxl, logical globind );
public     : virtual                                                     ~mvld ( );
};

#pragma pack()
#endif
