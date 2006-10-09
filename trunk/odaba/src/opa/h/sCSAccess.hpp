/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/15|18:19:36,78}|(REF)
\class    CSAccess

\brief    


\date     $Date: 2006/04/03 18:38:29,70 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CSAccess_HPP
#define   CSAccess_HPP

class     CSAccess;

class     DBFieldDef;
class     DBHandle;
class     DBStructDef;
class     LACObject;
class     cst;
class     exd;
#include  <sEB_Number.hpp>
#include  <sRefAccess.hpp>
#include  <sStructAccess.hpp>
#pragma pack(8)

class  CSAccess :public RefAccess
{
protected  :         cst                                         *cs_table ATTR_ALIGN(4);                                    
protected  :         exd                                         *cs_entry;                                                  
protected  :         int16                                        id_size;                                                   
protected  :         logical                                      owns_table;                                                

public     :
                     cst                                         *get_cs_table() { return(cs_table); }
                     exd                                         *get_cs_entry() { return(cs_entry); }
public     :                                     logical AddInstance (void *instptr );
public     :                                                             CSAccess (LACObject *lobhandle, DBFieldDef *fielddef, uint16 len, logical extopt, cst *cstptr );
public     :                                     exd *GetInstance (EB_Number ebsnum, EB_Number clnumb, void *instptr, exd *exdarea, int32 instlen, uint16 version, logical *p_update );
public     :                                     exd *GetInstance (void *instptr, exd *exdarea );
public     : virtual                             logical PutInstance (void *instptr, exd *exdarea, int32 instlen, logical refresh_opt=NO );
public     :                                                             ~CSAccess ( );
};

#pragma pack()
#endif
