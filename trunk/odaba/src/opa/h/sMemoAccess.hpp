/********************************* Class Declaration ***************************/
/**
\package  OPA
\class    MemoAccess



\date     $Date: 2006/05/09 13:59:52,89 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   MemoAccess_HPP
#define   MemoAccess_HPP

class     MemoAccess;

class     ACObject;
class     fmcb;
#include  <sacc.hpp>
#pragma pack(8)

class  MemoAccess :public acc
{
protected  :         PropertyHandle                               void_pi;                                                   
protected  :         int16                                        max_size;                                                  

public     :
                     PropertyHandle                              &get_void_pi() { return(void_pi); }
                     int16                                        get_max_size() { return(max_size); }
public     : virtual                                char *Access (int32 lindx0, char *string, int32 maxlen );
public     : virtual                                logical DirToRef (fmcb *targfmcb, fmcb *srcefmcb, void *targfld, void *srcefld, logical replace=NO );
public     :                                             MemoAccess (ACObject *obhandle, int16 maxsize );
public     : virtual                                logical RefToDir (fmcb *targfmcb, fmcb *srcefmcb, void *targfld, void *srcefld, logical replace=NO );
public     : virtual                                logical RefToRef (fmcb *targfmcb, fmcb *srcefmcb, void *targfld, void *srcefld, logical replace=NO );
public     : virtual                                     ~MemoAccess ( );
};

#pragma pack()
#endif
