/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ACStructure

\brief    


\date     $Date: 2006/03/12 19:12:14,39 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACStructure_HPP
#define   ACStructure_HPP

class     ACStructure;

class     DBHandle;
class     DBStructDef;
class     LACObject;
class     exd;
class     exdBuffer;
class     isel;
#include  <sEB_Number.hpp>
#include  <sRefAccess.hpp>
#include  <sStructAccess.hpp>
#pragma pack(8)

class  ACStructure :public RefAccess
{
protected  :         exdBuffer                                   *struct_buffer ATTR_ALIGN(4);                               //

public     :
                     exdBuffer                                   *get_struct_buffer() { return(struct_buffer); }
public     :                                                             ACStructure (LACObject *lobhandle, DBStructDef *strdefptr, int16 maxcount, logical shadow_read=NO );
public     :                                                             ACStructure ( );
public     :                                     logical ConvertInstance (exd *exdarea, void *instptr, int32 instlen, logical *p_update );
public     :                                     exd *CreateEXD (char *extarea, int32 instlen, uint16 version );
public     : virtual                             exd *CreateInstance (int16 mbnumber, EB_Number clnumb, int32 instlen, uint16 version_nr=CUR_VERSION );
public     : virtual                             exd *GetEXD (exd *exdarea );
public     : virtual                             int32 GetInstLength ( );
public     : virtual                             exd *GetInstance (EB_Number ebsnum, EB_Number clnumb, void *instptr, exd *exdarea, int32 instlen, uint16 version, logical *p_update );
public     : virtual                             exd *GetInstance (void *instptr, exd *exdarea, logical *p_update );
public     : virtual                             logical PutInstance (void *instptr, exd *exdarea, int32 instlen, logical refresh_opt=NO );
public     : virtual                             exd *ReadInstance (exd *exdarea, int32 instlen );
public     : virtual                                                     ~ACStructure ( );
};

#pragma pack()
#endif
