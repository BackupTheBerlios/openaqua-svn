/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    mvlx

\brief    


\date     $Date: 2006/03/12 19:14:39,43 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   mvlx_HPP
#define   mvlx_HPP

class     mvlx;

#define  MVLX_OLN                                  12
class     DBHandle;
class     DBIndex;
class     LACObject;
class     exd;
class     mven;
#include  <cPIACC.h>
#include  <sEB_Number.hpp>
#include  <smvlp.hpp>
#pragma pack(8)

class  mvlx :public mvlp
{
protected  :         int32                                        mvlxcnt ATTR_ALIGN(4);                                     
protected  :         mvlp                                        *mvlxmvlp;                                                  
protected  :         int32                                        mvlxstrt;                                                  
protected  :         int16                                        mvlxindx;                                                  

public     :
                     int32                                        get_mvlxcnt() { return(mvlxcnt); }
                     mvlp                                        *get_mvlxmvlp() { return(mvlxmvlp); }
                     int32                                        get_mvlxstrt() { return(mvlxstrt); }
                     int16                                        get_mvlxindx() { return(mvlxindx); }
public     : virtual                             logical CheckIndex (NString &nresult, logical repair );
protected  : virtual                             logical FillIndexEntry (int32 lindx0 );
public     : virtual                             int32 GetCount ( );
public     : virtual                             EB_Number GetID (int32 lindx0 );
public     : virtual                             char *GetKey (int32 lindx0, char *keyptr );
public     : virtual                             logical GetTable ( );
public     : virtual                             logical ReadIndexEntry (int32 lindx0, void *instptr );
public     : virtual                             logical Refresh ( );
public     : virtual                             logical RepairMVL ( );
public     : virtual                             logical Reset ( );
public     : virtual                             logical ResetTable (mven *mvenptr );
public     : virtual                             logical Save ( );
public     : virtual                             void SetVersion (uint16 version_nr=CUR_VERSION );
public     : virtual                             logical Setup (EB_Number *extref, EB_Number clnumb, int16 w_mbnumber=0 );
public     : virtual                             logical WriteIndexEntry (int32 lindx0, void *instptr );
public     :                                                             mvlx (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, DBIndex *akcbptr, char otyp, int16 maxl, logical globind );
public     :                                     int32 mvlxbsr (char *skey );
public     :                                     int32 mvlxcntc ( );
protected  :                                     logical mvlxdcr ( );
protected  :                                     logical mvlxicr ( );
public     :                                     logical mvlxidl (int32 lindx0 );
public     :                                     int32 mvlxstrc (int16 indx );
public     : virtual                                                     ~mvlx ( );
public     :                                     void reset_mvlxindx ( ){

  mvlxindx = 0;

}

};

#pragma pack()
#endif
