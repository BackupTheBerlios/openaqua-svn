/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    StructAccess

\brief    


\date     $Date: 2006/03/12 19:13:53,56 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   StructAccess_HPP
#define   StructAccess_HPP

class     StructAccess;

class     DBHandle;
class     DBStructDef;
class     RefAccess;
class     exd;
class     isel;
#include  <sEB_Number.hpp>
#pragma pack(8)

class  StructAccess
{
protected  :         DBStructDef                                 *struct_def;                                                //
protected  :         char                                        *instarea;                                                  
protected  :         RessourceLock                                ref_lock;                                                  
protected  :         logical                                      pif;                                                       

public     :
                     DBStructDef                                 *get_struct_def() { return(struct_def); }
                     char                                        *get_instarea() { return(instarea); }
                     RessourceLock                               &get_ref_lock() { return(ref_lock); }
                     logical                                      get_pif() { return(pif); }
public     : virtual opa7ImpExp                  exd *CreateInstance (int16 mbnumber, EB_Number clnumb, int32 instlen, uint16 version_nr=CUR_VERSION );
public     : virtual opa7ImpExp                  exd *GetEXD (exd *exdarea );
public     : virtual opa7ImpExp                  exd *GetEXD (EB_Number entnr, uint16 version_nr=CUR_VERSION );
public     :         opa7ImpExp                  int32 GetInstLength ( );
public     : virtual opa7ImpExp                  exd *GetInstance (EB_Number ebsnum, EB_Number clnumb, void *instptr, exd *exdarea, int32 instlen, uint16 version, logical *p_update );
public     : virtual opa7ImpExp                  exd *GetInstance (void *instptr, exd *exdarea );
public     : virtual opa7ImpExp                  RefAccess *GetRefAccess ( );
public     :                                     logical ILock (logical wait );
public     :                                     logical IUnlock ( );
public     : virtual opa7ImpExp                  logical PutInstance (void *instptr, exd *exdarea, int32 instlen, logical refresh_opt=NO );
public     :                                     void SetPIF ( );
public     :         opa7ImpExp                                          StructAccess (DBStructDef *strdefptr );
public     :         opa7ImpExp                                          StructAccess ( );
public     : virtual opa7ImpExp                                          ~StructAccess ( );
};

#pragma pack()
#endif
